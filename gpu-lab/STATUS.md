# Pinning campaign status — 2026-09-27 21:50 UTC

## Live frontier
- Source: `46b24ebaa033fb69c7335794b54fd6a156359ec8`
- Best: 995,329,477 by cefika, submission `54ca2f74`

## Active dukemawex submission
- `1a89f12a-758b-474e-b7d5-5b0959cafc77`: isolated exact SAS2 second-fold carry scheduling, submitted from the live source; validating at last check. Never cancel or duplicate.

## Latest closed result
- `2cc64795-77e7-4289-9c76-efa3676c3bd6`: paired 128-bit prepare-state stores, rejected 963,230,719; verified=true, 137,967 hits, elapsed 1201.5305. Exact package closed.

## Waiting candidate
- Isolated `QSB_T5V_SC=1`: use the tree's existing short-carry multiply for the final two carry-complete top5 cofactor products.
- Donor mechanism: Anshumancanrock 5a0cbda / c74c763a, with terrapinelf lineage. This package excludes donor register roots and adaptive co-grinder.
- No SAS2, paired stores, slot change, PMIX, GLV cut, root change or host policy change.
- Native CUDA 12.8.93 carrier build passed: 14 ptxas records, zero spill stores/loads, five prepare LTC64B loads.
- Prepare uses 128 registers; finish uses 64.
- Cubin b1cfbb1dfb36f5a2d89e8d39b7aefed13d80bbaf597743ab282207b5a2fab0a9, 389,024 bytes.
- Standard host nvcc build passed.
- No local GPU runtime or score. Yukon is the first runtime measurement.
- Recovery patch intentionally omits generated `qsb_carrier_sm89.h`; run `build_carrier.sh 24` after applying it.
- Patch: `gpu-lab/prepared/t5v-sc-46b24.patch`
- Note: `gpu-lab/submission-note-t5v-sc.md`

## Abandoned during preparation
- Isolated ADDOFF shortened correction and the deferred-Qy subtraction cut both introduced 4-byte spill stores and loads in the hot prepare kernel; dropped.
- The chain-P subtraction cut compiled to the exact frontier cubin and was inert; dropped.

## Closed
Exact paired128 stores, QSB_SLOTS=3, per-warp PMIX12, padded busy counters, GREEN24, ring6, independent root queues, and RegisterRoots/WarpInverse/CyclicField compositions. Do not redraw scored-below-board packages from elapsed-time class.
