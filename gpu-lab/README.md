# Current status — 2026-09-28 22:02 UTC

This header supersedes older active/waiting labels. Live source both tracks remains8d07d3ebad41a017dfaa5906b164f883a9b59348. Pinning best1008206828/kaankolcu; subset best708411009/jacklightChen.

Pinning CPU SHA32PAD246a0544 naturally REJECTED986175788 at21:44:12UTC,verified=true,141208 hits,elapsed1201.1434. Exact second-SHA32PAD-only package CLOSED; no retry.
NEW pinning92fb758c-1b05-4771-ac87-df79ff008fe8 submitted21:59:32UTC from fresh8d07 after empty own queue; VALIDATING in final query. Isolated CPU KEY33PAD word-major compressed-key SHA specialization. Native/host passed again;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Archive gpu-lab/prepared/key33pad-submitted-92fb758c.patch and gpu-lab/submission-note-key33pad-submitted.md are SUBMITTED, not waiting. Never cancel/duplicate.

Subset372154a4-3ead-43c7-b6cc-1b43fa6dd4bd SHA32PAD remains VALIDATING. Waiting subset KEY33PAD unchanged: candidates/subset/prepared-key33pad-8d07.patch and submission-note-key33pad.md9730B;13 zero-spill native/host,unchanged promoted device image. Patch SHA2560032f2431fa298e2e121e25624734d8ff271f45a4ef4ec34c32f62c433d8dc84. No KH16 or submitted second-SHA32PAD in waiting source.

NEW WAITING PINNING: QSB_CG_NORM_IFMA=1, final canonical correction only in CPU IFMA fnorm. Replace t0+=(0-x)&C with QI_LO(t0,x,C), where unchanged exact comparison gives x in{0,1} and C=0x1000003D1; x*C<2^33 so the52-bit low product is exact. All comparisons,carries,masks,outputs and callers unchanged. No submitted KEY33PAD,closedsecond-SHA32PAD,FSEL3,PACK2,split45,VLSHA,square,GPU/controller changes. Independent adaptation of live normalization code.
Scalar model20010 legal limb vectors below2^62 matched old/new exact limbs and big-integer modulo p; x0 in20005 cases,x1 in5 boundary cases. NOT IFMA execution. Actual-source GCC13.3/O3 fnorm wrapper: vpmadd52luq1->2,vpaddq9->8,vpsubq1->0,vpand12->11,vpxor1->0;vmovdqa7 unchanged;total static vector sites53->50,stack-reference sites0 both. Fewer sites do not prove speed; added IFMA latency/port contention can hurt.
Native/host CUDA12.8.93 exit0;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Note9877B,no local runtime/gain/promotion claim.
Patch gpu-lab/prepared/norm-ifma-8d07.patch SHA2562b97b97c61d7a36d7c4e10889250cc929b50372aa5b668518b1c04f737ceb495; note gpu-lab/submission-note-norm-ifma.md; evidence gpu-lab/prepared/norm-ifma-evidence.json. Recovery omits note/carrier: sync live,apply,copy note,regenerate. Current pinning execution tree holds waiting NORM_IFMA,not submitted KEY33PAD. Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent; no new donor import or speed claim.

One own active per track; tracks concurrent; MLX independent. NEVER CANCEL. Reassess live tip,result,overlap/blacklists and fresh own queue before fire; rebuild moved source. No identical/noise retries or local GPU/targetCPU execution claims.

---

# Current status — 2026-09-28 20:04 UTC

This header supersedes older active/waiting labels. Live source both tracks remains8d07d3ebad41a017dfaa5906b164f883a9b59348. Pinning best1008206828/kaankolcu; subset best708411009/jacklightChen.

Pinning FSEL3 70db1d25 naturally REJECTED989496512 at19:26:54UTC,verified=true,141670 hits,elapsed1201.0291. Exact FSEL3-only package CLOSED; no retry.
NEW pinning246a0544-b94c-482f-8b80-2605485d86c1 submitted20:00:48UTC from fresh8d07 after empty own queue; VALIDATING in final refreshed query. Isolated CPU SHA32PAD second-hash specialization in z_shani_2. Native/host passed again;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Archive gpu-lab/prepared/sha32pad-submitted-246a0544.patch and gpu-lab/submission-note-sha32pad-submitted.md are SUBMITTED, not waiting. Never cancel/duplicate.

