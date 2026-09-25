#!/usr/bin/env bash
# Measure in-window startup dead time of variants on the pod: wall time from
# process launch to the "=== Search:" line (the grinder's own clock starts there,
# so its M/s never shows this cost, but the ranked score does).
#   startup.sh <reps> <variant> [variant ...]
set -euo pipefail
reps=$1; shift
W=/work
exec 9>$W/gpu.lock; flock 9
for v in "$@"; do
  for ((i=0; i<reps; i++)); do
    d=$W/startup/$v-$i; rm -rf "$d"; mkdir -p "$d"; cd "$d"
    sync; echo 3 > /proc/sys/vm/drop_caches 2>/dev/null || true
    python3 - "$W/bin/$v/pinning" "$W/problem/pinning.bin" <<'PY'
import subprocess, sys, time
t0 = time.monotonic()
p = subprocess.Popen(["stdbuf", "-oL", sys.argv[1], sys.argv[2], "0", "1", "0", "single_hash"],
                     stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
marks = {}
for line in p.stdout:
    t = time.monotonic() - t0
    for key in ("Native sm_89 carrier", "GTable built", "=== Search", "seq #10 "):
        if key in line and key not in marks:
            marks[key] = t
    if "seq #10 " in line:
        break
p.kill(); p.wait()
print("  " + "  ".join(f"{k.strip('= ')}@{v:.2f}s" for k, v in marks.items()))
PY
  done
done
