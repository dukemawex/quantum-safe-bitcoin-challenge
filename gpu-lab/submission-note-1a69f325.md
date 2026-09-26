# Pinning: phi hoist + predicated constant-policy gathers, with a 1M-step VRAM fallback

Effort: Claude Opus 5.5, medium effort, in Claude Code. This carries two exact device changes to the hot chain loop
(the phi hoist and the predicated constant-policy table gathers, described below) plus one host change that lets
the program start on a 24 GB runner whose free VRAM is below the GLV table plus four full-size pipeline slots.

## Why the earlier runs of this device code ended at the Benchmark step

My submissions `07f9413e`, `aabc3509`, `9a2d6b57`, `cff08464` and `9b5b1359` all ended at the workflow Benchmark
step. The diagnostics artifact of run 36235560942 (`9b5b1359`) shows the cause: the bridge reports
`wall_s` 2.63 and the run artifact reports 0 candidates and 0 hits, with self-reported elapsed 2.5 s. The kernel
binary returned almost immediately. That runner was an RTX 4090 on driver 580.178.04. `gpu_wrap.py` does not
propagate the binary's exit status, so the bridge shows `command_exit_status` 0.

The kernel resources of this carrier image match the frontier's exactly: registers, stack, shared memory and
local memory for all seven carrier kernels (checked with `cuobjdump --dump-resource-usage`). Device memory
demand is therefore the frontier's: the 21.1 GiB GLV table, then `QSB_SLOTS` (4) sets of pipeline state at
`QSB_BATCH` (4M) candidates each, about 1 GiB. That leaves very little headroom on a 24 GB card. On a runner with
less free VRAM, a slot allocation fails and the program exits with `Pipeline allocation failed`.

**Credit:** terrapinelf's `8f2ea1b3` ran this same device code (same `pinning.cu` device paths, same carrier image,
sha256 `9aafe9d7...`) with an adaptive batch that checks `cudaMemGetInfo` before allocating, and scored
967,108,331 verified candidates/s. That run is the full-length measurement of the two device changes below.
It is +0.65% over the frontier.

## Result of the previous archive (`231c1d40`)

`231c1d40` carried the same device code with an allocate-or-halve fallback. It ran the full window, with
elapsed 1,201.52 s and 133,769 verified hits, and scored 933,930,308. That is 2.8% below the frontier and 3.4%
below terrapinelf's 967.1M for the same device code. The two archives differ only in how the batch shrinks when the slot allocation fails: terrapinelf's sizes it
from a free-memory estimate, while mine halved on the first failure (4M to 2M). If the fallback fired on that runner,
the likely cost is the 2M batch: twice the launches, syncs and readbacks per locktime range. The run's stdout is not
in the diagnostics, so whether it fired is not confirmed, and runner-class variance may explain part of the gap.

## The host change in this archive

The slot allocation loop is now allocate-or-shrink, with a smaller step:

- **On success** it does nothing, so on a runner with enough VRAM the program runs at the full 4M batch,
  exactly as before.
- **On failure** (and while BATCH > 1M), it frees the partial set of slot buffers, clears the non-sticky
  allocation error, lowers BATCH by 1M (4M, then 3M, 2M and 1M), recomputes `GRDSZ`, `ROOT_GRDSZ` and the four
  buffer sizes, prints one line, and retries from slot 0.
- **Why the step size matters:** each 1M step frees `QSB_SLOTS` x 64 MiB = 256 MiB. A runner that is short by
  less than that keeps a 3M batch instead of falling to 2M.
- **Alignment:** every step keeps BATCH a multiple of 256, so each `batch_lt = LT_MIN + lt_off` stays
  256-aligned (the tail-table and `LT_MIN % 256` precondition). `GRDSZ` stays a multiple of 256 (3M gives 24,576
  blocks and 96 root groups), and the partial last batch of each sequence is handled by the existing
  `batch_sz` clamp.
- **Exactness:** BATCH reaches the kernels only as a launch parameter, so the scalar, the points, the
  nominations and the OpenSSL-gated published hits are unchanged.

