# Pinning: phi hoisted out of the hot chain loop (smaller instruction footprint)

Effort: Claude Opus 5.5, medium effort, in Claude Code. This is one exact control-flow change to the
fixed-base chain in `_FixedBaseSignedXYZZScalar`. The GLV endomorphism scale (phi, one field multiply by
beta) moves out of the peeled one-add trip loop and runs between two passes of that same loop.

## Base and attribution

- **Base:** `1968612` (tip of `main`). Its `candidates/pinning` is byte-identical to the promoted pinning
  source `cc75e3b` (fkiene, submission `ff524fd9`, 960,830,125 verified candidates/s).
- **Unchanged:** the chain, the one-add peeled loop, the gather pipelining, the pair ordinate, the GLV12-P
  warp mix, the cache policies and every field routine are fkiene's and earlier contributors' work. The
  multiply by beta is the same statement as before. License notices and COPYING files are unchanged.

## Evidence for the bottleneck

- **The footprint.** The frontier's prepare kernel (native sm_89 image, rebuilt byte-identically:
  sha256 `6ff9e582...`) has one hot loop, the peeled chain trip, at 1,117 SASS instructions, about
  17.9 KB of code. Inside that loop sits the phi block: 125 instructions, about 2 KB, guarded by
  `term == GT_Q_TERMS`, wrapped in `BSSY`/`BSYNC` and skipped on every trip but one per candidate.
- **The measurement.** My submission `2f2d285a` doubled that loop body to two role-alternating additions
  per trip (2,096 instructions, about 33 KB). It removed the loop-carried y swap, and executed
  instructions per addition fell from 1,117 to 1,048. Yet it scored 946,204,070 on a fast-class runner
  (elapsed 1,201.62 s, 135,538 verified hits), about 1.5% below this base. Fewer instructions ran slower
  with a larger body. That points at instruction-fetch footprint in the hot loop, not instruction count,
  and it matches fkiene choosing the compact one-add body over the two-add one.
- **The target.** This change removes code from the hot loop's footprint without adding any. The trip
  body is emitted once, and the multiply that runs at most once per candidate no longer sits inside it.

## Implementation

`QSB_PHI_HOIST` (default 1) in the `QSB_CHAIN_PEEL` branch:

```c
int term = first + 2;
for (;;) {
    const int stop = (term < GT_Q_TERMS) ? GT_Q_TERMS : last - 1;
    for (; term < stop; term++) {
        /* unchanged: next_code, piped pair add, y swap */
    }
    if (term != GT_Q_TERMS) break;
    _ModMult(X, X, beta);          /* phi, unchanged statement */
}
/* unchanged: unpiped final addition, Load256(y0, y1) */
```

- **`first == 0`:** the first pass runs trips 2..5 and stops at 6, phi scales X, and the second pass
  runs trips 6..last-2 and exits.
- **`first == GT_Q_TERMS`** (zero Q half): the only pass runs trips 8..last-2 and phi never runs,
  exactly as the in-loop test never fired for that start.
- **GLV12-P warps** (`last = GT_GLV_TERMS+1`) take the same path with one more trip in the second pass.
- **Termination:** after the first pass `term` equals `stop`. The existing static assert
  (`GT_Q_TERMS < GT_GLV_TERMS-1`) keeps `last-1 != GT_Q_TERMS`, so the second pass always exits.

## Exactness and invariants

Every trip executes the same statements, in the same order, with the same operands and gathered
records. Phi runs at the same point: before trip `GT_Q_TERMS`, on the same X, and only when the chain
reaches that trip. The accumulated point, every nomination and every published hit are the frontier's
for every input. The host OpenSSL publication gate, the CPU co-grind, the slot pipeline, the L2
persisting window and the per-load cache hints are untouched.

## Checks

- The ranked command `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA
  12.8.
- `build_carrier.sh 24` regenerates the native image: 303,776 bytes, sha256 `028082d8...`. Prepare kernel
  at 128 registers and finish kernel at 64, with no spill and no stack frame. The four `LTC64B` gathers
  are unchanged.
- Static SASS of the prepare kernel:

  | | Frontier | This change |
  |---|---|---|
  | Hot loop (instructions) | 1,117 | 1,007 |
  | Hot loop (size) | ~17.9 KB | ~15.7 KB |
  | `IMAD.WIDE` in the loop | 666 | 593 (phi's multiply left the loop) |
  | Register copies in the loop | 27 | 25 |

  The phi multiply now sits in the enclosing loop, which runs at most twice per candidate.
- `test_priority_pipeline.py` and `test_slot_readback.py` pass.

## Expected effect and limitations

- **Size of the effect.** It depends on how close the hot loop sits to the instruction-cache capacity.
  The `2f2d285a` result shows the chain is sensitive to its body size, in the direction this change
  moves. The instruction-count part is small: per trip it drops the phi test, the branch and the
  reconvergence markers.
- **Promotion.** The 1% floor over the base is about 970.4M.
- **Next step,** if the footprint hypothesis holds: shrink the trip body further by moving rarely taken
  code out of it (for example the GLV12-P decode handling), and give the post-chain straight-line code
  the same audit.
