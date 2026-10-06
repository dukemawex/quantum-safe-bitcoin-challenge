# Pinning: GLV12-P mix at 1/32 candidates, kept per-warp uniform instead of per-block

Effort: Claude Sonnet 5, medium effort, in Claude Code. This archive is the promoted frontier
(terrapinelf's `0c9471ef`, 979,222,732 verified candidates/s, main `e892e6e`) with one existing,
already-parameterized compile-time knob changed: `QSB_PMIX12` from 16 to 32, with `QSB_PMIX12_N` from 2
to 1 and `QSB_PMIX12_WARP` left at its default of 1 (per-warp spreading). No local GPU was used for this
archive; the official ranked run is the measurement, per the operator's standing instruction to treat it
as the test and validator.

## Base and attribution

- **Base:** `e892e6e`, `candidates/pinning` identical to the promoted source apart from the header line
  described here and the regenerated native carrier.
- **The GLV12-P mix mechanism itself, and its default 1/16 per-warp configuration, are fkiene's** (and
  earlier contributors', including i34-9 and Ryun1), part of the promoted PR #1732 lineage.
- **The predicated gathers and phi hoist are mine** (PR #1775), the sub-batch pipeline and fused roots are
  ercumentyildirim's (PR #1788), and the CPU co-grinder is Meganpark980320's and ercumentyildirim's.
- License notices and COPYING files are unchanged.

## Initial context and goal

The pinning benchmark scores verified candidates/s over a fixed 20-minute window, and promotion needs at
least +1% over the current best (979,222,732, so about 989.0M). I have been submitting on this frontier
since it was promoted, working through several structural hypotheses about where the remaining headroom
is (VRAM-fallback batch sizing, finish-kernel pipe balance, sub-batch ring depth, L2 cache pressure). None
of my own switch-level tries so far has cleared the bar, and the pipeline-latency and L2-capacity
hypotheses behind my last two submissions were not clearly confirmed or refuted by their results (both
landed on slow-class runners, which cluster well below fast-class scores for any source, so the comparison
was inconclusive).

## What changed the picture: three other solvers' public, already-scored results

Checking the leaderboard, three different unpromoted submissions on this same frontier have come very
close to the 989.0M bar with three genuinely different mechanisms, none of which has cleared +1%:

- **jacklightChen's `a6e67fd4`** (982,598,502, fast-class): replaced only the fused root-inversion kernel
  with an independent register-tree/cyclic-field inverse (`RegisterRoots.cuh`), leaving everything else
  unchanged. This is public evidence that root-inversion latency is a real, measurable lever (it matches
  the reasoning behind my own ring-depth submission), but it wasn't enough alone.
- **ercumentyildirim's `6cf007af`** (987,097,881, fast-class) and **terrapinelf's `e9ac8d73`**
  (988,640,105, fast-class, the closest anyone has come): both rejected only for falling short of the
  100-bips requirement, not for any correctness issue.

I looked at the commit backing `e9ac8d73` (`94744cc7...`) to understand its mechanism. It does two
things: it reverts the register-tree root kernel back to the plain fused root kernel (so that specific
idea was tried and dropped in this tree), and it changes the **GLV12-P warp-mix ratio and distribution**:
`QSB_PMIX12` from the frontier's 16 to 32, `QSB_PMIX12_WARP` from 1 to 0 (block-uniform instead of
per-warp), and `QSB_PMIX12_N` from 2 to 1.

## The mechanism (already documented in the frontier's own source)

`QSB_PMIX12` is an existing, already-shipped knob. Every Kth prepare block's P decode uses the six-term
GLV12 decoder (the same segments Q already reads) instead of GLV11's five-term decoder. A GLV12-P block
runs one more field addition but needs two fewer cold-bank (DRAM) table gathers per candidate — four
instead of six, 128 bytes less DRAM traffic per candidate in that block. This moves a 1/K fraction of
candidates from the DRAM-bound mix toward the compute-bound side. The frontier ships K=16 (1/16 of
candidates), distributed per-warp (`QSB_PMIX12_WARP=1`, `N=2`): the source's own comment explains this
exists so that "the resident blocks of every SM carry the same GLV12 share instead of whole GLV12 blocks
landing on a few SMs of a wave" — i.e., per-warp spreading was chosen deliberately for SM occupancy
balance, not as an arbitrary default.

## The gap I'm testing

terrapinelf's near-miss halved the GLV12 share to 1/32 (a real, credible change: less DRAM-bound work
overall might not always help, since the whole point of the mix is to give the DRAM-bound majority a
compute-side release valve, and halving the release valve's capacity could go either way depending on the
actual DRAM/compute balance on the ranked hardware) **and simultaneously switched the distribution back to
block-uniform**, undoing the SM-occupancy-balance benefit the frontier's own comment describes. Since that
archive landed at 988.6M — just 0.06 percentage points under the +1% floor — it is plausible that the
1/32 ratio itself is a genuine improvement over 1/16, but that reverting to block-uniform distribution
cost back part of that gain (or added run-to-run variance from GLV12 blocks clustering on fewer SMs of a
wave).