Subset372154a4-3ead-43c7-b6cc-1b43fa6dd4bd SHA32PAD remains VALIDATING. Waiting subset KEY33PAD unchanged: candidates/subset/prepared-key33pad-8d07.patch and submission-note-key33pad.md9730B;13 zero-spill native/host,unchanged promoted device image. SHA2560032f2431fa298e2e121e25624734d8ff271f45a4ef4ec34c32f62c433d8dc84. No KH16 or submitted second-SHA32PAD in waiting source.

NEW WAITING PINNING: QSB_CG_KEY33PAD=1, exact compressed33-byte-key padding only in pub_hash8_shani_wm. cg_sha.h template shani_compress2_impl<PAD33> preserves generic false wrapper; true loads W8 unchanged,fixes W9..14=0,W15=264,omits zero align/add and identity msg1 at group3. Word-major key-hash call only, used by existing IFMA/AVX2 EC SHA-NI paths; row-major generic path unchanged. No submitted second-SHA32PAD,FSEL3,PACK2,split45,VLSHA,square,GPU/controller changes. cpu_cogrind3.h original promoted.
Structural model2052 messages with both parity prefixes: actual grouped macro ordering generic/specialized64-word schedules matched recurrence and full scalar digest/hashlib; NOT SIMD execution. Actual function/header GCC13.3/O3 sites:msg1 24->22,palignr25->23,paddd58->56,movdqa113->109;msg2 remains24,rnds2 remains64;stack-reference sites13->3. Generic wrapper body identical after label normalization. Static code checks, not runtime/timing.
Native/host CUDA12.8.93 exit0,15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Note9563B; no measured gain/promotion claim. Can be immaterial when controller chooses another mode.
Patch gpu-lab/prepared/key33pad-8d07.patch SHA25644334c8fa91dfcbd64dcf3439b90988d3bfafae72470a90bb3d2d64b2d27111a; note gpu-lab/submission-note-key33pad.md; evidence gpu-lab/prepared/key33pad-evidence.json. Recovery omits carrier/note: sync live,apply,copy note,regenerate carrier. Current pinning execution tree holds waiting KEY33PAD, not submitted second-SHA32PAD. Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent. Independent adaptation of live pinning code; fixed-padding observation shared with terrapinelf/subset lineage, no donor speed claim.

One own active per track; tracks concurrent; MLX independent. NEVER CANCEL. Reassess live tip,result,overlap/blacklists and fresh own queue before fire; rebuild moved base. No identical/noise retries,local GPU or target CPU execution claim.

---

# Current status — 2026-09-27
Both Bitcoin tracks are active, one own validation per track. MLX is independent. Never cancel.

Live promoted source: f0e453daaf8b1af848e0bf4afd42fb730018c041.
Subset best 691630437 / kshitij-hash d052bc3d. Pinning best 995329477 / cefika 54ca2f74.

Subset 49f1ab79-c0e9-4723-828b-85d592210957 naturally rejected at 693254524, updated 12:09:08 UTC. It beat the live score by 0.2348%, but missed the required 1% promotion margin. Verified=true, elapsed1201.8168,99321 hits. This does not establish repeatable gain; no identical retry.

NEW subset 9d56c6fb-8e8b-43fc-abdf-774fb631ef56 submitted and validating. Base freshly synchronized f0e453d, live best unchanged, own subset queue empty before fire. Mechanism: v3 cached SHA schedules for the three floating host producers, composed with the previously tested r7 CPU lane. Keeps original spinning waits/main-core reservation and unchanged GPU code. Producer header is byte-identical to ercumentyildirim donor3b4fce1213a41ab5e2e96d7f038fdd88a07f2878 (a141df2b); donor's published score696429794 and component evidence are confounded and not claimed as this candidate's performance. Credits terrapinelf ercumentyildirim i34-9 Ryun1 Meganpark980320 kshitij-hash fkiene.

Full native carrier build and standard host nvcc build exit0.13 native zero-spill records. Cubin91948fc251250a6607615c28327b62892a26cc7ef1d62047eb9e42148fdb98b1 byte-equals frontier.3 digest LTC64B loads. tree.cu unchanged. Note9552 bytes. No local GPU/runtime/score claim; actual GPT(exact variant not exposed)/Codex metadata.

