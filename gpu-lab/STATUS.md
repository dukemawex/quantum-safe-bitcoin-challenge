# Current Bitcoin frontier status — 2026-09-27 19:45 UTC

This header supersedes older queue and waiting-candidate text below.

## Live promoted source

Both tracks currently sync to `46b24ebaa033fb69c7335794b54fd6a156359ec8`.
Subset best: **700953730**, RealAdii `521075fe`.
Pinning best: **995329477**, cefika `54ca2f74`.

## Active submissions

- Pinning `2cc64795-77e7-4289-9c76-efa3676c3bd6` is validating. It was submitted after a fresh sync and empty-own-queue check. It isolates four paired 128-bit prepare-state stores from the promoted four-slot implementation. Never cancel or duplicate.
- Subset `c1472179-294a-45da-b79e-f67482ea07f4` remains validating. It isolates the 24 MiB persisting-L2 address-window cap. Never cancel or duplicate.

## Latest scored result

Pinning `cff30dc4-dcff-42ad-9b25-b5e91144f04f` naturally rejected at **965192942**, verified=true, 138248 hits, elapsed 1201.53. The exact `QSB_SLOTS=3` isolation is closed and was not cancelled.

## Submitted pinning package

Recovery patch: `gpu-lab/prepared/vector-state-submitted-2cc64795.patch`, SHA256 `90677e64c597c2b82e509163f83fbad1a0dd0b42ab6be9b8005bb02e9f3fe3e8`.
The refreshed note is included in that patch. Host/native builds exit 0; 14 zero-spill records; prepare 128 registers; finish 64; five prepare LTC64B loads; cubin `d314e41b12353a5dfe179f388f1fb87e7834fd066d1a7bde13b237e17ceef8a0`. This is submitted, not waiting.

## Waiting pinning candidate

A distinct successor is prepared on live source: isolated exact second-fold carry scheduling in `_ModSqrAddSub2` (`QSB_SAS2_GLUE=1`). It consumes the first carry directly into `z2` and then consumes the following high-word carry into the same limb, removing one named carry temporary. It imports only this cut from i34-9's public `f7470c17` package. No paired stores, three-slot pipeline, other carry cuts, GLV assumptions or root changes.

CUDA 12.8.93 host/native builds exit 0. The native log has 14 zero-spill records. Prepare registers fall from 128 to 126; finish remains 64. Cubin SHA256 `59e120cd2445313800bcc0488437db7c7ea9a7e586cfc38c307a73fb6e3035ba`, 391072 bytes, five prepare LTC64B loads.

Recovery patch: `gpu-lab/prepared/sas2-glue-46b24.patch`, SHA256 `0560010a50aa94817007ae933a9b377538d67a888d515cc34c46620a4cb729af`.
Note: `gpu-lab/submission-note-sas2-glue.md` (8073 bytes).

Do not submit while `2cc64795` is active. On natural completion, assess its result, the current tip and overlap. Re-sync, reapply/rebuild if source moved, refresh the note and submit only if still qualified.

## Subset waiting candidate

Isolated `QSB_Q_MIX 4 -> 2` remains prepared on `46b24eb`; see the subset branch STATUS. Do not submit while `c1472179` is active.

## Rules

One own active per Bitcoin track; tracks may run concurrently; MLX independent. Never cancel. Before every edit/submission preserve delta and run `yukon sync --force`; immediately before fire sync and check the exact own queue again. Candidate-directory executable changes only; no harness/scorer/measurement edits, binaries or stamps. Notes at least 5 KiB and honest, with actual model/harness and proper coauthors. No local runtime claims, identical/noise-driven retries or blind sweeps.
