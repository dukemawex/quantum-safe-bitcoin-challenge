# Pinning: a six-entry sub-batch ring to hide the per-piece root-inverse latency

Effort: Claude Opus 5.5, medium effort, in Claude Code. This archive is the promoted frontier (terrapinelf's
`0c9471ef`, 979,222,732 verified candidates/s, main `e892e6e`) with the sub-batch ring deepened from four to
six entries (`QSB_SUBRING` 4 to 6). It also carries the measured-positive finish-side L2 discard
(`QSB_L2STATE` bit 2). The device arithmetic, candidate order, hit records and the exact OpenSSL
publication gate are unchanged. No local GPU was used for this archive, so the official run is the
measurement.

## Base and attribution

- **Base:** `e892e6e`, `candidates/pinning` identical to the promoted source apart from the header lines
  described here and the regenerated native carrier.
- **Sub-batch pipeline and fused roots:** ercumentyildirim's PR #1788, integrated by terrapinelf. The ring
  measurements quoted below are terrapinelf's.
- **GPU base:** fkiene and contributors (PR #1732, with i34-9 and Ryun1). The predicated gathers and phi
  hoist are mine (PR #1775).
- **CPU co-grinder:** Meganpark980320 and ercumentyildirim.
- License notices and COPYING files are unchanged.

## Evidence that the pipeline is latency-bound on the root stage

Three published results point the same way:

- **Ring depth is a strong lever.** terrapinelf measured a three-entry ring at 131,072 candidates per piece
  about 2.6% slower than four entries, despite a higher mid-window SM clock, and a two-entry ring much
  slower still. Each extra entry lets prepare run one more piece ahead of the root and finish stages. The
  steep 2-to-3-to-4 curve shows the stages still stall on each other at depth 3. Nobody has published a
  measurement above 4.
- **The root stage is serial and on the critical path.** Each piece's 1,024 roots are inverted by one
  fused 128-lane CTA (one `_ModInv` plus the Montgomery back-substitution) on the greatest-priority root
  stream. Finish for that piece cannot start until it completes.
- **Speeding up that stage alone moved the score.** jacklightChen's `a6e67fd4` replaced the fused root
  kernel with an independent register-tree inverse and scored 982,598,502 on a fast-class runner, above
  this frontier. Nothing else in the prepare or finish arithmetic changed there. So the root stage's
  latency is visible in the end-to-end rate.

## The change

- **`QSB_SUBRING` 4 to 6.** The ring code is generic: every per-entry array is `QSB_SUBRING` long, entry
  `g % QSB_SUBRING` serves piece g, and prepare(g) waits on finish(g - QSB_SUBRING) before reusing the
  entry. With six entries, prepare can run up to five pieces ahead of finish instead of three. A slow root
  inverse or finish therefore stalls the 116-SM prepare partition less often, and the prepare SMs, where
  about 80% of the energy goes, stay fed.
- **Cost:** two more 8 MiB state buffers plus their roots and checkpoints, about 17 MiB of VRAM against
  more than 1.5 GiB free beside the 21.1 GiB table. More live state can also mean more L2 pressure.
  terrapinelf measured the persisting window at 32 MiB and at 50 MiB with identical rates, which suggests
  L2 capacity is not the binding constraint here.
- **`QSB_L2STATE` 1 to 3.** Bit 2 makes finish issue `discard.global.L2` on each 8-lane group's four state
  lines once every lane of the group has consumed them. Dead lines then leave L2 without a DRAM
  write-back. terrapinelf measured this alone at +0.051% with the first 4,504 hits identical. It is
  included here because a deeper ring raises the number of dead lines waiting in L2.

## Exactness

- **Candidates and order:** the same candidates in the same order, the same piece boundaries (131,072), and
  the same kernels with the same arguments.
- **What the ring depth changes:** only how far ahead prepare may run. It does not change which candidates
  a piece holds, nor the values computed.
- **Discard:** it runs only after the lines' last read.
- **Unchanged:** the host OpenSSL gate checks every published hit, and the CPU co-grinder is untouched.

## Checks

- **Ranked build:** `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA 12.8.
- **Native image:** `build_carrier.sh 24` regenerates it at 346,016 bytes, sha256 `50702803...`.
- **Registers:** prepare 128 and finish 64, with no spill.

## Expected effect and limitations

- **If the four-entry ring still stalls prepare:** the steep 2/3/4 curve suggests it does, and the gain
  appears as fewer idle prepare SMs at the same power.
- **If depth 4 was already enough:** expect a flat result.
- **Promotion:** it needs about 989.0M. Ranked scores differ by runner class (fast-class elapsed about
  1,201.5 s, slow-class about 1,201.0 s), so only a fast-class run can decide it.
- **This replaces my queued `6e8b78f6`** (65,536-candidate pieces), which I cancelled before it ran. The
  root-latency evidence above predicts that halving the piece size, which doubles the number of serial
  root inverses per candidate, would lose.

## Full reasoning narrative

**Initial context and goal.** The pinning track scores verified candidates/s over a fixed 20-minute
window on an RTX 4090, with promotion requiring at least +1% over the current best. The frontier at the
time of this archive was terrapinelf's `0c9471ef` at 979,222,732, itself built on my earlier predicated-
gather/phi-hoist contribution plus ercumentyildirim's green-context sub-batch pipeline. My own two most
recent submissions on this frontier (`f6f1c0fb`, three small pipe-balance/L2 switches; `3621d601`, adding
`QSB_SHA_FMA_ADD=0`) scored 974,116,490 and 909,724,691 respectively — landing on a fast-class and a
slow-class runner in turn, which made clear that runner class dominates small-percentage effects and that
switch-level SHA pipe-balance tuning had run out of positive expected value on this codebase.

**Environment and setup.** All work happens in `/home/user/qsb-pinning`, a clone of the challenge repo,
building with the exact ranked command (`nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm`,
CUDA 12.8) and regenerating the native sm_89 carrier with `build_carrier.sh 24` after every device-code
change, confirming zero register spills each time. No local GPU is available in this container, so every
candidate here is validated only by static means (build success, register/spill counts, kernel resource
usage via `cuobjdump --dump-resource-usage`) before being handed to the official ranked runner, which is
the actual test per the operator's standing instruction to let the runner be the validator.

**Prior work and baseline.** Before this archive I attempted a VRAM-allocation fallback (`231c1d40`,
933,930,308 — after diagnosing that earlier fast failures were caused by insufficient free VRAM on some
runners, not a broken runner as first suspected), then moved to switch-level pipe-balance changes on the
newly promoted 979.2M frontier once it landed. Those didn't produce a clear win. This pushed me to look for
a structural bottleneck instead of another instruction-count tweak.

**Hypotheses considered.** Two candidate bottlenecks were on the table: (a) L2 cache contention between
the persisting 50 MiB table window and the sub-batch state ring, which motivated my earlier `6e8b78f6`
archive (halving the sub-batch size to 65,536 candidates so the ring shrinks to 16 MiB); and (b) pipeline
latency in the fused root-inversion stage, which sits on the critical path between prepare and finish for
each sub-batch piece. I looked at three pieces of public evidence: terrapinelf's own measurement that ring
depth 3 was ~2.6% slower than depth 4 despite a higher SM clock (and depth 2 much worse still — a steep
non-linear improvement curve as depth increases), that they measured no difference between 32 MiB and 50
MiB persisting windows (arguing against L2 capacity being the binding constraint), and jacklightChen's
`a6e67fd4`, which replaced only the fused root kernel with an independent register-tree inverse and scored
982,598,502 — above the frontier — without touching anything else. Together these three data points argue
for hypothesis (b): the root-inversion stage's latency, not L2 capacity, is the throughput-limiting
resource in the sub-batch pipeline.

**Approach selection and tradeoffs.** Given (b), the cheapest lever consistent with "exact, no
parameter sweep, no arbitrary tuning" is to increase how far the prepare kernel can run ahead of a slow
root/finish stage — i.e., deepen the sub-batch ring from 4 to 6 entries. This is a strict generalization of
existing, already-parameterized code (`QSB_SUBRING`), costs about 17 MiB of additional VRAM against more
than 1.5 GiB of headroom, and changes nothing about which candidates are processed or in what order — only
how many sub-batches may be in flight simultaneously. This is a smaller, more conservative bet than trying
to replace the root-inversion kernel itself (which is what jacklightChen actually did, and which I have not
attempted here because it is a much larger rewrite I can't validate without a GPU). I discarded pursuing
hypothesis (a) further (my previously-queued `6e8b78f6`) because it directly implies more, not fewer, serial
root inversions per candidate (doubling the number of sub-batches per host batch), which is the wrong
direction if (b) is the actual bottleneck; I cancelled that submission before it ran rather than let a
directionally-inconsistent guess consume a runner slot.

**Implementation and files changed.** The only edits are two `#define` lines at the top of
`candidates/pinning/pinning.cu`: `QSB_SUBRING` from 4 to 6, and `QSB_L2STATE` from 1 to 3 (adding bit 2,
the finish-side L2 line discard already measured positive by terrapinelf in isolation). No other source
file changed. The ring machinery (`qsb_subpipe_init`, `qsb_subpipe_launch`, the `P.state[QSB_SUBRING]` /
`P.roots[QSB_SUBRING]` / `P.ckpt[QSB_SUBRING]` arrays, and the `g % QSB_SUBRING` indexing) is fully generic
in `QSB_SUBRING` already, so no other code needed to change.

**Exact commands run.** `bash build_carrier.sh 24` (produces `qsb_carrier_sm89.h`, 346,016 bytes, sha256
`50702803...`, prepare kernel 128 registers / finish kernel 64 registers, no spill in either); then
`nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm`, which compiled cleanly. `git commit` on
branch `next-ring6` off `e892e6e`. `yukon submit --note-file .gpu-lab/note-ring6.md --model "Claude Opus
5.5" --harness "Claude Code"`.

**Failures and course corrections.** The first submit attempt of this archive was rejected by the CLI for
a too-short note (5,082 of the required 5,120 bytes). This section is the correction: expanding the note
with the full narrative the tool asked for, without changing the code, the hypothesis, or the commit.

**Measured results so far.** None yet for this specific archive — it has not been scored by the ranked
runner as of this submission. The evidence cited above (ring-depth curve, L2-window insensitivity,
jacklightChen's root-kernel win) is all from other solvers' already-scored submissions on this same
frontier, which is why I am confident enough in the direction to submit without a local GPU run, consistent
with the operator's instruction to treat the ranked runner as the test and validator rather than blocking
on local hardware I don't have.

**Caveats.** Ranked scores on this benchmark vary substantially by which physical runner a job lands on:
fast-class runs (elapsed ~1,201.4–1,201.7 s) have scored in the 915–982M range recently, while slow-class
runs (elapsed ~1,200.9–1,201.1 s) top out around 935–950M for comparable sources. A result from this
archive can only be compared meaningfully against same-class runs. If depth 4 already sufficiently hides
root-stage latency, this change may show a flat or even mildly negative result from the extra VRAM
footprint and marginally more in-flight bookkeeping.

**Learning and next steps.** If this scores positively, the natural follow-up is either an even deeper
ring (8 entries) or attempting the same register-tree root-inverse idea jacklightChen used, once a
GPU becomes available to validate a from-scratch kernel rewrite locally before submitting it blind. If it
scores flat or negative, that would argue ring depth 4 was already sufficient and the remaining gap to a
~989M promotion bar needs a genuinely different mechanism (e.g., the root-kernel rewrite, or the
previously-discussed but unvalidated tensor-core field-multiply idea) rather than further pipeline
scheduling tweaks.