Archive: candidates/subset/prepared-r7-v3-f0e453d.patch and candidates/subset/submission-note-r7-v3.md. These are SUBMITTED records, not a waiting candidate. Older r7 patch is also submitted; do not replay.

Pinning07af5750-deb9-450f-91cc-e759f5ee4a5b remained validating at this check. Its busy-counter patch/note are archived on the pinning branch. Do not duplicate or cancel.
BOTH replacement candidates are now compile-qualified and waiting on f0e453d. No local GPU runtime or performance measurements. Do not submit while that track's current own validation is active. Recheck current results/overlap, sync then-live tip and rebuild if changed before fire.

Pinning waiting: paired 128-bit prepare state stores, alone on promoted source. Import only qsb_st_state_v2 and qsb_po_store from i34-9 public5b7d88f9377443b74d77519eb943c4e391941751 (57c97154). Four wide stores replace eight scalar stores, same addresses/data/evict-last policy. No busy counters, register roots, ring/slots changes, carry cuts or GREEN changes. Full native and host builds exit0;14 zero-spill records; prepare128 registers/finish64;5 prepare LTC64B loads. Native disassembly confirms four STG.E.128 stores. New cubin d314e41b12353a5dfe179f388f1fb87e7834fd066d1a7bde13b237e17ceef8a0 (391072bytes). Address model passed N=64,128,256, including active N=128; this is not CUDA validation. Patch gpu-lab/prepared/vector-state-f0e453d.patch SHA2561329d279b5f80939497fea791f7d1812cc5423c0258ca5dbce2b2359e23648a1. Note gpu-lab/submission-note-vector-state.md (7509bytes). Credits i34-9 DPZZxlz cefika terrapinelf ercumentyildirim hybridnoise. Public donor's broader package scored954584203 and DPZZxlz broader stack989702157: disclosed confounding, no promised gain. Reassess competitor81221dd9 separately; that is cache-window cap, NOT this package.

Subset waiting: weighted CPU inversion prefixes on the adapted r7 lane, with original promoted producer header, spinning waits and main-core reservation. ec8_window/ec8_final_cf weighted branches from donor3b4fce1 only; keep original L1 prefetch, table geometry, workers and diagnostic fields. No v3 producer schedule cache in this waiting package (that is the active submission), no9-window table, no L2 prefetch retune. Weighted prefix moves numerator multiplication to the forward pass, shortens the backward slope dependency and avoids TY inter-pass storage, retaining field helper arithmetic and guards. Python modular identity model400 chains passed, NOT C++/GPU test. Host/full carrier builds exit0;13 zero-spill records; GPU cubin remains91948fc251250a6607615c28327b62892a26cc7ef1d62047eb9e42148fdb98b1,3 digest LTC64B loads. Patch candidates/subset/prepared-weighted-f0e453d.patch SHA2567f0617e380e062a2d436cb08b6584db2cdc54f2ee4ce9ba9bdc0640e06771500. Note candidates/subset/submission-note-weighted.md (9462bytes). Credits terrapinelf jacklightChen ercumentyildirim i34-9 Ryun1 Meganpark980320 kshitij-hash fkiene.

Both complete waiting patches include their public submission note. Execution worktrees currently contain these waiting sources on f0e453d; submitted source is separately archived. Avoid applying note twice or confusing historical SUBMITTED patches with these waiting patches. Native ptxas logs /tmp/tmp.04ecGghfWU (pinning) and /tmp/tmp.a8ITdAyJyn (subset), host logs /tmp/pinning-vector-host.log and /tmp/subset-weighted-host.log. Exact prior build evidence carries over only while source/base remain identical.

Closed pinning: GREEN24 958188986; ring6 950985831; dualroot953239579; RegisterRoots/WarpInverse/CyclicField combinations; PMIX12 warp replay draft dropped. Closed subset: paired-SHA ALU/full unroll, prep overlap, split verify, flag sweeps, chain-loop unroll/spills, GPU affine batch chain. A scored rejection below tip closes its exact approach; elapsed classes never justify identical retries.

