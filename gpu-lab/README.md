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
| Diagnostic: stage-0 tail + SHA256d replaced by a cheap mix | +6.4% sustained / +7.5% cold: stage-0 SHA share. |
| Diagnostic: two pubkey SHA-256s replaced by a cheap mix | +8.1% sustained / +8.2% cold: stage-2 SHA share. |
| Remainder | ~80% is the 11-addition XYZZ chain, recovery and batched inversion. |

Implication: the frontier is power-capped, so a change must cut executed instructions or DRAM energy;
latency tricks (prefetch, occupancy, extra loads) cost energy and lose. Swapping a cold read for an extra
point addition (~9% of arithmetic) cannot pay back its ~1.45%.

DRAM cost is nonlinear: 4 random 64 B reads/candidate (~230 GB/s) cost <=5.8%, but GLV10's 10 reads scored
-55% officially (random-read bandwidth knee), so the fewer-adds/bigger-table direction stays closed.
The pubkey SHA is already IV-folded, padding-folded, h0-only and FMA-pipe offloaded.

## Official results log (pinning)

| Submission | Change | Base | Official | Runner | Verified | Outcome |
|---|---|---|---|---|---|---|
| `4dd2b342` | QSB_SLOTS 3 | df1df15 (934.45M) | 891.80M | slow | yes | rejected |
| `2f2d285a` | QSB_CHAIN_ROLES under QSB_PMIX12 (2-add loop, 33 KB body) | 1968612 (960.83M) | 946.20M | fast | yes (135,538 hits) | rejected, about -1.5%: larger hot-loop body is slower despite fewer instructions |
| `07f9413e` | QSB_PHI_HOIST (phi out of hot loop, 17.9 KB to 15.7 KB) | 1968612 (960.83M) | none | n/a | n/a | FAILED at workflow step Benchmark (logs not reachable; other solvers failed at the same step at the same time; loop control flow proven identical by host simulation) |
| `aabc3509` | QSB_PHI_HOIST + QSB_TBL_POL_PRED (predicated constant-policy gathers, hot loop 997) | 1968612 (960.83M) | none | n/a | n/a | FAILED at Benchmark about 2 min after submit (fast failure; the phi hoist or the runner is suspect) |
| `9a2d6b57` | QSB_TBL_POL_PRED alone (isolation) | 1968612 (960.83M) | none | n/a | n/a | FAILED at Benchmark 1m40s after submit |

Fast-failure window 09:15-09:30 UTC: i34-9 `a81de57c`/`5e328f13` and my `07f9413e`/`aabc3509`/`9a2d6b57` all failed at Benchmark within ~2 min, while full ~20-min runs scored in between (IvanLudvig `fe9e1fa7` at 09:18). That fits one runner failing every job it picks up. The three failed builds differ (phi hoist; phi hoist + policy; policy only), and all use the same carrier rebuild process as the successful `2f2d285a`. Holding resubmission until another solver scores again.

09:40 UTC: terrapinelf `f6d7bbb9` scored 959.0M (a full run), so the runner pool is working again.
| `cff08464` | re-run of `aabc3509` (QSB_PHI_HOIST + QSB_TBL_POL_PRED) | 1968612/a137e28 (960.83M; pinning tree unchanged) | pending | | | |
| `cff08464` | re-run of `aabc3509` | a137e28 | none | n/a | n/a | FAILED at Benchmark ~1 min after submit, while i34-9 scored on another runner |

**Debug (10:05-10:20 UTC, L40S sm_89, `dbg.sh`):** the policy-only tree (`f69b60a`, same as the failed `9a2d6b57`)
passes the repository's own `setup.sh pinning` + `benchmark.sh pinning` flow: 4,525/4,525 hits verified, RESULT PASS,
648.9M/s self-reported on the L40S. So the fast Benchmark failures are not a crash in the build. At 09:46 the two
known-good runners were busy (i34-9 scoring continuously; terrapinelf `8f2ea1b3` stuck validating since 09:42), and
my job still failed within a minute, which points to a third runner that fails every job it picks up.
| `9b5b1359` | re-run: QSB_PHI_HOIST + QSB_TBL_POL_PRED | a137e28 (pinning = cc75e3b, 960.83M) | pending | | | |

**Root cause of the fast Benchmark failures (from the diagnostics artifact of run 36235560942):** the kernel binary returned after 2.5 s with 0 candidates (bridge `wall_s` 2.63; `gpu_wrap.py` does not propagate the binary's exit status, so the bridge shows exit 0). The runner was an RTX 4090 on driver 580.178.04. The carrier's kernel resources match the frontier's exactly, so this is the frontier's memory demand (21.1 GiB GLV table plus 4 slots x 4M-candidate state) not fitting that runner's free VRAM. terrapinelf's `8f2ea1b3` ran the same device code (carrier `9aafe9d7`) with an adaptive batch and scored 967,108,331.

| `231c1d40` | phi hoist + polpred + allocate-or-halve slot allocation (host only, carrier byte-identical) | a137e28 (960.83M) | 933,930,308 | 1201.52 | 133,769 | rejected (-2.8%); terrapinelf's same device code got 967.1M |
| `1a69f325` | same, fallback steps BATCH down by 1M instead of halving | a137e28 (960.83M) | pending | | | |

**Frontier moved to 979,222,732** (terrapinelf `0c9471ef`, main `e892e6e`; includes my phi hoist + predicated gathers and ercumentyildirim's green-context sub-batch pipeline). `1a69f325` (old base) cancelled.

| `f6f1c0fb` | e892e6e + QSB_SHA_FMA_ROT=0 + L2STATE bit 2 (finish discard) + GREEN_SHARED 12 | e892e6e (979.22M) | pending | | | |

Prepared next (in hand): `next-fmaadd` = above + QSB_SHA_FMA_ADD=0 (finish kernel 4,040 -> 3,600 SASS, IMAD mul-by-one 1,148 -> 30).

| `f6f1c0fb` | result | e892e6e | 974,116,490 | 1201.55 (fast) | 139,529 | rejected (-0.52%); closest to the frontier since it moved |
| `3621d601` | f6f1c0fb + QSB_SHA_FMA_ADD=0 | e892e6e | 909,724,691 | 1200.98 (slow) | 130,243 | rejected; about -1.7% vs same-class runs: finish is pipe-balanced, ALU-heavier finish loses |
| `6e8b78f6` | frontier + QSB_SUBPIPE 65536 (16 MiB state ring beside 50 MiB persisting window) + L2 discard | e892e6e (979.22M) | pending | | | |

Runner classes: every score >= 950M came from fast-class runs (elapsed ~1201.4-1201.7 s); slow-class (~1200.9-1201.1 s) tops out near 935M. Yukon deduplicates byte-identical trees (a resubmission of f6f1c0fb returned the existing result).
