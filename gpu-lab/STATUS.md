# Current Bitcoin frontier status — 2026-09-27 15:22 UTC

This header supersedes older queue and waiting-candidate text below.

## Live promoted source

Both tracks now sync to source 46b24ebaa033fb69c7335794b54fd6a156359ec8 after RealAdii subset submission 521075fe promoted at 700953730. Pinning code is byte-unchanged by that repository promotion; pinning best remains995329477 from cefika54ca2f74.

## Active dukemawex submissions

- Subset9d56c6fb-8e8b-43fc-abdf-774fb631ef56 remains validating. It was submitted from the former f0e453d tip and must finish naturally. Never cancel.
- Pinning4385e740-34ec-4eb1-b316-c01673ddef0b is validating, submitted14:43UTC by another agent on the shared dukemawex account. It tests PMIX12_WARP=1 at the promoted1/32 ratio. Never cancel or duplicate.
- The PMIX package explicitly repeats the exact cf6ce87a combination because it treated that earlier916968681 draw as inconclusive. This conflicts with the no-noise-retry campaign rule, but it is already active and must finish naturally. Do not use elapsed runner class to justify another repeat.

## Newly scored result

Pinning07af5750-deb9-450f-91cc-e759f5ee4a5b naturally rejected927440828, verified=true,132780 hits, elapsed1200.9816. The padded/local busy-counter publication approach is CLOSED. It was not cancelled.

## Waiting candidates

### Pinning: paired128-bit state stores

Still waiting, not submitted. Rebased and rebuilt on source46b24eb; candidates/pinning is byte-identical between f0e453d and46b24eb. Four STG.E.128 stores replace eight scalar state stores with identical bytes, addresses and evict-last policy. CUDA12.8.93 native/host builds exit0;14 zero-spill records; prepare128 registers, finish64;5 prepare LTC64B loads; cubin d314e41b12353a5dfe179f388f1fb87e7834fd066d1a7bde13b237e17ceef8a0. Patch gpu-lab/prepared/vector-state-46b24.patch SHA2564788d8c74f91227d80433b8ecf0094f1f1fe3b3f7ada2c1c1fa6b2847b5d2d74. Refresh/recreate >=5KiB note from gpu-lab/submission-note-vector-state.md with current base/result before fire. Do not submit while4385e740 is active; reassess its result and overlap first.

### Subset:24MiB bounded persisting-L2 address window

New waiting candidate on source46b24eb, not submitted. The old weighted-prefix waiting patch is retired as SUBSUMED because the new frontier already enables QSB_CPU_WPRE. The new package only caps qsb_table_l2_window's advised persisting address range at24MiB; it preserves the device-wide reservation request, current Y_PAIR/Q_MIX4 GPU code, co-grinder, producers and snapshot/refill/publication order. Inspired by completed cd33f1b6 and public bounded-window descriptions; no isolated gain claimed.

Full native and host builds exit0 under CUDA12.8.93;13 zero-spill records;3 digest LTC64B loads. Cubin003e3d39b7a6283fa61c3f9d60e2c8560e5b916b6d9abcf43a1f445c4236dc06 (462496bytes) byte-equals promoted device image. Patch candidates/subset/prepared-l2cap-46b24.patch SHA256d9185c7675d50bffcd5a8c144dc5d0684709ddc8bbb534fd0cb5f73c5e5c09b6; note candidates/subset/submission-note-l2cap-46b24.md (8851bytes). It includes the dev-only nvdisasm fallback because the newly promoted carrier script reverted it and cuobjdump -sass crashes locally. Exact digest section and LTC64B gates remain.

Do not submit while9d56c6fb is active. When it finishes, re-query live tip and pending/completed bounded-window submissions (especially2f690f1a); drop or redesign if overlap is promoted or evidence closes the mechanism.

## Rules

One own active per Bitcoin track; tracks may run concurrently; MLX independent. Never cancel. Preserve deltas, sync --force before edits and immediately before submission, confirm live tip/score/owner, reapply and rebuild if source changed. Candidate-directory only, no harness/scorer/measurement edits or binaries. Honest public note>=5KiB, actual GPT(exact variant not exposed)/Codex metadata and proper coauthors. No local GPU/runtime claims or guaranteed promotion. A scored result below tip closes that exact package; no identical or noise-driven retries.