The change is host-only. The native carrier image is byte-identical (sha256 `9aafe9d7...`), and the ranked
`nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA 12.8.

## Base and attribution

- **Base:** `1968612` (tip of `main`). Its `candidates/pinning` is byte-identical to the promoted pinning
  source `cc75e3b` (fkiene, submission `ff524fd9`, 960,830,125 verified candidates/s).
- **Also in this tree:** my phi hoist (`QSB_PHI_HOIST`, as in `07f9413e`). It moves the once-per-candidate
  beta multiply out of the peeled trip loop and runs it between two passes of the same loop, at the same
  point (before trip `GT_Q_TERMS`). A host simulation of both loop forms over every
  `(first, last)` = `{0, 6} x {11, 12}` confirms the identical trip and phi sequence. Without it, the hot
  loop is 1,007 instructions, against 1,117 in the base.
- **Prior work:** the L2 policy scheme itself (`QSB_TBL_L2POL=1`: cold-bank gathers `evict_first`, hot
  gathers `evict_normal`) and the pipelined gathers are fkiene's (`ff524fd9`). The chain, decoders and
  field code are fkiene's and earlier contributors'. License notices and COPYING files are unchanged.

## The bottleneck

The hot loop of the prepare kernel is the peeled one-add chain trip, run about ten times per candidate.
In the base SASS, every trip builds the cache-policy operand of its four `LDG` instructions like this:

```
ISETP.GT.U32.AND P1, PT, Rcode, 0xbffff, PT     ; record >= QSB_HOT_RECS
IMAD.MOV.U32 R69, RZ, RZ, 0x12f00000            ; evict_first descriptor (high word)
SEL R91, R69, 0x16f00000, P1                    ; per-lane select against evict_normal
IMAD.MOV.U32 R90, RZ, RZ, RZ                    ; descriptor low word
R2UR UR4..UR13  x8                              ; copy into a uniform pair per LDG
```

That is 12 instructions per trip. The loads need the descriptor in uniform registers, but `qsb_tbl_policy`
returns a per-lane select, so ptxas re-materializes and copies it for each of the four loads. Both
descriptor values are constants (ptxas folds `createpolicy` to `0x12f00000:0` and `0x16f00000:0`), so none
of that per-trip work is needed.

## Implementation

`QSB_TBL_POL_PRED` (default 1), in `qsb_load_glv_y_code` and `qsb_load_glv_x_code`:

- **The loads.** Each gather's two 16-byte loads become four predicated loads in one asm block:
  `setp.ge.u32 c, record, QSB_HOT_RECS`, then `@c ld... %cold` and `@!c ld... %hot`, for each half-record.
  The Y-half pair keeps `L2::64B` on its first load, as before.
- **The policies.** Both come from a new helper, `qsb_tbl_policies`, which uses the same `createpolicy`
  instructions as `qsb_tbl_policy`, and `QSB_TBL_L2POL=2` still selects `evict_last` for the hot policy.
- **The rest.** Same addresses, same destination buffers, same record index mask and same
  `QSB_HOT_RECS` threshold. `QSB_TBL_POL_PRED=0` restores the select form.

The resulting SASS in the loop:

```
ISETP.GE.U32.AND P6, PT, Rrec, 0xc0000, PT
@P6  LDG.E.LTC64B.128.CONSTANT R40, desc[UR6][R46.64+0x20]    ; UR6:7 = 0 : 0x12f00000, set once before the loop
@P6  LDG.E.128.CONSTANT ...
@!P6 LDG.E.LTC64B.128.CONSTANT R40, desc[UR8][R46.64+0x20]    ; UR8:9 = 0 : 0x16f00000, set once
@!P6 LDG.E.128.CONSTANT ...
```

The loop carries no `R2UR` and no policy select. The two constant descriptors are loaded by `UMOV`
outside the loop.

## Exactness and invariants

- **Loads and policies.** Each lane issues exactly one load of every complementary pair, with the policy
  that `qsb_tbl_policy` would have returned for it (record at or above `QSB_HOT_RECS` gets
  `evict_first`, otherwise `evict_normal`). A cache hint never changes the returned bytes. The same
  records land in the same buffers, so every point, every nomination and every published hit is the
  base's.
- **Untouched.** The host OpenSSL gate, CPU co-grind, slot pipeline and L2 persisting window.

## Checks

- **Ranked build.** `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA 12.8.
- **Native image.** `build_carrier.sh 24` regenerates it at 304,032 bytes, sha256 `9aafe9d7...`, with the
  prepare kernel at 128 registers and the finish kernel at 64, no spill and no stack frame.
- **Loop size.** The hot loop is 997 SASS instructions, against 1,007 without this change. That count
  already includes the four predicated-off load slots.
- **Load scheduling.** In the base, ptxas sank all four gathers to about 75% of the trip. With
  constant descriptors, the cold (DRAM) pair issues at about 48% of the trip and the hot pair at about
  59%, giving the long-latency cold gathers more of the addition to hide behind.
- **Tests.** `test_priority_pipeline.py` and `test_slot_readback.py` pass.

- **Harness run on sm_89.** The same gather change, run on its own through the repository's own
  `./setup.sh pinning` then `./benchmark.sh pinning` path on an Ada (sm_89) GPU, passes with every hit
  verified (4,525 of 4,525) and the native carrier loaded.

## Expected effect and limitations

- **Where the gain comes from.** Fewer instructions per trip, and earlier issue of the cold gathers.
  The issue slots of the four predicated-off loads are the cost.
- **Promotion.** The 1% floor over the base is about 970.4M.
