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
