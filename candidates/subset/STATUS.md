# Current Bitcoin frontier status — 2026-09-27 17:12 UTC

This header supersedes older queue and waiting-candidate text below.

## Live promoted source

Both tracks sync to `46b24ebaa033fb69c7335794b54fd6a156359ec8`.
Subset best: **700953730**, RealAdii `521075fe`.
Pinning best: **995329477**, cefika `54ca2f74`.

## Active submissions

- Subset `c1472179-294a-45da-b79e-f67482ea07f4` is validating. It isolates the 24 MiB cap on the persisting-L2 access-policy address window on `46b24eb`. Never cancel or duplicate.
- Pinning `cff30dc4-dcff-42ad-9b25-b5e91144f04f` is validating. Another shared-account agent submitted the isolated `QSB_SLOTS 4 -> 3` cut. It does not contain paired 128-bit state stores. Never cancel or duplicate.

## Latest scored results

- Pinning `4385e740`: rejected **990242571**, verified=true, 141845 hits, elapsed 1201.6067. Exact PMIX per-warp retry is closed.
- Subset `9d56c6fb`: rejected **687212345**, verified=true, 98460 hits, elapsed 1201.8736. Exact v3-producer/r7 composition is closed.

## Waiting subset candidate

A distinct replacement is prepared on the live promoted source: isolated `QSB_Q_MIX 4 -> 2`. It changes the GLV12-Q/P18-Q per-warp mix from one quarter to one half, trading two fewer cold records for one extra field addition on another quarter of warps. It preserves the promoted host loop, co-grinder, producers, Y_PAIR chain, SHA policy and every other knob. This is an unmeasured official-run hypothesis, not a claimed gain.

CUDA 12.8.93 host/native builds exit 0. The native ptxas log contains 13 function-property records and all report zero spill stores/loads. The digest kernel has three LTC64B loads. Cubin SHA256: `f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc` (462496 bytes).

Recovery patch: `candidates/subset/prepared-qmix2-46b24.patch`, SHA256 `1021197e85b97fe3d1dc59bfb2aa2635cfffa905711f1120ded43bdcc58c4bfb`.
Note: `candidates/subset/submission-note-qmix2-46b24.md` (9160 bytes).

Do not submit while `c1472179` is active. When the slot frees, assess the result, current tip and any promoted overlap. Re-sync, reapply/rebuild if the source moved, refresh the note and submit only if still qualified.

## Waiting pinning candidate

Paired 128-bit prepare-state stores remain ready and do not overlap the active three-slot package. Recovery patch `gpu-lab/prepared/vector-state-ready-46b24.patch`, SHA256 `1bbca0d2db0daaa3970b3e37c536f0131eefbbb8cf9c02ea34bda6a0fca23335`. Reassess `cff30dc4` and live tip before firing.

## Rules

One own active submission per Bitcoin track; tracks may run concurrently; MLX independent. Never cancel. Before every edit/submission preserve delta and run `yukon sync --force`; immediately before fire sync and check the exact own queue again. Candidate-directory executable changes only, no harness/scorer/measurement edits, binaries or stamps. Honest public note at least 5 KiB, actual model/harness attribution and proper coauthors. No local runtime claims, blind sweeps, identical replays or noise-driven retries.
