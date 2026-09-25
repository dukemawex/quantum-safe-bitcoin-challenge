# QSB pinning — GPU A/B lab

Tooling for measuring pinning-track kernel changes on a rented RTX 4090 before
spending a ranked Yukon submission. None of this is part of a submission: the
track's only editable path is `candidates/pinning/`.

## Why

- Official runs fall in two runner classes, fingerprinted by `elapsed_s`:
  ~1201.5 s runners score 909–921 M/s, ~1201.0 s runners 870–892 M/s.
- The same source scored 913.9 M and 920.8 M on two fast-class draws, so one
  official run cannot resolve a sub-1% change. Promotion needs +1% over
  914,845,044 (≈ 924.0 M) *and* a fast draw.
- Earlier ledgers attribute up to ~29 s of each 1200 s window to startup; the
  current frontier's remaining startup cost is unmeasured.

## Files

| File | Runs on | Purpose |
|---|---|---|
| `bootstrap.sh` | session | Recreate the work dir (git clone + Yukon link config; `yukon clone` 404s), install CUDA 12.8 |
| `runpod.sh` | session | Create/terminate a 4090 pod; upload repo and variants; run jobs over HTTPS |
| `pod_agent.py` | pod | Token-authenticated HTTP job agent (outbound SSH is blocked from the session) |
| `ab.sh` | pod | Build variants with the ranked command, interleaved ABBA runs from a fixed start temperature |
| `make_clang_variant.sh` | session | Variant whose embedded sm_89 image is built by clang 18 (LLVM NVPTX) + ptxas 12.8 instead of nvcc |
| `analyze.py` | pod | Sustained M/s after warm-up per variant, and exact hit-set equality over completed sequences |

## Shared pod (more than one agent)

The pod may be shared. Do **not** run `runpod.sh up` or `down` if one is already running:

```sh
.gpu-lab/runpod.sh attach        # find the running qsb-pinning-ab pod, read its agent token via the RunPod API
```

`ab.sh` takes an exclusive `flock` on `/work/gpu.lock` for its whole run, so A/B timings from
different agents queue instead of overlapping. Use your own variant names (`push <name>`),
and don't delete other agents' `/work/variants/*` or `/work/runs/*`. Only terminate the pod
when every agent using it is done.

## Use

```sh
# RUNPOD_API_KEY comes from the environment settings, never from chat.
.gpu-lab/runpod.sh up
.gpu-lab/runpod.sh sync
.gpu-lab/runpod.sh push base candidates/pinning          # the promoted tree
.gpu-lab/runpod.sh push cand /path/to/modified/pinning   # a variant
.gpu-lab/runpod.sh run '/work/lab/ab.sh 300 4 base cand'
.gpu-lab/runpod.sh down                                  # stop billing
```

The native sm_89 image in `qsb_carrier_sm89.h` is what runs on a 4090; after any
device-code edit rerun `candidates/pinning/build_carrier.sh 24` with CUDA 12.8.
The toolchain installed by `bootstrap.sh` reproduces the committed image
byte-for-byte (sha256 f38efa14…, 282,336 bytes).

## clang 18 image (first variant to A/B)

`./make_clang_variant.sh /path/out` copies `candidates/pinning` and regenerates only
`qsb_carrier_sm89.h` from clang 18.1.3 PTX. Static comparison against the nvcc image:

| Kernel | nvcc 12.8 | clang 18 + ptxas 12.8 |
|---|---|---|
| stage 0 prepare | 6,608 SASS, 122 regs, 0 stack | 6,656 SASS, 128 regs, 0 stack |
| stage 2 finish | 4,128 SASS, 64 regs | 4,128 SASS, 70 regs |

Both keep 3 `LTC64B` table loads and zero spills; occupancy is unchanged (128 and 73
register caps). Without `-mllvm -inline-threshold=100000` clang leaves
`_FixedBaseSignedXYZZScalar` as a call with a 160-byte stack frame.

## Measured on RunPod RTX 4090 (stock 450 W, driver 580.159, CUDA 12.8), 2026-09-25

| Experiment | Result |
|---|---|
| clang 18 image vs frontier, 4-round ABBA 180 s, 40 C starts | **-1.00%** (898.2 vs 907.2 M/s sustained; cold 923 vs 931). 17,851 identical hits across 8 runs. Dropped. |
| Startup before search (frontier) | 0.90 s (carrier 0.25 s, GPU table build 0.65 s): 0.08% of the window, no lever left. |
| Throttle state during every run | SW power cap the whole time (450 W, ~2,250 MHz of 3,105 max), no thermal slowdown. Throughput = work per joule. |
| Diagnostic: cold-bank reads redirected into L2 (wrong math) | +5.77%: upper bound on everything the 4 DRAM reads/candidate cost. |

Implication: the frontier is power-capped, so a change must cut executed instructions or DRAM energy;
latency tricks (prefetch, occupancy, extra loads) cost energy and lose. Swapping a cold read for an extra
point addition (~9% of arithmetic) cannot pay back its ~1.45%.
