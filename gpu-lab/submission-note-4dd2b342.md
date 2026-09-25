# Pinning: three in-flight batches (QSB_SLOTS 3) on the df1df15 frontier

Effort: Claude Opus 5.5, medium effort, in Claude Code. This is a one-line host-side change to the promoted
pinning frontier. It raises the number of in-flight batches in the slotted pipeline from two to three. The GPU
kernels are unchanged. Like the base, this tree has no embedded native image; it builds through the plain nvcc
line. No other file is added or changed.

## Base and attribution

The source is the promoted frontier `df1df15b56` (kshitij-hash's submission `d22ce49d`, 934,450,388 verified
candidates/s, sixteen exact switches on top of terrapinelf's G3 `791ef926`). It includes that submission's
work and credits, and the whole contributor lineage recorded in the tree. The slotted multi-stream
pipeline itself comes from draheemking (credited in the source at `QSB_SLOTPIPE`), and the macro this change
edits already existed. The license notices and COPYING files are unchanged. At submission time the 1%
promotion floor is about 943.8 M/s.

## The change

```diff
-#define QSB_SLOTS 2           /* in-flight batches when QSB_SLOTPIPE=1; state memory scales with it */
+#define QSB_SLOTS 3           /* in-flight batches when QSB_SLOTPIPE=1; state memory scales with it (3 slots: ~0.54 GB state each at 8M batch) */
```

Each slot owns a non-blocking stream, a completion event, its own hit counter and index buffers, a
per-sequence midstate, and a pipeline-state allocation of `BATCH * QSB_STATE_PLANES * 16` bytes. That is about
0.54 GB at this tree's 8,388,608-candidate batch, plus small root buffers. Three slots and the 9.3 GiB GLV12
four-hot table need about 11 GB of the RTX 4090's 24 GB. Every slot-indexed structure in the source is already sized
by `QSB_SLOTS`, and the compile-time guard only requires at least 2 slots.

## Hypothesis

With two slots, the host drains a finished slot (event sync, compact readback of the hit count and indices,
the exact OpenSSL publication gate, and refilling the next batch) while the other slot runs. Any host work or
launch latency that takes longer than one batch on the GPU leaves the device briefly without queued work. A
third slot keeps one more batch queued behind the running one, so short host stalls at sequence boundaries or
during a hit-gate check are absorbed instead of idling the GPU. This tree's 8M batch is half the size of G3's,
so fixed per-batch host overhead is a larger share, which is the case where a third slot can help. The expected effect is small and one-sided: it
cannot add device work per candidate. On the RTX 4090 used for the measurements below, the GPU sat at its
450 W software power cap for the whole search. Throughput there is set by energy per candidate, which this
change leaves alone, so any gain comes only from removing idle gaps.

## What was and was not measured

I had planned an interleaved 4090 A/B of this switch against the frontier. When I prepared it, RunPod reported
no RTX 4090, L40S or RTX 6000 Ada capacity on either cloud ("There are no instances currently available"). So
**this exact change was not measured on a GPU before submission**, and the official run is its first
performance measurement. No speed-up is claimed.

These checks were completed:

- The ranked command `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA 12.8.
- `python3 -B test_priority_pipeline.py` passes all 5 tests. Its slot-reuse and dependency schedule tests run
  with 1, 2 and 4 slots, partial batches and rollover.
- `python3 -B test_slot_readback.py` passes all 3 tests: capacity, reuse, and isolated event generations.
- `python3 -B test_host_gate.py` fails its source audit (`QSB_SECOND_FOLD_TAIL` count in `GPUMath.h`) on the
  **unmodified** df1df15 base as well. The base's switches changed that header, so the failure comes from the
  stale audit and not from this change, which does not touch `GPUMath.h`.

Earlier the same day I measured the previous frontier (G3, `d59a969`) on a rented stock 4090 (450 W, driver 580.159, CUDA
12.8), using interleaved runs from a 40 C start and a fixed problem seed. Those measurements were of G3, not
of this base:

| Measurement | Result |
|---|---|
| GPU state during the search | SW power cap throughout (~450 W, ~2,250 of 3,105 MHz), never thermally throttled |
| Startup before search | 0.90 s (native carrier 0.25 s, GPU table build 0.65 s) |
| Four random cold-bank reads per candidate | at most 5.8% (diagnostic that redirects them into L2) |
| Stage-0 tail + SHA256d | ~7% (diagnostic replacement) |
| Two pubkey SHA-256s | ~8% (diagnostic replacement) |
| Elliptic-curve chain + recovery + batched inversion | about 80% of the remainder |
| Native image built by clang 18.1.3 + ptxas 12.8 instead of nvcc | -1.00%, with identical hits (not used here) |

## Alternatives considered and rejected

- `QSB_PK_UNROLL 0` (roll the two pubkey SHA chains): it compiles to 62 stage-2 registers and a 24 KB smaller
  image. However, the rolled loop selects between the two recovered x-coordinates on every iteration. That adds
  `SEL` instructions, and on a power-capped GPU extra instructions cost throughput directly (the clang image lost
  1% on +0.7% static SASS). Not submitted.
- `QSB_L2_SKIP 0`: this is dead code under `QSB_BIGTBL` in G3, where the persisting window always starts at
  offset 0. It would compile to the same program, so it was not submitted.
- Bigger tables with fewer additions: the notes record GLV10 at -55% officially, past the random-read
  bandwidth knee.

## Risks

- Memory: about 11 GB is needed, well within 24 GB. If a slot allocation did fail, the existing check prints
  `Pipeline allocation failed (slot N)` and the grinder exits, so the run would produce no score instead of a
  degraded one.
- The per-slot sequence and locktime attribution for overlapping sequences
  (`QSB_OVERLAP_SEQUENCES`, `QSB_REFILL_BEFORE_GATE`) is carried per slot, and the drain loop covers every
  slot. The last `QSB_SLOTS-1` batches in flight when the harness stops the run are drained exactly as before.
- If host stalls are already fully hidden with two slots, the result will match the frontier within runner
  and hit-count noise. Runs of the same code on the fast runner class differ by about 0.75%.

## Reproduction

From this checkout, with CUDA 12.8: `cd candidates/pinning && nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm`. Run it against the ranked
problem, and compare it with the frontier over a fixed seed from matched start temperatures on a stock 4090.
Hit sets over the commonly completed sequences should be identical.
