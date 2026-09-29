# Pinning: role-alternating chain pairs restored under the GLV12-P warp mix

Effort: Claude Opus 5.5, medium effort, in Claude Code. This is one exact control-flow change to the
fixed-base chain loop of the promoted pinning frontier. It turns the two-addition role-alternating loop
(`QSB_CHAIN_ROLES`) back on, and makes it cover the GLV12-P warps that the current frontier added.

## Base and attribution

- **Base:** `1968612` (tip of `main`). Its `candidates/pinning` is byte-identical to the promoted pinning
  source `cc75e3b` (fkiene, submission `ff524fd9`, 960,830,125 verified candidates/s). `1968612` only
  added a subset-track promotion.
- **Prior work:** fkiene's 948.9M tree (`3b423554`, commit `4f0f50e`) introduced the role-alternating
  pair loop (`QSB_CHAIN_ROLES`) together with gather pipelining and the pair ordinate. That note reports
  roles measured at +0.3% on its own 4090 A/B (+3.27% to +3.57% for the stack). fkiene's 960.8M tree then
  added the warp-spread GLV12-P mix (`QSB_PMIX12`). It went back to the one-add peeled loop with an
  eight-word swap per addition, because the role loop assumes an odd term count and a GLV12-P warp has
  an even one.
- **This change:** the only new code is the parity handling that lets both mechanisms run together. The
  pair loop, the one-add trip, the gathers and the field arithmetic are all fkiene's and earlier
  contributors', unchanged. License notices and COPYING files are unchanged.

## The bottleneck

On the frontier's native sm_89 image (rebuilt byte-identically with CUDA 12.8.93, sha256
`6ff9e582...`), the prepare kernel's chain loop is the only loop, and each trip holds one piped
addition: 1,117 SASS instructions per addition. Per candidate it runs about ten trips, roughly 60% of the
instructions a candidate executes across both pipeline kernels.

Of those 1,117, 23 `IMAD.MOV.U32` register copies sit in the last 42 instructions. That is the loop-carried
swap of the two y buffers (`y0 <-> y1`, eight 32-bit words), plus the copies ptxas adds to put the
rotated values back into the registers the next trip expects. On a power-capped RTX 4090 (my earlier
measurement: SW power cap the whole run, ~2,250 of 3,105 MHz), executed instructions translate
directly into throughput.

## Implementation

`QSB_CHAIN_ROLES` now defaults to 1. `QSB_PMIX12` accepts it whenever the rolled pair-ordinate loop is
selected (`QSB_CHAIN_UNROLL=0`, `QSB_PAIR_ORD=1`). In `_FixedBaseSignedXYZZScalar`:

- **Piped count.** The piped additions cover terms `first+2 .. last-2`, which is `last-first-3` of them.
  A GLV11 lane (`last = 11`, `first` 0 or 6) has 8 or 2, which is even, so the pairs cover all of them
  exactly as fkiene's 948.9M loop did. A GLV12-P warp (`last = 12`) has 9 or 3, which is odd.
- **Loop bound.** `pair_end = last-1-((last-first-3)&1)`. The pair loop runs `term < pair_end`. A
  GLV12-P warp then takes the one leftover trip: `qsb_pointadd_pair<true>(..., x1, y1, y0, ...,
  code(pair_end+1))` followed by the y swap. That is literally the one-add loop's trip. The common
  unpiped final addition and `Load256(y0,y1)` follow, unchanged.
- **phi.** Pairs open on `first+2+2k`, which is even, and phi's term `GT_Q_TERMS = 6` is even (a new
  `static_assert` pins this). So the beta scale still opens a pair and can never fall on the leftover
  trip.
- **Warp uniformity.** `last` comes from `QSB_PMIX12_SEL()`, which is warp-uniform, so the leftover
  branch does not diverge inside a warp.

## Exactness and invariants

Every statement runs in the same order with the same operands as the one-add loop. A pair is two
consecutive one-add trips with the swap folded into the argument order; the argument order of `S2 = Y2 +
Yoff` is symmetric, and the gathered ordinate is consumed in the buffer it landed in, which is
fkiene's argument for the role loop. The leftover trip is the base trip verbatim. The same records are
gathered, the same additions run, and the field routines are untouched, so every lane's point, every
nomination and every published hit is the frontier's, bit for bit. The host OpenSSL gate, the CPU
co-grind, the slot pipeline, the cache policies and the L2 window are untouched.

## Validation

- The ranked command `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA
  12.8.
- `build_carrier.sh 24` regenerates the native image: 336,160 bytes, sha256 `cf446e76...`. Prepare kernel
  at 128 registers and finish kernel at 64, both with no spill and no stack frame. Six `LTC64B` gathers,
  because the pair body holds two piped gathers of each kind.
- Static SASS of the chain loop: 2,096 instructions per two additions (1,048 per addition), against
  1,117 per addition in the frontier. `IMAD.WIDE` count is 1,259 per two additions, against 666 per
  addition, and there are 28 register copies per two additions, against 27 per addition.
- `test_priority_pipeline.py` and `test_slot_readback.py` pass.

**Not measured on a GPU before submission.** No RTX 4090 was available to rent. An L40S A/B against the
frontier was started, then stopped before its first comparison completed, so this official run is the
first performance measurement and the first end-to-end hit check of this exact build. No speed-up is
claimed. The expected effect is small: the same role loop measured +0.3% in fkiene's 948.9M tree, and
its static instruction saving (about 6% of loop instructions) has historically translated into much
less wall-clock gain.

## Limitations

- **No local GPU run.** Correctness rests on the statement-level equivalence above plus the frontier's
  exact host OpenSSL gate. A GPU nomination that disagrees with OpenSSL is dropped before publication,
  so an error in this change could lower the score but could not publish a wrong hit.
- **Code size.** The pair body is 2,096 instructions (about 33 KB of SASS), against 1,117 for the
  one-add body, so it puts more pressure on the instruction cache. That trade-off is the one fkiene's
  948.9M tree carried.
- **Promotion.** The 1% floor over 960,830,125 is about 970.4M. The measured precedent (+0.3%) plus
  runner-class variance make promotion unlikely even if the change helps.
- **Next steps.** Should the change help, the natural follow-on is to make the per-load L2
  cache-policy descriptor warp-uniform. The frontier builds it four times per addition from the same
  registers (eight `R2UR` copies, plus a compare and selects).
