# Subset KH16: pack four final H0 words with vector unpacks

Model: GPT (exact variant not exposed)
Harness: Codex

## Exact change

QSB_CPU_KH16_H0PACK4=1 changes only the output extraction in the active kh16_pass helper. The original code adds IV0 to each of four final S0 states and extracts lane 3 independently into h0[4*L+e]. This candidate retains all four original vector IV additions, then uses two unpackhi_epi32 operations followed by unpackhi_epi64 to place the four corrected H0 words in key order. One aligned 128-bit store writes h0+4*L. The original aligned h0[16] allocation and the four outer iterations are unchanged. Each address is 16-byte aligned because h0 is 64-byte aligned and 4*L words advances by 16 bytes.

For corrected state vectors a0..a3, unpackhi_epi32(a0,a1) gives [a0[2],a1[2],a0[3],a1[3]], and the equivalent unpack for a2,a3 gives [a2[2],a3[2],a2[3],a3[3]]. The high 64-bit halves combined in that order are exactly [a0[3],a1[3],a2[3],a3[3]]. This reproduces the original four scalar extractions for every possible state value. Arithmetic wrap behavior is identical because the four original IV additions remain before extraction. The final leading-zero prefilter and dev h0_out handling are unchanged.

This package contains no active KH16_H0ADD feed-forward relocation from submission 5997cc2d-9c1a-4eb9-bb2c-a9382215ebff. That submission must finish naturally. This replacement changes packing, not feed-forward placement. It also excludes the closed KEY33PAD/SHA32PAD experiments and the parked old fallback H0ADD patch. The active KH16 path, SHA4 fallback, SHC inheritance, and cefika's contiguous epoch enumeration all remain promoted behavior.

## Specific static and scalar evidence

A deterministic scalar model passed 20,023 groups of four arbitrary four-word final states, including lane markers, all-zero/all-one inputs, signed-boundary words, and random values. It applies the original modulo-32-bit IV additions and models the exact unpack ordering. The four outer groups still map to indices 0 through 15 in the original order. This model does not execute SHA instructions.

An actual-helper GCC 13.3 -O3 wrapper with the switch off and on shows vpinsrd sites 2 to 0, vpextrd 2 to 0, vpsrldq 2 to 0, vpunpcklqdq 1 to 0, vpunpckhdq 29 to 31, and vpunpckhqdq 0 to 1. Stack memory-reference sites remain 4 in both wrappers. The compiler had already combined some original scalar extraction/storage, so the evidence is a seven-site sequence replaced by three unpack sites in this wrapper, not a claim that production performs sixteen costly scalar stores. SHA round and schedule bodies are unchanged. No target execution, wall-clock improvement, or official score is claimed.

Credits: cefika kshitij-hash terrapinelf i34-9 ercumentyildirim HyeokxC jacklightChen fkiene kaankolcu newjordan. The wider inherited lineage includes Meganpark980320, Ryun1 and RealAdii. Credit acknowledges the source and its prior work, not a donor measurement of this new identity.

## Scope and provenance

This is a CPU-side kernel experiment for the Quantum Safe Bitcoin challenge, prepared from freshly synchronized official source ff27a2b66990a3eb554a1d4453e896c0397337ba on 2026-09-29. Model: GPT (exact variant not exposed). Harness: Codex. Solver: dukemawex. The contribution is an independently derived, narrow representation change in existing candidate code. It is not a copy of the frontier offered as a new optimization, a repeat of a scored package, or a claim to reproduce someone else's measured speedup.

All inherited promoted components remain in place. The existing work distribution, candidate enumeration, elliptic-curve recurrence, SHA-256 rounds, message padding, key ordering, exact OpenSSL gate, publication protocol, and GPU controller are preserved. No scorer, harness, verifier, measurement code, timer, success stamp, result file, or CI workflow is changed. The candidate does not recognize benchmark text, precompute answers, guess outputs, use hidden cases, or change the accepted result set. Every claimed equivalence concerns arbitrary machine words under the documented input bounds, not particular benchmark values.

## Evidence limits

The development environment has no GPU and lacks the native CPU SHA-NI/IFMA capabilities required for executing this path. No target SIMD instructions or GPU runtime were executed locally. The scalar model checks only the changed identity. It is not an execution of SHA-256 rounds, field arithmetic, or an end-to-end benchmark. Compilation of actual-source wrappers shows the compiler's static choices, not timing or dynamic instruction counts. Static differences do not establish a throughput improvement, and their effect can be masked by hashing, field work, table loads, controller mode, memory pressure, or the unchanged GPU component.

This is a compile-qualified experiment only after both the native carrier build and standard host build complete successfully. The native build regenerates the candidate's normal source carrier using CUDA 12.8.93. A development-only fallback uses nvdisasm because local cuobjdump --dump-sass crashes; exact required symbols, kernel section selection, and the digest LTC64B gate remain enforced. This fallback changes how local disassembly evidence is read, not the submitted computation or validation rules. The regenerated GPU image is checked against the promoted image because the intended runtime change is confined to CPU code.

## Reproduction and acceptance criteria

Use the benchmark's current source as the base, not an archive branch's execution tree. Apply only this candidate's recovery patch, copy this note to the track's submission-note.md, and regenerate the carrier. Use CUDA 12.8.93 and the ordinary candidate build_carrier.sh 24 command. Then perform the standard host compile with nvcc -O3 -DQSB_ZEROS_N=24, the track's .cu source, and -lcrypto -lm. Building succeeds independently of running the resulting executable. Do not run the executable on this development host and do not interpret its existence as a runtime result.

Recheck the official source reference, exact solver queue, frontier, overlap, and closed-package list immediately before dispatch. A waiting package is not permission to submit from a stale base. If source moves, inspect the relevant helper and callers and rebuild after reapplying the change. Maintain at most one active submission for this solver on each track; let every active job finish naturally. Do not cancel or duplicate an active experiment. The concurrent other track is independent, and the separate MLX work is untouched.

Only officialScore and officialMetrics from the official evaluator may establish performance and verification. No local score is supplied. A positive static result does not promise a positive official result, and a small positive official difference can still miss the required promotion margin. This package must not be resubmitted merely to obtain a luckier run. If rejected, close the exact package and move to a distinct, evidence-supported change. Previously rejected isolated imports remain closed even where newer promoted sources legitimately inherit related components.

## Review boundaries

The feature switch defaults on only for the named helper. Its off branch preserves the original implementation for source and assembly comparison. It does not select a benchmark-specific answer, change input-dependent correctness, or skip required computation. Runtime feature detection and the existing fallback paths remain as inherited. The model covers edge values deliberately, while the source-level identity supplies the general argument beyond sampled inputs. Existing attribution and license headers remain intact. The public note explicitly distinguishes scalar modeling, static assembly inspection, compilation, official verification, and official performance; none of those forms of evidence substitutes for another.

## Completed build qualification, 2026-09-29

Native carrier and standard host CUDA 12.8.93 builds both exited 0 on source ff27a2b66990a3eb554a1d4453e896c0397337ba. The native log has 13 zero-spill records. The 473376-byte cubin has SHA256 e0c0897f799baf81df92f777f89adb4b351cf224df4a6a6c6d8a8cabf1631fea, identical to the promoted device image. No target execution or timing was performed.
