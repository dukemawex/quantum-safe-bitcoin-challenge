# Subset: combine H0 feed-forward after packing four key-hash results

Model: GPT (exact variant not exposed)
Harness: Codex

## Base, provenance and current queue

This waiting candidate starts from live source8d07d3ebad41a017dfaa5906b164f883a9b59348. The promoted subset score is708,411,009 from jacklightChen's5c7e36c5, with a one-percent promotion threshold around715,495,120. It is a new independently derived output-packing identity in the promoted qsha_keyhash4_h0 function, not an import of another solver's measured package.

Coauthors: terrapinelf jacklightChen i34-9 ercumentyildirim HyeokxC RealAdii kshitij-hash fkiene

The attribution covers the current frontier and retained SHA/co-grinder lineage. It does not imply that a donor measured this isolated transformation. The preceding second-SHA32PAD372154a4 naturally rejected706,714,889 at2026-09-29 02:46:46UTC, verified=true,101,268 hits,elapsed1202.0372. That exact package is closed. KEY33PAD32002794-e204-49c8-a0db-165b0657cf5d was submitted02:53:25UTC and remains active; its padding edits are absent from this waiting source. KH16,MRG,X4PS and all previous closed GPU packages remain excluded.

## Exact runtime change

QSB_CPU_KEY_H0ADD=1 changes only the feed-forward and final packing in the CPU compressed-key SHA helper. The promoted function processes four independent compressed33-byte messages in two pairs. It runs the same64 rounds for every message and retains the final SHA-NI ABEF register S0 for each message. The promoted code adds IV0 to each of these four registers, then uses the existing unpack sequence to extract the A lane from each register as four H0 outputs.

Only the highest32-bit lane of each S0 contributes to that returned vector. Its IV constant is always0x6a09e667. The candidate saves each unmodified S0, performs the identical unpack sequence, then adds a single vector containing four copies of0x6a09e667. Lane selection commutes with lane-wise addition modulo2^32 when the selected constant is preserved. Therefore each output remains precisely A_final+IV_A modulo2^32 in the original message order.

No intermediate SHA state, compression round, message word, schedule expansion, key serialization, parity prefix or caller changes. All64 rounds still execute. This does not remove feed-forward or assume the discarded state words are zero; it simply avoids adding constants to lanes which are never returned. The helper has always exposed H0 only, and its prefilter and exact host publication gate remain unchanged. Generic full-digest SHA functions are not altered.

The zero setting of the compile-time switch retains the original four additions for a reproducible compiler comparison. There is no runtime tuning, benchmark-seed dependency, worker-count change, table change, GPU change or modified controller. The existing SHA-NI feature gate and target attribute remain sufficient because the candidate uses the same128-bit integer add and unpack operations already present.

## Integer model and actual-source wrappers

A deterministic model checked20,005 groups of four arbitrary final SHA states, including wrapping boundaries around the feed-forward constant and20,000 seeded random groups. It models the original two unpackhi32 operations followed by unpackhi64, and compares extracting after four lane-wise IV additions with one broadcast addition after extraction. Every returned32-bit lane matched, including modulo2^32 wraparound. This tests the output identity on arbitrary final states, rather than restricting evidence to hashes of a few particular keys. It is not execution of SHA-NI or a claim to have benchmarked complete key hashing.

An isolated wrapper was compiled from the exact candidate function and actual SHA constants using GCC13.3 -O3 and the original target attribute. With the switch zero versus one, paddd sites change112->109, movdqa143->141 and movaps2->1; stack-reference sites change4->2. SHA256msg1 remains48, SHA256msg2 remains48 and SHA256rnds2 remains128; palignr remains52. The reduction is small and its aggregate value is unmeasured. The unchanged SHA instruction counts corroborate that this is output feed-forward placement, not a padding or round-count experiment.

## Verification boundaries and performance interpretation

The local machine has no CUDA device and its CPU lacks the target IFMA/SHA-NI execution capability. Native image generation and standard host compilation are compile-only checks. The scalar integer checks are models of the specific mathematical identity, not execution of the intrinsics or an official benchmark. Static instruction counts describe isolated compiler output; they are not executed instruction counts, cycle measurements, cache measurements, throughput or a simulated score. No local runtime gain is claimed.

The complete native build uses CUDA12.8.93, QSB_ZEROS_N=24 and sm_89. The standard host build uses the same compiler version and zero-bit parameter and links the existing crypto and math dependencies. Generated executables, raw cubins and compiler logs remain outside the candidate directory. The generated carrier header is source data required by the existing program and is regenerated through the existing development script. No binary or build stamp is packaged.

The local cuobjdump disassembler crashes. The existing developer-only fallback uses nvdisasm on the same compiled cubin, preserving exact kernel-symbol identification, exact text-section selection and the LTC64B gate. This is not a change to the benchmark harness, scorer, verifier, workflow, elapsed-time accounting, hit accounting or publication validation. The device image is expected to remain byte-identical because this candidate changes CPU code only. Image equality is a useful scope check, not evidence of a host speedup.

A reduction in isolated assembly work is evidence for a mechanism worth assessing, not a promise that the complete workload improves. Full-program inlining, register allocation, instruction scheduling, branch behavior, CPU/GPU overlap and the controller's chosen mode can alter the result. Even a real reduction in one CPU helper can be too small to clear the one-percent promotion threshold. The frontier and the measured official result, rather than static counts, determine success.

## Recovery and dispatch gate

The recovery source patch omits this public note and the generated carrier. Preserve the execution-tree delta before synchronizing to the then-live Yukon source. Confirm actual HEAD against benchmark.sourceRef and inspect the current promoted score and owner. Review the latest completed own result, package overlap and the closed-experiment list before applying the patch. Copy the note, regenerate the source carrier and rebuild if the source has moved or the build evidence no longer corresponds to the exact package. Refresh the subset source-manifest file hashes when applicable.

Immediately before submission, sync again and fetch the full official submission list. Filter exact solverUsername=dukemawex, inspect every own entry and ensure that this track has no active validation. Reapply only the reviewed and compiled delta. Never duplicate or cancel an active job. Bitcoin tracks may operate concurrently; MLX is independent and is not changed by this package. Official Yukon validation is the first complete target execution authorized for this candidate.

This candidate must remain distinct from the then-live source. If a promotion has subsumed it or new evidence makes it unqualified, preserve the record rather than dispatch a repackage merely because a slot is free. A below-frontier score closes the exact package. Noise, runner elapsed-time classification or an attractive unmeasured prediction does not authorize an identical retry. Report officialScore and officialMetrics exactly when available; never replace them with a model score or guarantee promotion.

## Completed compile-only evidence — 2026-09-29

Both the full native carrier generation and standard nvcc host build completed with exit code 0 for this exact source. CUDA 12.8.93 reported 13 spill records, all zero for stores and loads. The exact digest section passed the 3 LTC64B-load gate. The cubin is 462496 bytes, SHA256 f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc, byte-identical to the promoted device image. No executable was run on a GPU or on the target SIMD CPU. These results establish compilation and scope only, not performance.
