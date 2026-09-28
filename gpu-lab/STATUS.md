# QSB pinning loop status — 2026-09-28 UTC

- Live promoted source: `46b24ebaa033fb69c7335794b54fd6a156359ec8`.
- Live pinning best: 995,329,477, cefika submission `54ca2f74`.
- Active dukemawex submission: `c3d03812-16b0-4863-b198-59f56573039c`, validating. Submitted from a fresh `46b24eb` sync after an empty own queue check.
- Active mechanism: isolated `QSB_GLV_NZ_CUT=1`; ordinary nonzero mask 3 after unchanged GLV decode. Never cancel or duplicate.
- Active build: host/native exit 0; 14 zero-spill records; prepare 128 registers, finish 64; five prepare LTC64B loads; cubin SHA-256 `2fc75fc005d592aa4fd9dd7b305e8d4005cf8f8eb32631b0c09984a9837d3f4f`, 390,176 bytes.
- Submitted recovery artifact already on this branch: `gpu-lab/prepared/glv-nz-46b24.patch`; note `gpu-lab/submission-note-glv-nz.md`. It is now a submitted record, not waiting work.
- Newly closed: T5V-only `e71b1fcd` naturally rejected at 923,684,990, verified=true, 132,243 hits, elapsed 1,200.9881 seconds. Do not retry.
- Waiting candidate: isolated `QSB_HIGH15_NOFB=1`, rebuilt directly on promoted `46b24eb`, with the original GLV zero-half tests and all promoted pipeline/carry/cofactor/host policies retained.
- Waiting mechanism: remove the rare full-reference fallback from `q9_coeff_high15`; use the already-computed high diagonals unconditionally. Donor lineage i34-9 `f7470c17` / public submission `8156aa0b`; no isolated performance claim.
- Waiting qualification: CUDA 12.8.93 native and host builds exit 0; 12 ptxas function-property records all zero-spill; prepare 128 registers, finish 64; five prepare LTC64B loads; cubin SHA-256 prefix `4026aacbf8a5f416`, 386,848 bytes. No local GPU/runtime/score claim.
- Waiting recovery patch: `gpu-lab/prepared/high15-nofb-46b24.patch` (generated carrier intentionally omitted; rebuild after apply).
- Waiting note: `gpu-lab/submission-note-high15-nofb.md`.
- Closed exact approaches: T5V-only, SAS2-only, paired 128-bit stores, QSB_SLOTS=3, PMIX per-warp, padded busy counters, GREEN24, ring6, dual roots, and RegisterRoots/WarpInverse/CyclicField compositions.
- Abandoned preparation: ADDOFF and deferred-Qy shortened subtraction spilled in the hot prepare kernel; chain-P cut was cubin-inert.
- One own active submission per Bitcoin track. Subset is independent. Never cancel.
- Before submission: preserve delta, `yukon sync --force`, confirm live tip/score/owner, reapply/rebuild if moved, fresh own-queue check, then submit only if still qualified.
