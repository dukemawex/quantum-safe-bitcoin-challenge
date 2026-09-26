#!/usr/bin/env bash
# Reproduce the ranked flow (setup.sh + benchmark.sh with the gpu_wrap grinder) for one variant,
# with a short window, and report where it fails.
#   dbg.sh <variant> [seconds]
v=$1; secs=${2:-60}
R=/work/r_$v
rm -rf "$R"; cp -r /work/repo "$R"; rm -rf "$R/candidates/pinning"; cp -r "/work/variants/$v" "$R/candidates/pinning"
cd "$R"
echo "=== $v: setup"
./setup.sh pinning > setup.log 2>&1; echo "setup rc=$?"; tail -4 setup.log
echo "=== $v: benchmark ${secs}s"
QSB_GRINDER="cmd:python3 harness/gpu_wrap.py --src candidates/pinning/pinning.cu" QSB_SECONDS=$secs \
  timeout $((secs+180)) ./benchmark.sh pinning > bench.log 2>&1; echo "benchmark rc=$?"
grep -E "carrier|GTable|seq #|rror|failed|Abort|illegal|SCORE|RESULT|verified|Traceback" bench.log | head -25
tail -6 bench.log
