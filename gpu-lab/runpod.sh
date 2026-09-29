#!/usr/bin/env bash
# Drive a RunPod RTX 4090 pod over HTTPS only (outbound SSH is blocked here).
#
#   RUNPOD_API_KEY=... ./runpod.sh up            # create pod, wait for agent, save state
#   ./runpod.sh attach [pod-id]                  # join an already-running shared pod instead of up
#   ./runpod.sh push <variant-name> <dir>        # upload a candidates/pinning copy as a variant
#   ./runpod.sh sync                             # upload repo (base tree) + lab scripts
#   ./runpod.sh run '<bash script>'              # run on the pod, stream the log until done
#   ./runpod.sh get <remote-path> <local-path>
#   ./runpod.sh down                             # terminate the pod (stops billing)
#
# State (pod id, agent token) lives in .gpu-lab/.pod, never in the repository.
set -euo pipefail
LAB="$(cd "$(dirname "$0")" && pwd)"; REPO="$(dirname "$LAB")"
STATE="$LAB/.pod"; API=https://rest.runpod.io/v1
GPU_TYPE=${GPU_TYPE:-NVIDIA GeForce RTX 4090}
CLOUD=${CLOUD:-SECURE}
IMAGE=${IMAGE:-nvidia/cuda:12.8.1-devel-ubuntu24.04}

api() { curl -fsS -H "Authorization: Bearer ${RUNPOD_API_KEY:?set RUNPOD_API_KEY}" -H 'Content-Type: application/json' "$@"; }
load() { [[ -f $STATE ]] || { echo "no pod; run: $0 up" >&2; exit 1; }; . "$STATE"; URL="${AGENT_URL:-https://${POD_ID}-8000.proxy.runpod.net}"; }
agent() { local m=$1 p=$2; shift 2; curl -fsS --retry 3 -X "$m" -H "X-Token: $TOKEN" "$URL$p" "$@"; }

case "${1:-}" in
up)
  TOKEN=$(python3 -c 'import secrets;print(secrets.token_hex(24))')
  AGENT_B64=$(base64 -w0 "$LAB/pod_agent.py")
  start='set -e; apt-get update -qq && DEBIAN_FRONTEND=noninteractive apt-get install -y -qq python3 libssl-dev >/dev/null; mkdir -p /work; echo "$AGENT_B64" | base64 -d > /work/agent.py; exec python3 /work/agent.py'
  body=$(python3 - "$TOKEN" "$AGENT_B64" "$start" <<'PY'
import json, os, sys
tok, b64, start = sys.argv[1:4]
print(json.dumps({
  "name": os.environ.get("POD_NAME", "qsb-pinning-ab"), "imageName": os.environ.get("IMAGE", "nvidia/cuda:12.8.1-devel-ubuntu24.04"),
  "gpuTypeIds": [os.environ.get("GPU_TYPE", "NVIDIA GeForce RTX 4090")], "gpuCount": 1,
  "cloudType": os.environ.get("CLOUD", "SECURE"), "containerDiskInGb": 30, "volumeInGb": 0,
  "ports": ["8000/http"], "allowedCudaVersions": ["12.8", "12.9", "13.0"], "env": {"AGENT_TOKEN": tok, "AGENT_B64": b64},
  "dockerEntrypoint": ["bash", "-c"], "dockerStartCmd": [start],
}))
PY
)
  POD_ID=$(api -X POST "$API/pods" -d "$body" | python3 -c 'import json,sys;print(json.load(sys.stdin)["id"])')
  printf 'POD_ID=%s\nTOKEN=%s\n' "$POD_ID" "$TOKEN" > "$STATE"; chmod 600 "$STATE"
  echo "pod $POD_ID created; waiting for agent..."
  load
  for i in $(seq 1 90); do
    if curl -fsS --max-time 10 "$URL/health" >/dev/null 2>&1; then echo "agent up at $URL"; exit 0; fi
    sleep 10
  done
  echo "agent did not come up in 15 min; check the pod in the RunPod console, then '$0 down'" >&2; exit 1 ;;
