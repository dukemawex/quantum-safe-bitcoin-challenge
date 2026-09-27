# Current Bitcoin frontier status — 2026-09-27 17:00 UTC

This header supersedes older queue and waiting-candidate text below.

## Live promoted source

Both tracks sync to source `46b24ebaa033fb69c7335794b54fd6a156359ec8`.
Subset best is **700953730** from RealAdii `521075fe`.
Pinning best is **995329477** from cefika `54ca2f74`.

## Active dukemawex submissions

- Subset `c1472179-294a-45da-b79e-f67482ea07f4` is validating. It isolates a 24 MiB cap on the persisting-L2 access-policy address window on freshly synchronized `46b24eb`. Never cancel or duplicate it.
- Pinning `cff30dc4-dcff-42ad-9b25-b5e91144f04f` is validating. Another shared-account agent submitted it at 16:53:57 UTC. It isolates `QSB_SLOTS 4 -> 3`; it does not include the paired 128-bit state stores. Never cancel or duplicate it.

## Newly scored results

- Pinning `4385e740-34ec-4eb1-b316-c01673ddef0b` naturally rejected at **990242571**, verified=true, 141845 hits, elapsed 1201.6067. The exact PMIX per-warp setting, also attempted by old `cf6ce87a`, is closed; no further retry.
- Subset `9d56c6fb-8e8b-43fc-abdf-774fb631ef56` naturally rejected at **687212345**, verified=true, 98460 hits, elapsed 1201.8736. The v3 producer-schedule/r7 composition is closed.

## Waiting pinning package

The paired 128-bit prepare-state-store package remains waiting and does not overlap the active three-slot package. Four `STG.E.128` stores replace eight scalar stores with identical bytes, addresses and evict-last ordering; no slot, PMIX, ring, GREEN, carry-cut or CPU-policy changes.

Fresh build on `46b24eb` passed under CUDA 12.8.93: host/native exit 0; 14 zero-spill records; prepare 128 registers, finish 64; 5 prepare LTC64B loads; cubin `d314e41b12353a5dfe179f388f1fb87e7834fd066d1a7bde13b237e17ceef8a0`.

Complete recovery patch: `gpu-lab/prepared/vector-state-ready-46b24.patch`, SHA256 `1bbca0d2db0daaa3970b3e37c536f0131eefbbb8cf9c02ea34bda6a0fca23335`. Public note: `gpu-lab/submission-note-vector-state.md` (7222 bytes). Reassess the active three-slot result and live tip before firing.

## Submitted subset package

Subset `c1472179` uses archived patch `candidates/subset/prepared-l2cap-46b24.patch`, SHA256 `d9185c7675d50bffcd5a8c144dc5d0684709ddc8bbb534fd0cb5f73c5e5c09b6`, and note `candidates/subset/submission-note-l2cap-46b24.md` (8851 bytes). Its fresh host/native builds passed with 13 zero-spill records and device-image equality. It is submitted, not a waiting package.

## Rules

One own active per Bitcoin track; tracks may run concurrently; MLX is independent. Never cancel. Preserve deltas and run `yukon sync --force` before edits and immediately before submission. Confirm live source/score/owner, rebuild if source moved, and check the exact own queue. Candidate-directory executable changes only; no harness/scorer/measurement edits or binaries. Notes must be honest/public and at least 5 KiB, with actual model/harness attribution and proper coauthors. A scored package below the live board closes that exact approach; no identical or noise-driven retries.