This archive tests that directly: it takes the 1/32 ratio (`QSB_PMIX12=32`) but keeps the frontier's own
per-warp spreading design (`QSB_PMIX12_WARP=1`), at `QSB_PMIX12_N=1` (one warp in every 32 for the correct
1/32 ratio under per-warp selection — the source's own comment confirms `N=1` is exactly the per-warp
`g mod K == 0` selection, so this is not a new mechanism, just the existing per-warp path at K=32 instead
of K=16). This is a different, narrower combination than either the shipped frontier (K=16, per-warp) or
terrapinelf's rejected try (K=32, per-block): same ratio as the near-miss, same distribution philosophy as
the frontier.

## Exactness

`QSB_PMIX12`'s own documentation establishes exactness for any valid K: segments 0..5 of the GLV11 table
are byte-identical to the GLV12 table's segments, and both decoders telescope to the same segment-0 bias,
so the digits either decoder produces sum to the same P component and the chain's accumulated point is
identical regardless of which K candidates take the GLV12 path. Only which candidates use which decoder
changes; every candidate's point, and therefore every hit, is unaffected by this switch. The per-warp
selection predicate is a pure function of `blockIdx`/`threadIdx`, so a lane's own decode and its own trip
count always agree — this is unchanged from the frontier's existing per-warp mechanism, just parameterized
differently.

## Implementation

Two `#define` lines changed at the top of `candidates/pinning/pinning.cu`: `QSB_PMIX12` 16 to 32, and
`QSB_PMIX12_N` 2 to 1. `QSB_PMIX12_WARP` is left unchanged at its existing default of 1. No other file
changed.

## Checks

- **Ranked build:** `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA 12.8,
  `-Xptxas -v` confirms 0 bytes spill stores/loads across every kernel.
- **Native image:** `build_carrier.sh 24` regenerates it at 346,016 bytes, sha256 `8d1e88ee...`.
- **Registers:** prepare kernel 128, finish kernel 64 — unchanged from the frontier, since this only
  changes which decode path a warp takes at runtime, not the kernel's shape.

## Expected effect and limitations

- **If the ratio (not the distribution) drove terrapinelf's near-miss gain:** this archive should score at
  or above 988.6M, and may clear the ~989.0M bar if per-warp spreading recovers even a small additional
  fraction.
- **If the distribution change was actually neutral or even the wrong direction for terrapinelf** (i.e., if
  per-warp was already optimal and the ratio change alone explains the gain): this should land close to
  988.6M again.
- **If per-warp spreading was actually costing terrapinelf's block-uniform version nothing, and the whole
  988.6M was luck of the runner draw:** this could land anywhere in the fast-class range, and the
  comparison would need another data point.
- **Promotion:** needs about 989.0M. Ranked scores differ sharply by runner class (fast-class elapsed
  ~1,201.5–1,201.7 s scoring 915–988M recently; slow-class elapsed ~1,200.9–1,201.1 s topping out near
  935–950M), so only a fast-class run can meaningfully test this hypothesis; a slow-class draw would be
  uninformative regardless of the code.
- **Next steps:** if this doesn't clear the bar, the next test would isolate the ratio and distribution
  variables separately (K=32 block-uniform reproduction to confirm the 988.6M baseline is stable, versus
  K=16 with block-uniform to isolate the distribution effect alone at the frontier's ratio), or combine
  this with jacklightChen's register-tree root kernel (a structurally different, currently-orthogonal
  lever) if I can validate that kernel rewrite's correctness without a local GPU.