Before edits/submission save delta, yukon sync --force, confirm live base, reassess/rebuild if moved. Only candidates/<track>/ executable changes, no harness/measurement changes, no binaries/stamps. Notes>=5KiB, actual attribution and proper coauthors. No GPU spend. Fetch explicit fork refs before connector commits and force:false updates; sync rewrites origin to upstream. Only designated branches.


## Historical session log (current status above supersedes older queue and slot policies)

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

**Note:** model switched mid-session from Claude Opus 5.5 to Claude Sonnet 5.

| `6e8b78f6` | 64Ki sub-batches (16 MiB ring) + L2 discard | e892e6e | cancelled | | | cancelled before scoring (directionally inconsistent with root-latency hypothesis below) |
| `0c8b0ffd` | QSB_SUBRING 4->6 (deepen sub-batch ring) + L2 discard | e892e6e (979.22M) | pending | | | rationale: ring-depth curve (terrapinelf: depth3 -2.6% vs depth4), L2-window insensitivity, jacklightChen's a6e67fd4 (root-kernel-only swap) scoring 982.6M all point at root-inversion latency as the bottleneck, not L2 capacity |

| `0c8b0ffd` | result | e892e6e | 913,807,983 | 1200.98 (slow) | 130,828 | rejected; slow-class run, inconclusive (within the 902-926M slow-class noise band for any source) |

**Field converging near the bar (checked before next submission):** three other unpromoted submissions on this frontier scored 977-988M with three different mechanisms, none clearing +1%: jacklightChen `a6e67fd4` (982.6M, replaced fused root kernel with register-tree/cyclic-field inverse), ercumentyildirim `6cf007af` (987.1M), terrapinelf `e9ac8d73` (988.6M, closest yet -- changed QSB_PMIX12 16->32, QSB_PMIX12_WARP 1->0 (block-uniform), QSB_PMIX12_N 2->1; also reverted the register-tree root kernel back to plain fused roots). PMIX12 controls the GLV12-P warp-mix ratio (trades DRAM gathers for compute); the frontier's own comment says per-warp spreading (WARP=1) exists specifically for SM-occupancy balance, which terrapinelf's near-miss gave up.

| `cf6ce87a` | QSB_PMIX12 16->32, QSB_PMIX12_N 2->1, QSB_PMIX12_WARP kept at 1 (frontier's per-warp spreading, at terrapinelf's near-miss ratio) | e892e6e (979.22M) | pending | | | tests whether per-warp spreading recovers the gap between terrapinelf's 988.6M and the ~989.0M bar |

| `cf6ce87a` | result | e892e6e | 916,968,681 | 1201.03 (slow) | 131,286 | rejected; slow-class, inconclusive (3 of last 4 submissions landed slow-class) |

**Pivot: building on jacklightChen's register-tree roots instead of hand-rolling.** Given the runner-class lottery is making it hard to test hypotheses cleanly, and RegisterRoots.cuh/WarpInverse.cuh/CyclicField.cuh/PrefixCyclicField.cuh are dense unfamiliar warp-shuffle field code I can't safely modify without a GPU, switched strategy: layer my one already-measured-safe change (L2 discard) onto jacklightChen's `a6e67fd4` (982,598,502, the strongest validated base on this frontier) instead of re-deriving their mechanism myself.

| `46071542` | jacklightChen's a6e67fd4 (register-tree root inverse, 982.6M base) + QSB_L2STATE bit 2 (finish L2 discard) | 73b24233 (982.6M) | pending | | | coauthor: jacklightChen. Tests whether the two independent mechanisms stack. |

| `46071542` | result | 73b24233 (982.6M) | 949,063,679 | 1201.55 (fast) | 135,940 | rejected; REAL regression (-3.4% vs same-class 982.6M base), L2 discard does NOT stack cleanly with register-tree roots -- orthogonality assumption was wrong |

**Corrected approach:** since L2-discard-on-state (memory-address orthogonality) failed to transfer to the register-tree base, tried a mechanism that's orthogonal by *code path* instead: PMIX12 operates entirely within prepare's P-decode, before any candidate reaches root inversion.

| `f0de3f0e` | jacklightChen's register-tree roots (a6e67fd4) + terrapinelf's EXACT PMIX12=32/block/N=1 recipe (94744cc7) -- the two largest independent near-frontier gains, combined for the first time | 73b24233 (982.6M) | pending | | | coauthors: jacklightChen, terrapinelf. Optimistic estimate ~991.7M if independent (multiplicative); could also regress like 46071542 did |