attach)
  # Join an already-running shared pod: the agent token is read from the pod's env via the
  # RunPod API, so it never has to be passed through chat. Optional arg: pod id.
  api "$API/pods" | python3 -c '
import json, sys
want = sys.argv[1] if len(sys.argv) > 1 else None
pods = [p for p in json.load(sys.stdin) if p.get("desiredStatus") == "RUNNING"
        and (p["id"] == want if want else p.get("name") == "qsb-pinning-ab")]
if len(pods) != 1: sys.exit(f"attach: expected 1 running qsb-pinning-ab pod, found {len(pods)}")
p = pods[0]; tok = (p.get("env") or {}).get("AGENT_TOKEN")
if not tok: sys.exit("attach: pod has no AGENT_TOKEN in env")
print("POD_ID=%s\nTOKEN=%s" % (p["id"], tok))' ${2:-} > "$STATE.tmp" && mv "$STATE.tmp" "$STATE" && chmod 600 "$STATE"
  load; curl -fsS --max-time 15 "$URL/health" >/dev/null && echo "attached to $POD_ID ($URL)" ;;
sync)
  load
  tar -C "$REPO" --exclude=.git --exclude=.gpu-lab --exclude=benchmark-results --exclude='__pycache__' -czf /tmp/qsb-repo.tgz .
  agent POST "/put?path=/work/repo.tgz" --data-binary @/tmp/qsb-repo.tgz >/dev/null
  for f in ab.sh analyze.py; do agent POST "/put?path=/work/lab/$f" --data-binary @"$LAB/$f" >/dev/null; done
  "$0" run 'rm -rf /work/repo && mkdir -p /work/repo && tar -C /work/repo -xzf /work/repo.tgz && chmod +x /work/lab/ab.sh && nvidia-smi --query-gpu=name,driver_version,power.limit,clocks.max.sm --format=csv && nvcc --version | tail -1' ;;
push)
  load; name=$2; dir=$3
  tar -C "$dir" -czf /tmp/qsb-var.tgz .
  agent POST "/put?path=/work/var-$name.tgz" --data-binary @/tmp/qsb-var.tgz >/dev/null
  "$0" run "rm -rf /work/variants/$name /work/bin/$name && mkdir -p /work/variants/$name && tar -C /work/variants/$name -xzf /work/var-$name.tgz && ls /work/variants/$name | wc -l" ;;
run)
  load
  id=$(agent POST /exec --data-binary "$2" | python3 -c 'import json,sys;print(json.load(sys.stdin)["id"])')
  echo "job $id" >&2
  seen=0; tmp=$(mktemp)
  while :; do
    agent GET "/job?id=$id&tail=1000000" > "$tmp"
    # print only new log lines; last line of helper output is "<count> <rc-or-empty>"
    out=$(python3 - "$tmp" "$seen" <<'PY'
import json, sys
j = json.load(open(sys.argv[1])); lines = j["log"].splitlines(); n = int(sys.argv[2])
for l in lines[n:]: print(l)
print(len(lines), "" if not j["done"] else j["rc"])
PY
)
    body=$(printf '%s\n' "$out" | sed '$d'); [[ -n $body ]] && printf '%s\n' "$body"
    read -r seen rc <<<"$(printf '%s\n' "$out" | tail -1)"
    [[ -n ${rc:-} ]] && { rm -f "$tmp"; exit "$rc"; }
    sleep 15
  done ;;
get)
  load; agent GET "/get?path=$2" -o "$3" ;;
down)
  load; api -X DELETE "$API/pods/$POD_ID" >/dev/null && rm -f "$STATE" && echo "pod $POD_ID terminated" ;;
*) sed -n 2,12p "$0"; exit 2 ;;
esac
