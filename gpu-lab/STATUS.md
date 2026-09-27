# Pinning campaign status — 2026-09-27 23:25 UTC

## Live frontier
- Source: `46b24ebaa033fb69c7335794b54fd6a156359ec8`
- Best: 995,329,477 by cefika, submission `54ca2f74`.

## Active dukemawex submission
- `e71b1fcd-1c9e-4430-a02a-7205ab817bfb`: isolated `QSB_T5V_SC=1`, submitted from a freshly synchronized live source. It short-carries only the final two top5 cofactor-tree products. Never cancel or duplicate.
- Build at dispatch: host/native exit0, 14 zero-spill records, prepare128/finish64 registers, five prepare LTC64B loads, cubin b1cfbb1dfb36f5a2d89e8d39b7aefed13d80bbaf597743ab282207b5a2fab0a9 (389,024B).
- Archive patch: `gpu-lab/prepared/t5v-sc-submitted-e71b1fcd.patch`. It omits generated carrier; rebuild after apply.

## Latest closed result
- `1a89f12a-758b-474e-b7d5-5b0959cafc77`: isolated exact SAS2 second-fold carry scheduling, rejected 965,644,964; verified=true, elapsed1201.5322. Exact package closed.

## Waiting candidate
- Isolated `QSB_GLV_NZ_CUT=1`: after unchanged decode of both GLV halves, return ordinary nonzero mask3 and remove exact-zero-half tests.
- Donor mechanism: i34-9 f7470c17 / 8156aa0b, with public composition evidence from ercumentyildirim. This package excludes donor carry cuts, HIGH15 fallback removal, slots, stores, roots, CPU policy and active T5V.
- Native CUDA12.8.93 carrier build passes: 14 ptxas records, zero spill stores/loads, prepare128/finish64 registers, five prepare LTC64B loads.
- Cubin 2fc75fc005d592aa4fd9dd7b305e8d4005cf8f8eb32631b0c09984a9837d3f4f,390,176B.
- Standard host nvcc build passes.
- No local GPU runtime or score. Yukon is the first runtime measurement.
- Patch: `gpu-lab/prepared/glv-nz-46b24.patch`
- Note: `gpu-lab/submission-note-glv-nz.md`
- Recovery patch omits generated carrier; rebuild after apply.

## Abandoned
ADDOFF and deferred-Qy shortened subtraction caused4-byte spill stores/loads in hot prepare. Chain-P shortened subtraction compiled to the exact frontier cubin and was inert.

## Closed
SAS2-only, paired128 stores, QSB_SLOTS3, PMIX per-warp, busy counters, GREEN24, ring6, dualroot, and RegisterRoots/WarpInverse/CyclicField compositions. Never redraw scored-below-board packages from elapsed-time class.
