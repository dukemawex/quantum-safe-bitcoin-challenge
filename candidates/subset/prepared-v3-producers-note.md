# Subset: isolate the v3 cached-schedule host producers on the promoted 700.95M tree

Model: GPT (exact variant not exposed)
Harness: Codex

## Summary

This candidate starts from the live promoted subset source
`46b24ebaa033fb69c7335794b54fd6a156359ec8`, corresponding to RealAdii's
submission `521075fe` and the recorded frontier score 700,953,730 when this
package was prepared. It changes only the host implementation of the three
floating epoch producers. The promoted GPU code, native sm_89 device image,
co-grinder, table geometry, warp mix, Y-pair path, digest kernel, publication
order, verifier-facing output and benchmark contract are unchanged.

The imported producer header is the public v3 cached-schedule implementation
used in ercumentyildirim's `a141df2b` lineage and later reused by i34-9. The
specific experiment here is deliberately narrower than those public packages:
only `tests/gpu_epochs/host_producers.h` is replaced. In particular, this does
not import their CPU co-grinder, weighted-prefix inversion, table retuning,
blocking wait policy, Q-mix change, or any device arithmetic. That isolation is
the reason for this submission.

I have no local NVIDIA GPU in this environment. The official Yukon run is the
first runtime and performance measurement. I do not claim a local score or a
guaranteed improvement. The evidence for trying the cut is source-level reuse,
public ranked component evidence, a byte-identical promoted device image, and
successful native and host builds.

## Hypothesis

The three host producers build the epoch descriptors and first-block SHA-256
states consumed by the GPU digest stage. Their input contains repeated block
shapes. The v3 implementation precomputes SHA-NI message schedules for those
repeated shapes instead of rebuilding the 64-word schedule on every producer
compression. It keeps the existing producer ring, fallback behavior and batch-0
self-check, so the intended effect is less host work per produced batch without
changing the bytes copied to the device.

The cached objects are schedules of `W[i] + K[i]`, not digests or seed-specific
answers. A SHA-256 compression schedule is a deterministic function of the
corresponding 64-byte message block. The recurring blocks in this producer have
fixed class layouts; their variable words are used as cache keys or filled by
the existing per-batch code. The compression state and round order remain the
same. The optimization therefore removes repeated schedule expansion rather
than approximating SHA-256.

This lever matters only if producer work is visible in the ranked host/GPU
pipeline. The current promoted source already moved those producers off the GPU
and runs them as floating host threads. Reducing their CPU demand can improve
headroom for the host loop and co-grinder, or prevent the ring from approaching
fallback. It can also be neutral if the producer ring already stays comfortably
ahead. The official runner is needed to settle that balance.

## Public evidence and why it is not treated as an isolated measurement

The v3 producer code appeared in ercumentyildirim's public package
`3b4fce1213a41ab5e2e96d7f038fdd88a07f2878` (`a141df2b`). That package reported
696,429,794 on an older source and combined several mechanisms, so its total
score is not a measurement of this header alone. A later current-tip public
package from i34-9 (`4da17ebc`) recorded 701,215,160 while combining this
producer implementation with a different co-grinder donor. That score was
above the live best numerically but below the challenge's one-percent promotion
threshold, and it is also confounded. Neither number is presented as a forecast
for this candidate.

The useful evidence is narrower: the implementation is public, has already
survived official compilation in related packages, and attacks repeated host
schedule construction rather than changing the GPU arithmetic. The current
candidate removes the co-grinder and other package differences so Yukon can
measure the producer cut on the actual promoted tree.

The immediately preceding dukemawex subset experiments are not replayed here.
The isolated r7 CPU lane scored 693,254,524 and missed promotion; the r7 plus v3
producer composition scored 687,212,345; the 24 MiB persisting-L2 address-window
cap scored 694,734,661. Those exact packages are closed. This package uses the
promoted co-grinder unchanged and contains no L2-window cap. It is therefore not
an identical or noise-driven resubmission of any of them.

## Exact implementation boundary

The executable change is the public v3 `host_producers.h` on top of the live
source. The header retains the established safety structure:

1. Batch 0 is produced by both the existing GPU producer path and the host
   producer path.
2. Descriptor words and first-block states are compared before host production
   is trusted.
3. A mismatch disables the host producers and leaves the GPU producer path as
   the fallback.
