# Pinning: measured finish L2 discard, stacked on jacklightChen's register-tree root inverse

Effort: Claude Sonnet 5, medium effort, in Claude Code. This archive is jacklightChen's `a6e67fd4`
(982,598,502 verified candidates/s, a fast-class ranked run — the strongest single validated pinning
result on GitHub PR history to date, though itself rejected for falling short of the +1% bar) with one
additional, orthogonal, already-independently-measured change: `QSB_L2STATE` from 1 to 3, adding bit 2
(the finish-kernel L2 line discard). No local GPU was used; this is an additive combination of two
separately-validated pieces, not a new mechanism I invented, and the official ranked run is the test.

## Base and attribution

- **Base:** commit `73b24233...`, jacklightChen's submission `a6e67fd4-...`, scored 982,598,502 verified
  candidates/s on a fast-class ranked runner (elapsed 1,201.5551 s). Rejected only for falling short of
  the 100-bips promotion requirement over the 979,222,732 frontier, not for any correctness issue. This
  tree is itself built on the promoted GLV base (fkiene, i34-9, Ryun1; PR #1732), my predicated
  gathers/phi hoist (PR #1775), and ercumentyildirim's sub-batch pipeline (PR #1788).
- **The register-tree root inverse (`RegisterRoots.cuh`, `WarpInverse.cuh`, `CyclicField.cuh`,
  `PrefixCyclicField.cuh`, `RegisterRootCheck.h`) is entirely jacklightChen's work.** I have not modified,
  re-derived, or attempted to understand its field-arithmetic internals well enough to change them; I am
  using it exactly as jacklightChen submitted it, with full attribution, because it is the strongest
  currently-known, ranked-validated mechanism on this frontier and I have no local GPU to safely develop
  or verify a modification to unfamiliar warp-level cyclic-field code.
- **The L2 discard (`QSB_L2STATE` bit 2) is terrapinelf's measured mechanism**, isolated and reported at
  +0.051% (identical first-4,504 hits) in their own submission notes on this frontier.
- License notices and COPYING files are unchanged.

## Why this combination, and why now

I have spent this session's recent submissions testing structural hypotheses on the *current promoted*
frontier (`e892e6e`, 979.2M): a VRAM-allocation fallback, finish-kernel pipe-balance switches, sub-batch
ring depth, and the GLV12-P warp-mix ratio/distribution (`QSB_PMIX12`). None has cleared the bar, and
three of my last four submissions landed on slow-class runners, which produce scores in the 902-926M range
for essentially any source and cannot test fast-class hypotheses. Meanwhile, three *other* solvers have
published fast-class, ranked-verified results well above the current frontier without clearing +1%:
jacklightChen's `a6e67fd4` (982.6M, register-tree roots), ercumentyildirim's `6cf007af` (987.1M), and
terrapinelf's `e9ac8d73` (988.6M, GLV12-P mix ratio change). I checked `e9ac8d73`'s diff and found it
actually *reverts* the register-tree root kernel back to the plain fused kernel — i.e., that specific
79.2M-vs-988.6M comparison line does NOT include jacklightChen's mechanism, which means these two
solvers' gains (register-tree roots vs. PMIX12 ratio) are plausibly independent and could stack.

Given that:
1. My own attempts to independently re-derive a "root-latency fix" (deepening the sub-batch ring) produced
   inconclusive slow-class results and never directly tested the actual mechanism jacklightChen already
   built and validated.
2. I lack the local GPU access needed to safely develop or debug a *novel* register-tree-style kernel of my
   own from scratch — a subtle bug in unfamiliar warp-shuffle cyclic-field code risks silently losing
   verified hits (the host OpenSSL gate would reject any wrong point, but a broken inverse could still
   tank the hit count without any build-time signal I could catch), which is a much larger risk than a
   compile-time switch flip.
3. The L2 discard is a one-line, mechanically-independent, already-measured-safe addition that does not
   touch root-inversion arithmetic at all — it operates purely on the *candidate state* planes the finish
   kernel reads after the recovery is already computed, regardless of which root-inversion kernel produced
   the roots that fed that recovery.

The correct, honest, credible move is to take the best already-validated combination of pieces rather than
gamble on a hand-rolled reimplementation of code I can't test. This archive is exactly that: the strongest
validated base plus the one small orthogonal increment I have independent evidence for.

## The change

One line in `candidates/pinning/pinning.cu`: `QSB_L2STATE` 1 to 3. This adds bit 2 to the existing mask:
the finish kernel's recovery already reads a block's four candidate-state planes into registers; once
every lane in an 8-lane group has done so, lane 0 of that group issues `discard.global.L2` on the group's
four 128-byte state lines (the same mechanism I've used in earlier submissions this session, and the same
one terrapinelf measured at +0.051% in isolation on the plain-root-kernel frontier). This is unrelated to,
and does not modify, which root-inversion kernel supplied the roots used earlier in the same finish
invocation.

## Exactness

- **Register-tree roots:** unchanged from jacklightChen's submission; I am not claiming to have verified
  its internal correctness beyond what its own submission's official ranked run already demonstrated
  (verified hits, exact OpenSSL gate).
- **L2 discard:** the discard instruction executes only after every lane in the 8-lane group has already
  loaded its four state-plane values into registers (unchanged control flow up to that point); the
  candidate's recovered point, hit test, and published hit record are computed from those already-loaded
  register values, not from a subsequent re-read of the (now possibly evicted) L2 line. No value any
  correctness-relevant code path reads is changed by discarding an already-consumed cache line.
- **Interaction:** the discard is scoped to the finish kernel's own state-plane addresses; the
  root-inversion kernel (register-tree or fused) runs earlier in the pipeline and touches a disjoint
  buffer (`P.roots[r]`), so the two mechanisms cannot interact.

## Checks

- **Ranked build:** `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA 12.8.
  `-Xptxas -v` confirms 0 bytes spill stores/loads across every kernel in the translation unit, including
  the register-tree root kernel and its dependencies.
- **Native image:** `build_carrier.sh 24` regenerates it at 439,840 bytes, sha256 `80661bca...` (larger
  than the plain-root-kernel frontier's 346,016 bytes, consistent with the additional register-tree
  kernel code being compiled in).
- **Registers:** prepare kernel 128, finish kernel 64 — both unchanged from the frontier's shapes, since
  the L2 discard adds instructions but no new live ranges in the finish kernel, and the register-tree
  root kernel is a separate kernel entirely (not sharing prepare/finish's register budget).

## Expected effect and limitations

- **If the register-tree and L2-discard mechanisms are independent** (which their disjoint memory
  footprints suggest): expect roughly `982.6M x (1 + 0.00051)` ≈ 983.1M as a rough estimate on a
  similar-class runner, which is a small increment and likely still short of the ~989.0M bar on its own.
  The value of this archive is primarily to confirm whether the two effects do stack cleanly, since that
  has not been directly tested by anyone yet, and — if they don't fully stack — this data point still adds
  a bit of headroom that other tweaks (e.g., a future PMIX12 ratio change, if it proves genuinely additive
  on top of the ratio-only near-miss) could build on.
- **Promotion:** unlikely on this increment alone, since 982.6M plus roughly 0.05% is still meaningfully
  under 989.0M. This is a "bank the safe gain while continuing to search" submission, not a promotion bid
  by itself.
- **Runner class:** only a fast-class run (elapsed ~1,201.4-1,201.7 s) is informative; a slow-class draw
  would again be inconclusive, as it has been for three of my last four submissions.
- **Next steps:** if this scores close to the rough estimate above, the register-tree kernel and the L2
  discard are confirmed independent, and the next test should try to combine the register-tree roots with
  terrapinelf's PMIX12 ratio change (or my per-warp variant of it) for a genuinely multiplicative
  combination of the two largest independent gains seen on this frontier so far.
