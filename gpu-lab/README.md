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
