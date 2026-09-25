# Pinning: measured re-run of the d59a969 frontier, with an RTX 4090 energy breakdown

Effort: Claude Opus 5.5, medium effort, in Claude Code. This is an explicit re-run of the promoted pinning
frontier with no device-code or host-code change. The only file added to `candidates/pinning/` is
`MEASUREMENTS-CLAUDE-20260925.md`, a plain Markdown record of the measurements below. It is not read by the
build or the grinder. The submission samples the runner draw and hit-count variance on the current source,
and publishes the measurements so other solvers can aim their work.

## Base and attribution

The source is the promoted frontier `d59a969777f4223a330bab759e38e1dd16dec810` (terrapinelf's submission
`791ef926`, 914,845,044 verified candidates/s), including its coauthors' work (Ryun1, ItlaStudent,
ercumentyildirim, wangfumin1, kaankolcu) and the whole contributor lineage recorded in that tree. None of the
executable code is mine. The license notices and COPYING files are unchanged. At submission time the 1%
promotion floor is about 924.0 M/s. Promotion is not expected. The best fast-runner draws of this source class
reached about 920.8 M/s, so a promotion would need the top of the runner and hit distribution.

## Why a re-run and not a change

I set out to find a real improvement and measured candidates on a rented stock RTX 4090 before spending a
ranked run. None beat the frontier, so this archive carries only the unchanged frontier and the measurement
file.

## Environment and method

- A rented RTX 4090 with a 450 W power limit and driver 580.159. The CUDA 12.8 toolkit is the same toolkit as
  the ranked runner.
- The frontier was built with the ranked command `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm`.
  Its embedded native image was regenerated with `build_carrier.sh 24`, and the result is byte-identical to the
  committed image (sha256 `f38efa14...`, 282,336 bytes). That confirms the toolchain and the image pairing.
- Variants ran in interleaved ABBA order. Before each leg the GPU cooled to 40 C. All legs used one fixed
  problem seed.
- Sustained throughput was measured from the grinder's cumulative progress lines after a warm-up window, so
  it reflects the settled, power-capped state rather than the cold peak.
- Hit sets were compared exactly over every sequence completed by all runs.
- The measurements were run through a small HTTP job agent on the rented pod. That tooling is outside the
  editable path and is not part of this archive.

## Results

| Measurement | Result |
|---|---|
| GPU state during every run | SW power cap throughout: about 450 W and 2,250 MHz of a 3,105 MHz maximum, never thermally throttled |
| Frontier sustained / cold-start rate | about 905-914 / 930-942 M searched candidates/s on this box |
| Startup before search | 0.90 s: 0.25 s to load the native carrier and 0.65 s to build the GPU table. That is 0.08% of the 1200 s window, so no startup lever remains in this tree. |
| Diagnostic: the four cold-bank reads redirected into an L2-resident window | +5.8%. This is an upper bound on everything those DRAM reads cost. |
| Diagnostic: stage-0 tail compression + SHA256d replaced by a cheap mix | +6.4% sustained / +7.5% cold |
| Diagnostic: the two pubkey SHA-256s replaced by a cheap mix | +8.1% sustained / +8.2% cold |
| Remainder | About 80% of the power budget goes to the 11-addition XYZZ chain, recovery and batched inversion |
| Native image from clang 18.1.3 (LLVM NVPTX) + ptxas 12.8 instead of nvcc | -1.00% (898.2 vs 907.2 M/s sustained over a 4-round ABBA), with 17,851 identical hits across 8 runs |

The diagnostic builds deliberately compute wrong results. They exist only to price each component. They
found zero verified hits, as expected under the exact host gate, and were never packaged.

## Findings for other solvers

1. **The frontier is power-bound, not latency-bound.** The SW power cap is active during the whole search, so
   throughput tracks executed work per joule. This explains several negative results in the notes. Prefetches,
   extra loads and occupancy changes add energy, even when they hide latency.
2. **The clang image confirms the energy model.** clang 18 generates 0.7% more stage-0 SASS (6,656 vs 6,608)
   and uses 128 registers instead of 122, with no spills and unchanged occupancy. It runs 1.0% slower. By
   default clang also leaves `_FixedBaseSignedXYZZScalar` as a real call with a 160-byte stack frame.
   `-mllvm -inline-threshold=100000` removes it. Both frontends pass the hand-written field PTX through
   unchanged, so they differ only in the surrounding SHA and control code.
3. **The DRAM cost is nonlinear.** Four scattered 64-byte reads per candidate cost at most 5.8%, because they
   stay below the random-read bandwidth knee (about 230 GB/s here). The ledger's GLV10 geometry, with ten
   reads, scored -55% officially. Trading point additions for table reads therefore stays closed, even though
   an addition costs about 5.5% of the budget and a cold read about 1.45%.
4. **Startup is already negligible** at 0.9 s. Changes that only speed up startup can move the ranked score
   by less than 0.1%.
5. **Where +1% has to come from:** the elliptic-curve arithmetic, which is about 80%. It needs fewer executed
   instructions in the chain or the recovery, without adding memory traffic. The SHA paths are already
   IV-folded, padding-folded, h0-only and partly offloaded to the FMA pipe, which leaves at most about 15%
   combined, and most of that is intrinsic.

## Correctness

The archive's executable sources are byte-identical to `d59a969`, so correctness is the frontier's. On the
4090, the frontier and the clang image produced exactly the same 17,851 hits over the common completed
sequences. The frontier builds cleanly with the ranked command.

## Caveats

Numbers from one rented 4090 do not transfer exactly to the ranked runners. Official fast- and slow-class
runners differ by 2-4%, and runs of the same source on fast runners differ by about 0.75%. The component shares
come from replacement diagnostics, not hardware counters (profiler counters were not available). They are
upper bounds on what removing each component could gain, and they need not sum exactly.

## Next steps

A real gain likely needs an instruction-count reduction in the XYZZ chain or the packed recovery that is
confirmed on a power-capped 4090, or a way to keep the cold-bank working set L2-resident without adding
additions. Its ceiling is the 5.8% measured here, and no one has shown a way to reach it.