## FRONTIER PROMOTED: 979,222,732 -> 995,329,477 (+1.64%)

While `f0de3f0e` was queued, cefika's `54ca2f74`/`f0e453d` was promoted (coauthors DPZZxlz, terrapinelf, ercumentyildirim, hybridnoise; jacklightChen NOT included). Confirms: (1) terrapinelf's exact PMIX12=32/block/N=1 recipe IS a real, large win -- it's in the winning tree, validating my earlier hypothesis. (2) A related-but-distinct L2STATE mechanism (bits 1|8|1024, DPZZxlz PR #1891: evict_last store policy + a differently-timed discard) -- NOT the same bit-2 discard that regressed on the register-tree base. (3) QSB_GT_BATCH=12 (hybridnoise): startup-only batched gtable build, doesn't affect steady-state score. (4) NEW: native-carrier dispatch for the root-inversion kernel itself (QK_RF) -- a lever nobody had exploited before this.

| `f0de3f0e` | result | 73b24233 (982.6M) | 918,445,502 | 1200.98 (slow) | 131,492 | rejected; slow-class, inconclusive (obsolete base regardless -- new bar is ~1,005.3M) |

**Re-integrated register-tree roots onto the NEW frontier** (rewrote the 3-way selector to also preserve f0e453d's new QK_RF carrier dispatch, which didn't exist when jacklightChen wrote their original integration).

| `02a847b9` | jacklightChen's register-tree roots layered onto f0e453d (995.3M), preserving its new QK_RF carrier dispatch as fallback | f0e453d (995.33M) | pending | | | coauthor: jacklightChen. Needs ~1,005.3M to promote. Tests whether register-tree roots compose with the actual strongest known base, after regressing (-3.4%) against an older/weaker combination |

| `02a847b9` | result | f0e453d (995.3M) | 26,201,910 | 1200.25 | 3,749 | rejected; CORRECTNESS BUG not perf regression -- candidates_self_reported ~1.21T (normal) but verified_hits only 3,749 (~72,500 expected) -- register-tree computed wrong roots for most sub-batches on this base; host OpenSSL gate correctly dropped every wrong candidate, no bad hit ever published |

**Register-tree investigation CLOSED.** Both terrapinelf (9b633d47, gave register-tree its own QsbCarrier.h native-dispatch entry, more thorough than mine) and jacklightChen's own new attempt (654f05fc) independently tried the same combination around the same time. Neither promoted: terrapinelf 991,732,208 (-0.36%), jacklightChen 859,419,979 (-13.6%). Even correct integrations by more careful hands (including the mechanism's own author) show no net gain. Register-tree roots do not compose with this frontier's current mix -- not pursuing this further this session.

**Pivoted to a clean, safe, orthogonal lever:** re-testing QSB_SUBRING (sub-batch ring depth) properly on fast-class hardware, since my only prior test (0c8b0ffd, on the old frontier) landed slow-class and was inconclusive. This frontier's new native root-kernel carrier dispatch (QK_RF) may have changed whether ring depth still matters.

| `eacbd337` | QSB_SUBRING 4->6 on the 995.3M frontier | f0e453d (995.33M) | pending | | | clean single-variable retest; no register-tree code involved |

## 2026-09-27 continuation

See STATUS.md for live queue state, toolchain checks and the prepared GREEN24 cut. Account-wide one-in-flight and no-cancellation rules remain in force. The candidate is not ready for automatic dispatch; the full carrier-script gate remains blocked.

## 2026-09-27 build-checked waiting candidates

This update supersedes the old carrier build-blocker and empty-backlog notices. GREEN24 2402ebc0 remains validating; ring6 eacbd337 rejected950985831 and is closed. Both frontiers remain f0e453d (pinning995329477, subset691630437). Independent-root/ring4 pinning and isolated-r7-CPU subset candidates now have successful host/native builds, zero-spill native logs, frontier-identical cubins and honest notes over5KiB. Neither was run locally. See STATUS.md for exact patches, hashes, credits and dispatch rules. Another own MLX validation was discovered, so the shared account slot is not free even if pinning finishes first. No submission or cancellation was performed this run.

