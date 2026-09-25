#!/usr/bin/env bash
# Interleaved A/B timing of pinning variants on ONE GPU (runs on the pod).
#
#   ab.sh <seconds> <rounds> <variant> [variant ...]
#
# Each variant is a directory /work/variants/<name>/ holding a full copy of
# candidates/pinning. Every variant is built with the RANKED command
# (nvcc -O3 -DQSB_ZEROS_N=24, no -arch: the embedded sm_89 carrier is what runs
# on a 4090). Rounds alternate order (ABBA...) so drift and heat hit both sides
# equally; before each run the GPU cools to $COOL_C (default 45 C) so every leg
# starts from the same thermal state. All runs use one fixed problem seed so hit
# sets are directly comparable.
set -euo pipefail
secs=$1; rounds=$2; shift 2; variants=("$@")
COOL_C=${COOL_C:-45}
SEED=${SEED:-444838033}
W=/work
mkdir -p $W/bin $W/runs

if [[ ! -f $W/problem/pinning.bin ]]; then
  python3 $W/repo/harness/gen_problem.py --seed "$SEED" --out-dir $W/problem
fi

for v in "${variants[@]}"; do
  mkdir -p $W/bin/$v
  if [[ ! -x $W/bin/$v/pinning ]]; then
    echo "== build $v"
    (cd $W/variants/$v && nvcc -O3 -DQSB_ZEROS_N=24 -o $W/bin/$v/pinning pinning.cu -lcrypto -lm 2>&1 | grep -v -E 'deprecated|SHA256_|~~~|\^|note:|^\s*[0-9]+ \|' || true)
  fi
done

cool() {
  local t0=$SECONDS
  while :; do
    t=$(nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader,nounits | head -1)
    (( t <= COOL_C )) && break
    (( SECONDS - t0 > 300 )) && { echo "  cool: still ${t}C after 300s, starting anyway"; break; }
    sleep 5
  done
  echo "  start temp ${t}C"
}

run_one() {  # variant round
  local v=$1 r=$2 d=$W/runs/$1-r$2
  rm -rf "$d"; mkdir -p "$d"; cool
  nvidia-smi --query-gpu=timestamp,temperature.gpu,clocks.sm,clocks.mem,power.draw,clocks_throttle_reasons.active \
    --format=csv,noheader -l 5 > "$d/smi.csv" &
  local smi=$!
  (cd "$d" && stdbuf -oL timeout "$secs" $W/bin/$v/pinning $W/problem/pinning.bin 0 1 0 single_hash > out.log 2>&1) || true
  kill $smi 2>/dev/null || true
  echo "  $v r$r: $(grep -E 'seq #' "$d/out.log" | tail -1)"
}

for ((r=0; r<rounds; r++)); do
  echo "== round $r"
  if (( r % 2 == 0 )); then order=("${variants[@]}"); else
    order=(); for ((i=${#variants[@]}-1; i>=0; i--)); do order+=("${variants[$i]}"); done; fi
  for v in "${order[@]}"; do run_one "$v" "$r"; done
done
python3 $W/lab/analyze.py $W/runs "${variants[@]}"
