# Current evidence gate and results — 2026-09-28 02:17 UTC

This header supersedes historical queue/dispatch instructions below.

User requested henceforth submissions with strong evidence of beating the frontier. Successful compilation and a plausible mechanism alone do not establish speed. Keep investigating on the live source, but hold speculative candidates until concrete comparative evidence supports exceeding the live promotion threshold with allowance for noise. Never promise certainty or invent performance measurements. Do not submit just to fill a free slot. No paid GPU without approval.

Fresh Yukon queries and sync confirm source 46b24ebaa033fb69c7335794b54fd6a156359ec8. Both own queues are empty. No submission or cancellation in this check.
- Subset frontier: 700,953,730 / RealAdii; 1% bar approximately 707,963,268.
- Pinning frontier: 995,329,477 / cefika; 1% bar approximately 1,005,282,772.
- Subset 2e178289 naturally rejected 691,857,188 at 2026-09-28 01:55:22 UTC, verified=true, 99,124 hits, elapsed 1201.8555. Exact Q_MIX2 package CLOSED.
- Pinning c3d03812 naturally rejected 925,750,928 at 2026-09-28 02:08:18 UTC, verified=true, 132,541 hits, elapsed 1201.0082. Exact GLV_NZ_CUT package CLOSED.
- Subset v3-only producer patch and pinning HIGH15_NOFB patch remain saved research candidates, HELD for insufficient isolated performance evidence; no longer automatically dispatch-qualified.
- Current top public scores examined: subset 4da17ebc 701,215,160 (confounded host composition), pinning c12006c2 1,003,132,947 (broad register-root/three-slot/carry/hash composition). Neither clears its current promotion threshold. These results do not prove gains for our isolated waiting patches; do not replay blacklisted combinations.
- Execution worktrees were preserved to /tmp/qsb-preserve-0217 before sync and now contain clean promoted source; recover candidate patches from designated fork branches when justified.

One active submission per track, never cancel. Preserve all prior blacklists. Continue monitoring and research; no guaranteed performance claim.

---

# Subset campaign status — 2026-09-27 21:50 UTC

## Live frontier
- Source: `46b24ebaa033fb69c7335794b54fd6a156359ec8`
- Best: 700,953,730 by RealAdii, submission `521075fe`

## Active dukemawex submission
- `2e178289-6467-468c-86a1-524e6c818eb5`: isolated `QSB_Q_MIX 4 -> 2`, submitted from the live source; validating at last check. Never cancel or duplicate.

## Latest closed result
- `c1472179-294a-45da-b79e-f67482ea07f4`: 24 MiB persisting-L2 address-window cap, rejected 694,734,661; verified=true, 99,529 hits, elapsed 1201.7678. Exact package closed.

## Waiting candidate
- Isolated v3 cached-schedule host producers on the promoted source.
- Only `tests/gpu_epochs/host_producers.h` changes at runtime; promoted co-grinder, GPU code, QSB_Q_MIX4 and wait/core policy remain.
- Donor: ercumentyildirim public a141df2b / source 3b4fce1, host-producer lineage from terrapinelf. i34-9's current-tip package gives composition evidence but is not copied wholesale.
- Native CUDA 12.8.93 carrier build passed: 13 ptxas records, zero spill stores/loads, three digest LTC64B loads.
- Cubin 003e3d39b7a6283fa61c3f9d60e2c8560e5b916b6d9abcf43a1f445c4236dc06, 462,496 bytes, byte-identical to promoted.
- Standard host nvcc build passed.
- No local GPU runtime or score. Yukon is the first runtime measurement.
- Recovery patch intentionally omits generated `qsb_carrier_sm89.h`; run `build_carrier.sh 24` after applying it.
- Patch: `candidates/subset/prepared-v3-producers-46b24.patch`
- Note: `candidates/subset/prepared-v3-producers-note.md`

## Closed
Exact r7 lane, r7+v3 composition, 24 MiB L2 cap, paired-SHA ALU/full unroll, prep overlap, split verify, flag sweeps, chain-loop unroll/spills and GPU affine batch chain. Do not redraw below-board packages from noise.
