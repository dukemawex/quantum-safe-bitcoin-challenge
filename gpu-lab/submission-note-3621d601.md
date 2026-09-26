# Pinning: pubkey SHA-256 back on the ALU pipe (-11% finish instructions), on the 979.2M green pipeline

Effort: Claude Opus 5.5, medium effort, in Claude Code. This archive is the promoted frontier
(terrapinelf's `0c9471ef`, 979,222,732 verified candidates/s, main `e892e6e`) with three compile-time
switches changed. Each switch already exists in the frontier source, each keeps the exact device
arithmetic and publication gate, and each has at least one zero-or-positive local measurement published
by the solvers who wrote it. None of them is in the promoted configuration. The bet is that small
positive effects stack on the ranked runner. The official run is the measurement; no local GPU was used
for this archive.

## Base and attribution

- **Base:** `e892e6e` (tip of `main`), `candidates/pinning` byte-identical to the promoted `0c9471ef` source
  apart from the lines below and the regenerated native carrier.
- **GPU pipeline:** fkiene and contributors (PR #1732, with i34-9 and Ryun1), the predicated policy gathers and phi hoist
  (dukemawex, PR #1775), the green-context sub-batch pipeline and fused roots (ercumentyildirim, PR #1788),
  and terrapinelf's integration and CPU `xlarge` table. The CPU co-grind framework descends from
  Meganpark980320, and its v2 arithmetic and SHA paths are ercumentyildirim's. License notices and COPYING
  files are unchanged.

## The three changes

1. **`QSB_SHA_FMA_ROT` from 8 to 0 (pubkey SHA-256 in the finish kernel).**
   - **What it does:** with 8, the two schedule-sigma logical shifts of every message-schedule word are
     issued as `IMAD.HI` by a power of two on the FMA-heavy pipe. With 0 they are ordinary shifts.
   - **Evidence:** ercumentyildirim's PR #1788, the source of the sub-batch pipeline itself, shipped
     `QSB_SHA_FMA_ROT=0` as part of its measured +1.26% set (+1.05% for the pipeline alone).
     terrapinelf's frontier note says the value 8 was kept only "so the pipeline result is easier to
     interpret", not because 0 measured worse.
   - **Mechanism:** the RTX 4090 runs at its software power cap for the whole ranked window, so energy per
     candidate sets the clock. A shift costs less energy than a 32x32 multiply-high. In the rebuilt finish
     kernel the count of `IMAD.HI` falls from 174 to 4 at an identical total of 4,040 instructions.
   - **Exactness:** `x >> k` equals the high word of `x * 2^(32-k)` for every x, so the digest is
     bit-identical.

2. **`QSB_L2STATE` from 1 to 3 (bit 2: the finish kernel discards consumed state lines).**
   - **What it does:** after a block's recovery has consumed its four state planes, lanes 0/8/16/24 of each
     warp issue `discard.global.L2` on their group's four 128-byte lines. The dead lines then leave L2
     without a DRAM write-back and stop competing with the next sub-batch's state and the hot table bank.
   - **Evidence:** terrapinelf measured +0.051% at matched temperature and SM clock, with exactly the
     same first 4,504 hits, and left it out only as too small to report alone.
   - **Exactness:** the discard runs only after every lane of the 8-lane group has loaded its entries. A
     lane that exits early leaves its lines to the normal write-back. No value anyone reads changes: the
     ring slot is rewritten by its next prepare before any read.

3. **`QSB_GREEN_SHARED` from 8 to 12.**
   - **What it does:** 12 of the finish partition's 20 SMs, instead of 8, are also available to
     prepare.
   - **Evidence:** terrapinelf measured +0.62% in a cooler, higher-clock first arm and +0.040% in an
     equal-clock reversed arm, with identical hits. That is no reliable gain, but no loss either.
   - **Why it may help more here:** change 1 makes the finish kernel cheaper per candidate. That leaves
     finish-partition slack, which the shared SMs can give back to the prepare kernel, where about 80% of
     the energy goes.
   - **Correctness:** partition layout changes where blocks run, not what they compute.



## Result of the previous archive (`f6f1c0fb`)

The three switches without this change scored 974,116,490, with 139,529 verified hits over 1,201.55 s.
That is -0.52% against the frontier's 979,222,732, inside the combined hit-noise and runner-class spread.
So those three are roughly neutral on the ranked runner. This archive keeps them and adds the one change
with a large static effect: 440 fewer instructions per candidate in the finish kernel.

## The main change in this archive: `QSB_SHA_FMA_ADD` from 1 to 0

- **What it does:** with 1, every two-input add of the pubkey compression is emitted as
  `mad.lo.u32 d, a, one, b`, a multiply by a runtime 1 that ptxas cannot fold. That moves the add onto the
  FMA-heavy pipe, at a cost of three extra instructions per round. The switch's own comment calls it a
  pipe-balance experiment, from before the green-context split.
- **Effect in the rebuilt native image:** the finish kernel falls from 4,040 to 3,600 SASS instructions
  (-10.9%). Its `IMAD` multiply-by-one count falls from 1,148 to 30, and its registers from 64 to 62.
- **Why it should help now:** the RTX 4090 sits at its software power cap for the whole ranked window, so
  energy per candidate sets the clock of every SM. The change removes 440 instructions per candidate, and
  turns about 1,100 multiplier operations into three-input integer adds. Pipe balance mattered when finish
  shared SMs with the FMA-bound prepare kernel. Under the green split, finish runs mostly on its own
  partition, where fewer instructions and less energy both count.
- **Exactness:** `a*1 + b = a + b mod 2^32`, so every digest word, and every hit, is bit-identical.
- **Stacking:** this is on top of the previous archive's three switches (`QSB_SHA_FMA_ROT=0`, finish L2
  discard, 12 shared SMs), which are kept.

## Checks

- **Ranked build:** `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA 12.8.
- **Native image:** `build_carrier.sh 24` regenerates it at 338,976 bytes, sha256 `c272157d...`.
  - Prepare is at 128 registers and finish at 62, with no spill and no stack frame.
  - Prepare's hot chain loop is unchanged (997 SASS instructions).
  - The finish kernel has 3,600 instructions (4,040 in the frontier), with four `discard.global.L2`
    added.

## Expected effect and limitations

- **Size:** each effect is small, around +0.05% to +0.3% by the published measurements. The combination has
  not been measured together, and the three may interact through the SM split.
- **Promotion:** it needs about +1% over the 979.2M frontier (about 989.0M). Hit-count noise near this
  rate is about 0.27% one standard deviation, and runner class moves scores by more than that.
- **What the run will show:** whether the finish-side energy reduction and the partition change give
  measurable gain on the ranked r5 runner. If the result is flat, the next step is to measure the finish
  partition's utilisation directly, not to tune these switches further.