4. Each later batch is copied only when its ring slot is ready. If it is not
   ready within the existing timeout, the GPU producer builds that batch.
5. Repeated fallback disables the host producer optimization for the remainder
   of the run rather than consuming incomplete data.

The v3 addition builds reusable schedule tables for the tail blocks, the first
block classes, and a per-thread cache keyed by the first block's variable
remainder words. The SHA-NI compression routine consumes those schedules in the
same ABEF/CDGH state representation already used by the producer. The OpenSSL
fallback remains for hosts without the required SHA extensions. Placement is
the public three-floating-producer policy used by this header; it does not pin
over the promoted main-core reservation or alter the GPU stream graph.

No `CpuGrindSubset.h` change is included. No constants in `subset.cu`, `tree.cu`
or the field headers are changed. The active `QSB_Q_MIX` remains the promoted
value 4; this candidate does not contain the separate Q-mix 2 experiment. The
device code compiled into the carrier is consequently byte-identical to the
promoted image.

The only build-script edit is a development-environment fallback from
`cuobjdump -sass` to `nvdisasm` when the former crashes. It analyzes the same
fresh cubin, finds the exact prepare/digest symbol, and preserves the existing
LTC64B gate. It does not run in the benchmark hot path and does not alter the
carrier bytes.

## Correctness argument

For each schedule-cached block, the SHA-256 recurrence is unchanged:

`W[t] = sigma1(W[t-2]) + W[t-7] + sigma0(W[t-15]) + W[t-16]`

and the round input uses `W[t] + K[t]`. Precomputing that sum for a block and
feeding it to the same round function is equivalent to recomputing it at each
compression. Cache selection includes the words that distinguish the block
class, and the existing producer self-check compares the actual output buffers
against the GPU path before those buffers can feed ranked work.

Even if a platform or layout assumption were not met, the result is not silent
publication of a false hit: the self-check disables the host path. The GPU
producer and exact verifier remain unchanged. This is a result-neutral host
optimization when its eligibility and self-check gates pass, and a fallback to
the promoted behavior when they do not.

## Build checks performed

The candidate was built from the synchronized live source with CUDA 12.8.93.

- Full native carrier generation completed successfully at `QSB_ZEROS_N=24`
  for `sm_89`.
- All 13 ptxas function-property records report zero spill stores and zero
  spill loads.
- The digest kernel still contains three `LTC64B` loads, satisfying the
  carrier script's exact-section check.
- The generated cubin is 462,496 bytes with SHA-256
  `003e3d39b7a6283fa61c3f9d60e2c8560e5b916b6d9abcf43a1f445c4236dc06`.
- That cubin is byte-identical to the promoted device image, as expected for a
  host-only producer change.
- The standard host binary build with `nvcc -O3 -DQSB_ZEROS_N=24` completed and
  linked against OpenSSL and libm. Only existing OpenSSL deprecation warnings
  were emitted.
- `git diff --check` passes.

These are compile and structural checks, not a CUDA runtime or throughput test.
No GPU was available locally, so the producer self-check, fallback counters,
ring depth and ranked throughput have not been observed in this environment.

## Expected effect and limitations

The expected direction is reduced producer CPU work. The end-to-end magnitude
may be small because the producer threads run concurrently with the dominant GPU
pipeline. More host efficiency helps only when it relieves contention or keeps
the producer ring ahead. It could also change CPU scheduling in a way that does
not help the thermally limited GPU, and public package scores are too confounded
to quantify that risk.

The challenge requires a strict one-percent promotion margin, so even a real
sub-percent gain is insufficient. This note therefore makes no promotion claim.
The official result should be interpreted as the first isolated measurement of
this host-producer implementation on the promoted 700.95M tree. A scored result
below the then-live frontier closes this exact package; it should not be redrawn
solely because of elapsed-time class or run noise.

## Attribution

Promoted subset source and GPU spine: RealAdii, kshitij-hash, fkiene,
Meganpark980320 and the credited authors already present in the live tree.
Cached-schedule host-producer implementation: ercumentyildirim, based on the
public host-producer lineage from terrapinelf. i34-9's public current-tip package
provided additional composition evidence but is not copied wholesale here.

Suggested coauthors for this isolated reuse are `ercumentyildirim terrapinelf
RealAdii kshitij-hash i34-9`. The exact model and harness are recorded above and
will also be supplied to the Yukon CLI. No local GPU score is claimed.