# Current status — 2026-09-27 10:29 UTC

This section supersedes all historical queue and waiting-candidate statements below.

- Subset49f1ab79-c0e9-4723-828b-85d592210957: validating, isolated r7 CPU lane, submitted09:04UTC on f0e453d. No score yet.
- Pinning62d66afd-484c-41f9-8e32-82d6c3085130: naturally rejected953239579 at09:58:42UTC, below995329477. Independent-root-queue approach CLOSED; do not replay saved dualroot patch.
- GREEN24 2402ebc0 rejected958188986; ring6 eacbd337 rejected950985831. Both closed.
- Both live frontiers unchanged and freshly Yukon-synced to f0e453daaf8b1af848e0bf4afd42fb730018c041: subset691630437/kshitij-hash, pinning995329477/cefika.
- Both previously prepared patches have been SUBMITTED. There are currently NO qualified waiting replacements. Historical ready notes below are archival, not dispatch instructions.
- User explicitly permits one active submission PER BITCOIN TRACK. MLX does NOT block Bitcoin. Never cancel any validation.
- Latest user request: prepare next candidates once both submitted results land; subset still pending. Then start from then-live promoted tip, use both results, recheck tip before submission and rebuild if moved.
- Submitted worktree deltas preserved in /tmp/pinning-submitted-1028.patch and /tmp/subset-submitted-1028.patch (plus pinning note), then sync reset execution source to frontier. Saved fork patches remain available as historical records; do not reapply closed/pending packages for another submission.
- No new submission, cancellation, candidate code change or GPU run this check. Status-only persistence. Compile-only qualification remains authorized.


# Current dispatch — September27 12:06UTC

Latest user request explicitly says submit pinning and subset; do not wait for both prior results before advancing a free track. One own submission per track, concurrent Bitcoin tracks authorized, MLX independent. Never cancel.

Pinning07af5750-deb9-450f-91cc-e759f5ee4a5b submitted successfully and validating. Parent freshly synchronized f0e453daaf8b1af848e0bf4afd42fb730018c041; live best995329477/cefika. Mechanism: padded single-writer busy-time counters and local accumulation plus relaxed store after each CPU batch. Based on pochita0 a839900a public mechanism, but isolates busy-time publication; retains stage timing/profiling and all budget controller policy. Coauthors pochita0 ercumentyildirim terrapinelf cefika DPZZxlz hybridnoise. Host and full native builds exit0,14 zero-spill records, cubin625c22c4298276a77064a5570a38821e8f97a7f6620596f961e945708d5a9bbd matches frontier. C++16-writer/1.6million-update test passed distinct cache lines, monotonic snapshots, exact total80012800000 and modular wrap. No runtime GPU or performance claim.
Archive patch gpu-lab/prepared/busy-counter-f0e453d.patch and note gpu-lab/submission-note-busy-counter.md are SUBMITTED records, not waiting packages.

Subset49f1ab79-c0e9-4723-828b-85d592210957 still validating at final dispatch check. No duplicate subset submitted. Subset frontier691630437/kshitij-hash, same sourcef0e453d. Both tracks now have one active submission. No qualified waiting replacements yet.

Build recovery: local CUDA ptxas executable was truncated and segfaulted even for --version. Downloaded cuda-nvcc-12-8_12.8.93-1_amd64.deb from NVIDIA ubuntu2404 repo into /tmp/cuda-nvcc-restore.deb. Extracting restored it; touch the extracted ptxas to ensure persistence across runtime snapshots. Repair and build in the same exec if needed. Native and standard builds then passed. This is resolved; do not report as remaining blocker. CUDA carrier fallback remains exact.

Closed: GREEN24, ring6, dualroot62d66afd953239579, register-tree combinations and previous subset blacklist. No resubmission of old prepared patches. Actual GPT(exact variant not exposed)/Codex metadata used. Only candidate-directory source edits. No cancellation or GPU spend.


## Session gap (~11h, 03:49-14:39 UTC): caught up

Another agent (harness "Codex", model "GPT") shares this Yukon account and submitted three more candidates during the gap, all on f0e453d, none promoted: `2402ebc0` 958,188,986 (24-SM finish partition), `62d66afd` 953,239,579 (independent root queues), `07af5750` 927,440,828 (CPU busy-time publication). `eacbd337` (my SUBRING=6) resolved at 950,985,831, elapsed 1201.0178s -- borderline/slow-class, SECOND inconclusive draw for ring-depth; dropping that hypothesis rather than retrying a third time.

**Field bunching tighter under the bar:** ItlaStudent's `02c7dda3` scored 1,001,615,305 (closest yet, -0.4% short of ~1,005.3M) and jungjipdo's `971c3e35` hit 995,491,210. Neither promoted. ItlaStudent's tree is a full 110-file reorganization I couldn't safely parse/reproduce in time.

**Submitted `4385e740`:** clean single-variable retest -- QSB_PMIX12_WARP 0->1 (per-warp instead of block-uniform) at the frontier's own 1/32 ratio. My only prior attempt at this exact combination (cf6ce87a) landed slow-class and was inconclusive; nobody has published a clean fast-class measurement of per-warp spreading at this higher ratio.

| `4385e740` | result | f0e453d (995.33M) | 990,242,571 | 1201.61 (fast) | 141,845 | rejected; REAL -0.51% regression (fast-class, comparable to base) -- per-warp spreading is worse than block-uniform at the 1/32 ratio, closes the PMIX12-distribution question |

**New near-miss:** i34-9's `f7470c17` scored 998,903,437 (+0.36%, still short of ~1,005.3M), a bundle of 4 changes: QSB_SLOTS 4->3, a v2 state-store form, QSB_YOFF_Y1_CUT, and unfamiliar QSB_SUB_CHAIN_P/QY/QSB_SUB_SEED macros (definitions not visible in the fetched diff -- treating as unverifiable risk, not reproducing).

| `cff30dc4` | QSB_SLOTS 4->3 isolated from i34-9's bundle (host-only, carrier byte-identical) | f0e453d (995.33M) | pending | | | tests whether this one safe, fully-verified piece explains some/all/none of i34-9's gain |

| `cff30dc4` | result | f0e453d (995.33M) | 965,192,942 | 1201.53 (fast) | 138,248 | rejected; REAL -3.0% -- QSB_SLOTS 3 is negative alone |

## 2026-10-06 resync: frontier 1,036,462,054 (fkiene `12233735`, source `582a994`), closes 2026-10-07 23:00 UTC

The prepared `next-i34bundle-noslots` package was never submitted (the shared account's other agents kept the slot busy) and is now stale against two promotions (1,008.2M kaankolcu, 1,020.9M DPZZxlz, 1,036.5M fkiene). Dropped.

**Runner-tier analysis (all ~60 ranked runs since the record):**
- Three tiers. Top: elapsed ~1201.6-1201.9 s, self-reported ~1,040-1,052M/s. Middle: self ~1,018M (the unchanged record redrawn scored 1,007.1M / 1,010.4M). Throttled: elapsed ~1200.9-1201.1 s, self still ~1,040M but score capped at 855-885M whatever the source (verified/expected ratio ~0.83).
- Every top-tier run on the current lineage, from every solver, lands at 1,032.6-1,039.7M. Bar is ~1,046.8M (+1%). Poisson noise is ~0.26%, so luck can't bridge it.
- verified / (self x 2^-23) on top tier: ~0.986 for record-lineage geometry, ~0.992-0.995 with 2M host batches. Co-grinder off (i34-9 `d4fc39be`) dropped it ~0.7%, so the CPU co-grinder adds ~0.7% of hits.
- Ruled out by code reading: inline host gate starving the GPU (REFILL_BEFORE_GATE plus GPU-side event ordering keep ~5 batches queued), sequence-boundary drains (QSB_OVERLAP_SEQUENCES=1), early exit (harness enforces >= max_seconds minus tolerance), PK host-SHA startup (QSB_PK_ON=0 on the record).

| id | change | base | score | elapsed | hits | outcome |
|---|---|---|---|---|---|---|
| `4e8e3e0c` | QSB_SUB_FINE 1->0 + QSB_BATCH 4M->2M, SLOTS 5 kept (carrier byte-identical to ranked `960e87fb`) | 582a994 (1,036.46M) | pending | | | pairs the highest-self knob (960e87fb, 1,051.5M/s) with the best-ratio knob (580217f7, 0.9945) without jacklightChen's SLOTS 4 |
