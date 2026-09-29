# Current status — 2026-09-29 07:39 UTC

This header supersedes historical source/queue/readiness labels. Both live source refs advanced to 7813ffe1b7442f4a998e4978834d9ce2bd4559c6. Subset frontier is now 720332123 / kshitij-hash, promoted submission e6715658-2270-4be9-8caa-9a7c7e072dd3 at 2026-09-29 06:27:47.363 UTC. Pinning frontier remains 1008206828 / kaankolcu / b9736ce1-e9d8-4a3c-b163-0deb274afa2d. Shared source movement is from subset promotion; git diff confirms every candidates/pinning file equals old 8d07 base.

Own subset 32002794-e204-49c8-a0db-165b0657cf5d KEY33PAD and pinning dc0d2bd6-f285-48b9-a435-372b8065d36f PARITY_ONLY both remain VALIDATING in fresh official query. No cancellation, duplicate or new submission.

SUBSET H0ADD IS NOW PARKED, NOT READY. Its 8d07 recovery patch fails to apply to the new CpuGrindSubset.h. New promoted defaults include QSB_CPU_KH16=1, QSB_CPU_SHA4=1, QSB_CPU_SHC=1; the old two-pair helper is bypassed in the guarded KH16 path, and fallback SHA4 implementation changed. Do not dispatch the archived H0ADD patch or merely force it onto fallback code. No qualified waiting subset candidate on current source. Next preparation must inventory the new active path and demonstrate a distinct non-inert change. Historical H0ADD patch/note/model retained as research only. Current subset execution tree is clean promoted 7813, not H0ADD. SOURCE-MANIFEST.json was removed by promoted source; do not restore stale old manifest wholesale.

WAITING PINNING KEY_H0ONLY requalified on 7813. Same runtime diff and all pinning base files byte-identical to 8d07; no overlap with subset promotion. Native and standard host CUDA12.8.93 builds both exit0 again; 15 zero-spill records, prepare128/finish64, five LTC64B. Cubin 476832B SHA256913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. New recovery gpu-lab/prepared/key-h0only-7813.patch, note gpu-lab/submission-note-key-h0only-7813.md, evidence gpu-lab/prepared/key-h0only-7813-evidence.json. Recovery omits note/carrier; sync live, apply, copy note, regenerate. Current pinning execution tree holds waiting KEY_H0ONLY. Logs /tmp/qsb-0732/pin-native.log, pin-host.log; raw native /tmp/tmp.hOj9nvqJZp/ptxas.log. Prior exact-source scalar/static checks remain applicable because runtime sources are identical. No local target execution, gain or promotion claim.

Keep all prior closures. New promoted subset inherits formerly isolated closed components including KH16/MRG/X4PS/padding and weighted-prefix/v3 lineage. Preserve promoted inheritance; this does not reopen any closed experiment. Active old-source submissions must finish naturally. Fresh source/result/overlap/own queue review still required before fire. One own active per track; tracks concurrent; MLX independent. NEVER CANCEL.

---

# Current status — 2026-09-29 05:26 UTC

This header supersedes historical active/waiting labels. Live source both tracks remains8d07d3ebad41a017dfaa5906b164f883a9b59348. Pinning best1008206828/kaankolcu; subset best708411009/jacklightChen.

Pinning ZMASK4 0590285a naturally REJECTED973578429 at04:33:54UTC, verified=true,139393 hits,elapsed1201.0468. Exact ZMASK4-only package CLOSED; no retry.
NEW pinning dc0d2bd6-f285-48b9-a435-372b8065d36f submitted05:20:50UTC from freshly synced8d07 after empty own queue. VALIDATING. Isolated PARITY_ONLY canonical Y parity. Native/host rebuilt exit0;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Public note9253B. Archive gpu-lab/prepared/parity-only-submitted-dc0d2bd6.patch and gpu-lab/submission-note-parity-only-submitted.md are SUBMITTED,not waiting. Never cancel/duplicate.

Subset32002794-e204-49c8-a0db-165b0657cf5d KEY33PAD remains VALIDATING. Waiting H0ADD unchanged: candidates/subset/prepared-h0add-8d07.patch SHA2567beebbeb91c1c8ce830777ca7ef9d03a78a3b13d2683731fd11f685d09204dbe; note submission-note-h0add.md8476B;13 zero-spill native/host,unchanged promoted462496B cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc. Original generic key padding and all64rounds remain; no active KEY33PAD in waiting source. Recovery omits note/carrier,refresh manifest hashes.

NEW WAITING PINNING: QSB_CG_KEY_H0ONLY=1, final output handling only for pub_hash8_shani_wm. Shared compression becomes shani_compress2_impl<H0_ONLY>; false wrapper preserves generic full digest. True wrapper extracts lane3 A from each final ABEF vector and adds incoming st[0] modulo2^32,writing only st[0]. Existing caller reads only H0. All64 rounds,schedule,message packing/generic padding and feature gates unchanged; original cpu_cogrind3_ifma.h retained. No active PARITY_ONLY,closedZMASK4/NORM_IFMA/KEY33PAD/SHA32PAD/FSEL3/PACK2/split45/VLSHA/square.
Scalar identity model20004 arbitrary incoming/final states passed with wrapping boundaries; NOT SHA-NI execution. Round/schedule body text equals promoted. Generic false-wrapper assembly equals promoted after label normalization. Actual word-major function/header GCC13.3/O3 sites:paddd58->54,pshufd34->30,pblendw3->1,movq8->6;adds2 pextrd and2 addl;movl6->8,movaps1->2,movdqa113 unchanged. msg1/msg2 remain24,rnds2=64,palignr=25. Stack-reference sites13->14,disclosed. Static counts,not runtime; compiler already removed some unused output work and gain may be negligible/negative or inactive with another controller mode.
Native/host CUDA12.8.93 exit0;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Note10167B. Patch gpu-lab/prepared/key-h0only-8d07.patch SHA256ddae331bf6c5b58f6af4a3bfe9f5d52a968a632985815e61c36dacb86318ff6c; note gpu-lab/submission-note-key-h0only.md; evidence gpu-lab/prepared/key-h0only-evidence.json.
Recovery omits note/carrier:sync live,apply,copy note,regenerate. Current pinning execution tree holds KEY_H0ONLY,not submittedPARITY_ONLY. Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent. Independent adaptation,no donor speed claim or local targetCPU/GPU execution.

One own active per track;tracks concurrent;MLX independent. NEVER CANCEL. Fresh source/result/overlap/blacklist review and own queue before fire; rebuild moved source. No identical/noise retries. Double-subtraction preparation remains abandoned.

---

# Current status — 2026-09-29 03:03 UTC

This header supersedes older active/waiting labels. Both live sources remain 8d07d3ebad41a017dfaa5906b164f883a9b59348. Pinning best 1008206828 / kaankolcu; subset best 708411009 / jacklightChen.

Subset second-SHA32PAD 372154a4 naturally REJECTED 706714889 at 02:46:46 UTC, verified=true, 101268 hits, elapsed1202.0372. Pinning NORM_IFMA bff7e30d naturally REJECTED 987709433 at 02:37:17 UTC, verified=true, 141418 hits, elapsed1201.0619. Both exact packages CLOSED; no retry.

NEW subset 32002794-e204-49c8-a0db-165b0657cf5d submitted 02:53:25 UTC from freshly synced8d07 after empty own queue; VALIDATING in final query. Isolated KEY33PAD compressed-key padding identities. Native/host passed again;13 zero-spill,three LTC64B;462496B cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc equals promoted. Archive candidates/subset/prepared-key33pad-submitted-32002794.patch and submission-note-key33pad-submitted.md are SUBMITTED,not waiting.

NEW pinning 0590285a-eb84-49f8-b1e0-12cd90540b71 submitted 02:53:26 UTC from freshly synced8d07 after empty own queue; VALIDATING in final query. Isolated ZMASK4 direct bit30 broadcast. Native/host passed again;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Archive gpu-lab/prepared/zmask4-submitted-0590285a.patch and gpu-lab/submission-note-zmask4-submitted.md are SUBMITTED,not waiting. Never cancel/duplicate either active.

NEW WAITING SUBSET: QSB_CPU_KEY_H0ADD=1, feed-forward placement only in qsha_keyhash4_h0. Save four final S0 states, retain original H0 unpack order, then one broadcast0x6a09e667 addition replaces four full-register IV additions. All64 rounds and original generic key padding/schedules remain. No active KEY33PAD,closedSHA32PAD/KH16/MRG/X4PS,field/GPU/worker changes.
Integer model20005 groups of four arbitrary final states checked exact unpack order and modulo32-bit wrap. NOT SHA-NI execution. Actual-function GCC13.3/O3 wrapper paddd112->109,movdqa143->141,movaps2->1,stack-reference sites4->2;msg1 remains48,msg2=48,rnds2=128,palignr=52. Static counts,not timings.
Native/host CUDA12.8.93 exit0;13 zero-spill,three LTC64B;462496B cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc equals promoted. Note8476B. Patch candidates/subset/prepared-h0add-8d07.patch SHA2567beebbeb91c1c8ce830777ca7ef9d03a78a3b13d2683731fd11f685d09204dbe; note candidates/subset/submission-note-h0add.md; evidence prepared-h0add-evidence.json.
Credits terrapinelf jacklightChen i34-9 ercumentyildirim HyeokxC RealAdii kshitij-hash fkiene. Independent identity,no donor speed claim. Recovery omits carrier/note: sync live,apply,copy note,regenerate carrier,refresh manifest hashes.

NEW WAITING PINNING: QSB_CG_PARITY_ONLY=1, canonical Y parity only in IFMA key-hash path. fparity preserves fnorm's first-stage folding/carries/exact correction x,then returns(t0^x)&1 since C is odd. Original fnorm unchanged. Production fully normalizes X but passes Y to parity helper; QCG_EC_HOOK keeps full canonical Y for hooks. All field arithmetic,EC recurrence,hashing,packing/controller/GPU unchanged. No activeZMASK4 or closedNORM_IFMA,KEY33PAD,SHA32PAD,FSEL3,PACK2,split45,VLSHA,square.
Scalar model20010 legal limb vectors below2^62 matched full original normalization and bigint modulo-p parity; x0=20005,x1=5 boundary cases. NOT IFMA execution. Actual-header GCC13.3/O3 wrapper old fullfnorm then n0&1 vs helper: vpaddq5->4,vpand6->5,vpternlogq2->3,vpxor1->0,vpor1->0,vpsubq1->0;one IFMA,6 shifts,3 comparisons,zero stack sites both. Compiler already deletes unused high-limb outputs in old wrapper; only small residual change,not a claimed complete second-pass elimination.
Native/host CUDA12.8.93 exit0;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Note8815B. Patch gpu-lab/prepared/parity-only-8d07.patch SHA25660b17dee258d3c74b3f33c3e6c257be75f8fea70fc831c116e26884f578a406f; note gpu-lab/submission-note-parity-only.md; evidence gpu-lab/prepared/parity-only-evidence.json.
Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent. Recovery omits note/carrier: sync live,apply,copy note,regenerate. No local runtime/gain/promotion claim for either waiting package.

One own active per track; tracks concurrent; MLX independent. NEVER CANCEL. Reassess live tip,result,overlap/blacklists and fresh own queue before fire; rebuild moved source. No identical/noise retries. Double-subtraction preparation remains abandoned due misleading alias-wrapper savings and representative stack temporaries.

---

# Current status — 2026-09-29 00:21 UTC

This header supersedes older active/waiting labels. Both live sources remain8d07d3ebad41a017dfaa5906b164f883a9b59348. Pinning best1008206828/kaankolcu; subset best708411009/jacklightChen.

Pinning KEY33PAD92fb758c naturally REJECTED990563285 at00:11:04UTC,verified=true,141823 hits,elapsed1201.0313. Exact KEY33PAD-only package CLOSED; no retry.
NEW pinning bff7e30d-f5de-4d0e-922e-25d70ac99638 submitted00:16:39UTC from fresh8d07 after empty own queue; VALIDATING in final query. Isolated NORM_IFMA final canonical correction. Native/host passed again;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Archive gpu-lab/prepared/norm-ifma-submitted-bff7e30d.patch and gpu-lab/submission-note-norm-ifma-submitted.md are SUBMITTED,not waiting. Never cancel/duplicate.

Subset372154a4-3ead-43c7-b6cc-1b43fa6dd4bd SHA32PAD remains VALIDATING. Waiting subset KEY33PAD unchanged: candidates/subset/prepared-key33pad-8d07.patch and submission-note-key33pad.md9730B;13 zero-spill native/host,unchanged device image. Patch SHA2560032f2431fa298e2e121e25624734d8ff271f45a4ef4ec34c32f62c433d8dc84. No submitted second-SHA32PAD in waiting source.

NEW WAITING PINNING: QSB_CG_ZMASK4=1, direct bit30 broadcast only in CPU IFMA zmask4. Load four32-bit digit words,shiftleft1,arithmeticright31,sign-extend to four64-bit masks. Exact QCG_ZERO semantics for all bit30/31 combinations; lowerbits/signencoding and callers unchanged. No submitted NORM_IFMA,closedKEY33PAD/SHA32PAD/FSEL3/PACK2/split45/VLSHA/square,GPU/controller changes.
Integer model10256 four-lane cases passed,including all256 high-two-bit combinations across fourlanes. NOT SIMD execution. Exact-helper GCC13.3/O3 wrapper:17->3 static vector sites;four->zero stack-reference sites. New vpslld,vpsrad,vpmovsxdq. Static checks only; zero-digit branch may be rare and aggregate benefit negligible,not measured.
Native/host CUDA12.8.93 exit0;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Note9881B,no local runtime/gain/promotion claim.
Patch gpu-lab/prepared/zmask4-8d07.patch SHA256ac1c8b335a2b49f1acf27d418a76b9eb058384f5eaaeaa988c34fce0d7a6deb2; note gpu-lab/submission-note-zmask4.md; evidence gpu-lab/prepared/zmask4-evidence.json. Recovery omits note/carrier: sync live,apply,copy note,regenerate. Current pinning execution tree holds waiting ZMASK4,not submitted NORM_IFMA. Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent.
Abandoned double-subtraction preparation: representative local-output wrapper erased initial apparent arithmetic savings and proposed form materialized stack temporaries. Not qualified or submitted; no revival based on aliasing-wrapper counts.

One own active per track; tracks concurrent; MLX independent. NEVER CANCEL. Reassess live tip,result,overlap/blacklists and fresh own queue before fire; rebuild moved source. No identical/noise retries or targetCPU/GPU execution claims.

---

# Current status — 2026-09-28 22:02 UTC

This header supersedes older active/waiting labels. Live source both tracks remains8d07d3ebad41a017dfaa5906b164f883a9b59348. Pinning best1008206828/kaankolcu; subset best708411009/jacklightChen.

Pinning CPU SHA32PAD246a0544 naturally REJECTED986175788 at21:44:12UTC,verified=true,141208 hits,elapsed1201.1434. Exact second-SHA32PAD-only package CLOSED; no retry.
NEW pinning92fb758c-1b05-4771-ac87-df79ff008fe8 submitted21:59:32UTC from fresh8d07 after empty own queue; VALIDATING in final query. Isolated CPU KEY33PAD word-major compressed-key SHA specialization. Native/host passed again;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Archive gpu-lab/prepared/key33pad-submitted-92fb758c.patch and gpu-lab/submission-note-key33pad-submitted.md are SUBMITTED, not waiting. Never cancel/duplicate.

Subset372154a4-3ead-43c7-b6cc-1b43fa6dd4bd SHA32PAD remains VALIDATING. Waiting subset KEY33PAD unchanged: candidates/subset/prepared-key33pad-8d07.patch and submission-note-key33pad.md9730B;13 zero-spill native/host,unchanged promoted device image. Patch SHA2560032f2431fa298e2e121e25624734d8ff271f45a4ef4ec34c32f62c433d8dc84. No KH16 or submitted second-SHA32PAD in waiting source.

NEW WAITING PINNING: QSB_CG_NORM_IFMA=1, final canonical correction only in CPU IFMA fnorm. Replace t0+=(0-x)&C with QI_LO(t0,x,C), where unchanged exact comparison gives x in{0,1} and C=0x1000003D1; x*C<2^33 so the52-bit low product is exact. All comparisons,carries,masks,outputs and callers unchanged. No submitted KEY33PAD,closedsecond-SHA32PAD,FSEL3,PACK2,split45,VLSHA,square,GPU/controller changes. Independent adaptation of live normalization code.
Scalar model20010 legal limb vectors below2^62 matched old/new exact limbs and big-integer modulo p; x0 in20005 cases,x1 in5 boundary cases. NOT IFMA execution. Actual-source GCC13.3/O3 fnorm wrapper: vpmadd52luq1->2,vpaddq9->8,vpsubq1->0,vpand12->11,vpxor1->0;vmovdqa7 unchanged;total static vector sites53->50,stack-reference sites0 both. Fewer sites do not prove speed; added IFMA latency/port contention can hurt.
Native/host CUDA12.8.93 exit0;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Note9877B,no local runtime/gain/promotion claim.
Patch gpu-lab/prepared/norm-ifma-8d07.patch SHA2562b97b97c61d7a36d7c4e10889250cc929b50372aa5b668518b1c04f737ceb495; note gpu-lab/submission-note-norm-ifma.md; evidence gpu-lab/prepared/norm-ifma-evidence.json. Recovery omits note/carrier: sync live,apply,copy note,regenerate. Current pinning execution tree holds waiting NORM_IFMA,not submitted KEY33PAD. Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent; no new donor import or speed claim.

One own active per track; tracks concurrent; MLX independent. NEVER CANCEL. Reassess live tip,result,overlap/blacklists and fresh own queue before fire; rebuild moved source. No identical/noise retries or local GPU/targetCPU execution claims.

---

# Current status — 2026-09-28 20:04 UTC

This header supersedes older active/waiting labels. Live source both tracks remains8d07d3ebad41a017dfaa5906b164f883a9b59348. Pinning best1008206828/kaankolcu; subset best708411009/jacklightChen.

Pinning FSEL3 70db1d25 naturally REJECTED989496512 at19:26:54UTC,verified=true,141670 hits,elapsed1201.0291. Exact FSEL3-only package CLOSED; no retry.
NEW pinning246a0544-b94c-482f-8b80-2605485d86c1 submitted20:00:48UTC from fresh8d07 after empty own queue; VALIDATING in final refreshed query. Isolated CPU SHA32PAD second-hash specialization in z_shani_2. Native/host passed again;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Archive gpu-lab/prepared/sha32pad-submitted-246a0544.patch and gpu-lab/submission-note-sha32pad-submitted.md are SUBMITTED, not waiting. Never cancel/duplicate.

Subset372154a4-3ead-43c7-b6cc-1b43fa6dd4bd SHA32PAD remains VALIDATING. Waiting subset KEY33PAD unchanged: candidates/subset/prepared-key33pad-8d07.patch and submission-note-key33pad.md9730B;13 zero-spill native/host,unchanged promoted device image. SHA2560032f2431fa298e2e121e25624734d8ff271f45a4ef4ec34c32f62c433d8dc84. No KH16 or submitted second-SHA32PAD in waiting source.

NEW WAITING PINNING: QSB_CG_KEY33PAD=1, exact compressed33-byte-key padding only in pub_hash8_shani_wm. cg_sha.h template shani_compress2_impl<PAD33> preserves generic false wrapper; true loads W8 unchanged,fixes W9..14=0,W15=264,omits zero align/add and identity msg1 at group3. Word-major key-hash call only, used by existing IFMA/AVX2 EC SHA-NI paths; row-major generic path unchanged. No submitted second-SHA32PAD,FSEL3,PACK2,split45,VLSHA,square,GPU/controller changes. cpu_cogrind3.h original promoted.
Structural model2052 messages with both parity prefixes: actual grouped macro ordering generic/specialized64-word schedules matched recurrence and full scalar digest/hashlib; NOT SIMD execution. Actual function/header GCC13.3/O3 sites:msg1 24->22,palignr25->23,paddd58->56,movdqa113->109;msg2 remains24,rnds2 remains64;stack-reference sites13->3. Generic wrapper body identical after label normalization. Static code checks, not runtime/timing.
Native/host CUDA12.8.93 exit0,15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Note9563B; no measured gain/promotion claim. Can be immaterial when controller chooses another mode.
Patch gpu-lab/prepared/key33pad-8d07.patch SHA25644334c8fa91dfcbd64dcf3439b90988d3bfafae72470a90bb3d2d64b2d27111a; note gpu-lab/submission-note-key33pad.md; evidence gpu-lab/prepared/key33pad-evidence.json. Recovery omits carrier/note: sync live,apply,copy note,regenerate carrier. Current pinning execution tree holds waiting KEY33PAD, not submitted second-SHA32PAD. Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent. Independent adaptation of live pinning code; fixed-padding observation shared with terrapinelf/subset lineage, no donor speed claim.

One own active per track; tracks concurrent; MLX independent. NEVER CANCEL. Reassess live tip,result,overlap/blacklists and fresh own queue before fire; rebuild moved base. No identical/noise retries,local GPU or target CPU execution claim.

---

# Current status — 2026-09-28 19:11 UTC

This header supersedes older active/waiting labels. Live source both tracks remains 8d07d3ebad41a017dfaa5906b164f883a9b59348. Subset best708411009/jacklightChen; pinning best1008206828/kaankolcu.

Subset KH16 93f29ce8 naturally REJECTED702231211 at18:29:37UTC, verified=true,100616 hits,elapsed1201.9235. Exact KH16-only package CLOSED; no retry.
NEW subset372154a4-3ead-43c7-b6cc-1b43fa6dd4bd submitted19:07:01UTC from fresh8d07 after empty own queue; VALIDATING in final query. Isolated SHA32PAD second-hash scheduling. Native/host passed again;13 zero-spill,three LTC64B;462496B cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc equals promoted. Archive candidates/subset/prepared-sha32pad-submitted-372154a4.patch and submission-note-sha32pad-submitted.md are SUBMITTED records. Never cancel/duplicate.

Pinning70db1d25-2458-4a1b-884a-7ef30113afc1 FSEL3 remains VALIDATING. Waiting pinning CPU SHA32PAD unchanged: gpu-lab/prepared/sha32pad-8d07.patch and submission-note-sha32pad.md11290B;15 zero-spill host/native,unchanged promoted image. This two-stream pinning adaptation is independent of subset's four-message second-SHA specialization.

NEW WAITING SUBSET: QSB_CPU_KEY33PAD=1, exact padding identities only in qsha_keyhash4_h0, the promoted CPU compressed33-byte-key function. Omit zero align/add at group r4 and identity msg1 at r6; original packing, two-pair grouping, all64 rounds/feedforward/h0 extraction retained. No submitted second-SHA32PAD, closedKH16/MRG/X4PS, worker/table/field/GPU changes. Fixed-padding observation shared with terrapinelf lineage; narrow implementation independently adapted to current live loop.
Structural model2052 messages, both parity prefixes, arbitrary coordinate bytes: generic/specialized grouped64-word schedules matched scalar recurrence and full digest/hashlib. NOT SIMD execution. Actual-source GCC13.3/O3 wrappers: msg1 48->44,alignr52->48,add112->108;msg2 remains48,rnds2 remains128;stack-reference sites4 both. Static code counts, not timing.
Native/host CUDA12.8.93 exit0,13 zero-spill,three LTC64B;462496B cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc equals promoted. Note9730B; no local runtime/gain/promotion claim.
Patch candidates/subset/prepared-key33pad-8d07.patch SHA2560032f2431fa298e2e121e25624734d8ff271f45a4ef4ec34c32f62c433d8dc84; note candidates/subset/submission-note-key33pad.md; evidence prepared-key33pad-evidence.json. Recovery omits note/carrier: sync then-live source,apply,copy note,regenerate carrier,refresh manifest hashes. Current subset execution tree holds waiting KEY33PAD, not submitted second-SHA32PAD.
Credits terrapinelf jacklightChen i34-9 ercumentyildirim HyeokxC RealAdii kshitij-hash fkiene. No donor speed claim; donor broader704265138 confounded. This CPU compressed-key specialization is distinct from closed GPU SHA experiments.

One own active per track; tracks concurrent; MLX independent. NEVER CANCEL. Fresh live-source/result/overlap review and own queue check before fire; rebuild moved source. All prior blacklists retained, no identical/noise retries. No local GPU or target CPU execution claimed.

---

# Current status — 2026-09-28 17:51 UTC

This header supersedes older active/waiting labels. Live source for both tracks remains 8d07d3ebad41a017dfaa5906b164f883a9b59348. Pinning best 1008206828 / kaankolcu; subset best 708411009 / jacklightChen.

Pinning PACK2 e03499b9 naturally REJECTED 987866809 at 16:39:52 UTC, verified=true, 141440 hits, elapsed1201.0574. Exact PACK2-only package CLOSED; no retry.
NEW pinning 70db1d25-2458-4a1b-884a-7ef30113afc1 submitted 17:46:56 UTC from fresh8d07 after empty own queue; VALIDATING in final query. Isolated FSEL3 whole-lane ternary selection. Native/host builds passed again; 15 zero-spill, prepare128/finish64, five LTC64B; 476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Archive gpu-lab/prepared/fsel3-submitted-70db1d25.patch and gpu-lab/submission-note-fsel3-submitted.md are SUBMITTED records. Never cancel/duplicate.

Subset 93f29ce8-e3b8-4881-88f1-8400270e5a44 KH16 remains VALIDATING. Waiting subset SHA32PAD unchanged: candidates/subset/prepared-sha32pad-8d07.patch and submission-note-sha32pad.md9756B; 13 zero-spill host/native, unchanged promoted image.

NEW WAITING PINNING: QSB_CG_SHA32PAD=1, fixed32-byte second-SHA in CPU z_shani_2 only. cg_sha.h generic body becomes compile-time shani_compress2_impl<PAD32>; false wrapper preserves generic callers, true wrapper fixes W8/W15 and removes zero align/add plus identity msg1 at group3. Only DA/DB second-hash call changes. Full64 rounds/all8 words/feedforward preserved; original first tail hash, keyhash, field arithmetic/selection/packing, GPU and controller retained. No submitted FSEL3 or closed PACK2/split45/VL SHA/square.
Structural model1026 messages compared generic/specialized grouped64-word schedules to scalar recurrence and full digest to hashlib; NOT SHA-NI execution. Actual-header GCC13.3/O3 wrappers: msg1 23->22, msg2 24->24, rnds2 64->64, palignr27->26, paddd56->54, movdqa117->116; stack references14 both. Compiler already shares some padding work, so small static difference only, not timing. Generic compiled wrapper body identical after label normalization.
Native/host CUDA12.8.93 exit0;15 zero-spill, prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Note11290B; no local runtime/gain/promotion claim. Could be inert at runtime if controller uses another hashing mode.
Patch gpu-lab/prepared/sha32pad-8d07.patch SHA2568c569e1c1fbbd4620cb5593dac8506cd2e731acde1bfeb84e13eed4144ed2cd1; note gpu-lab/submission-note-sha32pad.md; evidence gpu-lab/prepared/sha32pad-evidence.json. Recovery omits note/carrier: sync live, apply, copy note, regenerate carrier. Current pinning execution tree holds waiting SHA32PAD, not submitted FSEL3.
Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent. Independent pinning adaptation from live code; fixed-padding observation shared with subset/terrapinelf lineage, no donor speed claim. This CPU two-stream change is distinct from closed GPU SHA experiments.

One own active per track; tracks concurrent; MLX independent. NEVER CANCEL. Assess live tip/result/overlap and fresh queue before fire, rebuild moved base. All prior blacklists retained; no identical/noise retries.

---

# Current status — 2026-09-28 14:35 UTC

This header supersedes older active/waiting labels. Live source both tracks remains 8d07d3ebad41a017dfaa5906b164f883a9b59348. Pinning best1008206828/kaankolcu; subset best708411009/jacklightChen.

Pinning split45 29be6313 naturally REJECTED991168381 at14:18:08UTC, verified=true,141915 hits,elapsed1201.0768. Exact split45-only package CLOSED; no retry.
NEW pinning e03499b9-f873-4d6d-ab67-63b5f2649159 submitted14:29:34UTC on fresh8d07 after empty own queue; VALIDATING in final query. Isolated PACK2 two-source packing. Native/host builds passed again;15 zero-spill,prepare128/finish64,five LTC64B,476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Archive gpu-lab/prepared/pack2-submitted-e03499b9.patch and gpu-lab/submission-note-pack2-submitted.md are SUBMITTED records, not waiting. Never cancel/duplicate.

Subset93f29ce8-e3b8-4881-88f1-8400270e5a44 KH16 remains VALIDATING. Waiting subset SHA32PAD unchanged: candidates/subset/prepared-sha32pad-8d07.patch and submission-note-sha32pad.md9756B;13 zero-spill host/native, unchanged promoted device image.

NEW WAITING PINNING: QSB_CG_FSEL3=1. Whole-lane CPU IFMA fsel uses native ternary logic immediate0xca with arguments mask,a,b. All current masks from zmask4/negmask4 are whole-lane zero/all-ones; exact byte-blend semantics preserved. Original fmul/fsqr/SHA/packing and policies retained; no active PACK2, closed split45, VL SHA or symmetric square.
Structural truth table8 cases and10032 four-lane cases with all16 mask combinations passed; not SIMD execution. Exact-source GCC13.3/O3 isolated wrapper old:5 blends+1 compare+1 xor+11 moves; new:5 ternary+14 moves. Total static vector sites18->19,zero stack references both. Extra moves disclosed; fewer selection operations do not prove speed.
Host/native CUDA12.8.93 pass;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. No local runtime or measured gain.
Patch gpu-lab/prepared/fsel3-8d07.patch SHA256939bf36fde6aed53db1d7a1e8ea9a7c9e999c6b03c9aef199e03bcc5b519c5c1; note gpu-lab/submission-note-fsel3.md11286B; evidence gpu-lab/prepared/fsel3-evidence.json. Recovery omits carrier/note: sync current live source, apply, copy note, regenerate carrier. Current pinning worktree contains FSEL3 waiting, not submitted PACK2.
Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent.

One own active per track; tracks concurrent; MLX independent. NEVER CANCEL. Fresh sync/result/overlap review required before dispatch; all blacklists retained, no identical/noise retries. No guaranteed promotion.

---

# Current status — 2026-09-28 13:45 UTC

This header supersedes historical active/waiting labels. Both live sources remain 8d07d3ebad41a017dfaa5906b164f883a9b59348. Subset best708411009/jacklightChen; pinning best1008206828/kaankolcu.

Subset X4PS9ae6f186 naturally REJECTED701339295 at13:25:38UTC, verified=true,100488 hits,elapsed1201.921. Exact X4PS-only package CLOSED; no retry.
NEW subset93f29ce8-e3b8-4881-88f1-8400270e5a44 submitted13:40:39UTC from fresh8d07 after empty own queue; VALIDATING. Isolated KH16 sixteen-key SHA scheduling. Host/native builds passed again;13 zero-spill,three LTC64B,462496B cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc equals promoted. Archive candidates/subset/prepared-kh16-submitted-93f29ce8.patch and submission-note-kh16-submitted.md are SUBMITTED, not waiting. Never cancel/duplicate.

Pinning29be6313-9540-474a-bd9e-91a7ebce2708 split45 remains VALIDATING. Waiting PACK2 unchanged: gpu-lab/prepared/pack2-8d07.patch and submission-note-pack2.md9753B, source8d07;host/native15 zero-spill,unchanged promoted GPU image. No new pinning submission this check.

NEW WAITING SUBSET: QSB_CPU_SHA32PAD=1, isolated fixed32-byte second-SHA schedule from terrapinelf a33e04c3/source87d9ebfd20a635536b69fa24dbcc60b1a6dce7e3. Only donor qsha_xw_iv32/qsha_x4w_iv32 and the unique planned second-hash call are imported. No keyhash SHC, KH16, MRG, X4PS, worker/table/prefetch/GPU changes. Fixed W9..W14 zeros remove r4 align/add and make r6 msg1 identity; all rounds/full output preserved. Structural model1026 arbitrary32-byte messages matched all64 recurrence words and full scalar digest vs hashlib; NOT SIMD execution. Isolated compiler counts msg1 48->44,alignr52->48,add120->108;msg2 remains48,rnds2 remains128. Static sites, not timings.
Host/native CUDA12.8.93 builds pass;13 zero-spill,three digest LTC64B;462496B cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc equals promoted. Patch candidates/subset/prepared-sha32pad-8d07.patch SHA2561f47c2bdc9781008826367f01326eba42b34cff0f29061c60881f3da7068bc99; note candidates/subset/submission-note-sha32pad.md9756B; evidence prepared-sha32pad-evidence.json. Recovery omits carrier/note: sync live source, apply patch, copy note, regenerate carrier and refresh manifest file hashes. Current subset worktree holds waiting SHA32PAD, not submitted KH16.
Credits terrapinelf jacklightChen i34-9 ercumentyildirim HyeokxC RealAdii kshitij-hash fkiene. Donor's overall704265138 was confounded; no isolated speed claim or promised promotion.

One active per Bitcoin track; tracks concurrent; MLX independent. NEVER CANCEL. Assess result/tip/overlap, sync immediately before fire and rebuild moved base. All prior blacklists retained; no identical/noise retries. No local GPU or target CPU runtime claims.

---

# Current status — 2026-09-28 12:41 UTC

This header supersedes historical queue/candidate labels. Both live sources remain 8d07d3ebad41a017dfaa5906b164f883a9b59348. Subset best708411009/jacklightChen; pinning best1008206828/kaankolcu.

Pinning VL SHA e130e912 naturally REJECTED981787755 at11:56:43UTC, verified=true,140572 hits,elapsed1201.0777. Exact VL SHA-only package CLOSED; no retry.
NEW pinning29be6313-9540-474a-bd9e-91a7ebce2708 submitted12:38:13UTC from fresh8d07 after empty own queue; VALIDATING in final refreshed query. Isolated QSB_CG_SPLIT45 field-column scheduling. Host/native builds passed again;15 zero-spill,prepare128/finish64,five LTC64B,476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Archive gpu-lab/prepared/split45-submitted-29be6313.patch and gpu-lab/submission-note-split45-submitted.md are SUBMITTED records. Never cancel/duplicate.

Subset9ae6f186-00d1-4004-88f3-6331eb838c98 X4PS remains VALIDATING. Waiting KH16 remains unchanged on8d07: candidates/subset/prepared-kh16-8d07.patch and submission-note-kh16.md10155B; native/host passed13 zero-spill,unchanged device image.

NEW WAITING PINNING: QSB_CG_PACK2=1, direct two-source dword selection only in IFMA hash_block packing. It replaces eighteen one-source permutations and nine blends with nine two-source permutations; original fmul/fsqr/SHA and all promoted policies retained. No active split45 or closed VL SHA/square. Existing IFMA F/VL runtime gate covers the instruction. Plus/minus lane ordering preserved before either SHA-NI or vector hash path.
Lane model10018 input pairs x2 mappings passed; includes all16 lane basis positions. Isolated actual-source compiled wrappers:18 vpermd+9 vpblendd ->2 vpermi2d+7 vpermt2d; vmovdqa13->21,vmovdqu64 remains8; total static vector sites50->40,stack-reference sites14 in both. These are static counts, not runtime/performance.
Native/host CUDA12.8.93 builds pass;15 zero-spill,prepare128/finish64,five LTC64B,476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Note9753B.
Patch gpu-lab/prepared/pack2-8d07.patch SHA256531e5ce7b490debbf6d59cdcde28c669697cae2401ab20a6a2c32b1cf087f22e; note gpu-lab/submission-note-pack2.md; evidence gpu-lab/prepared/pack2-evidence.json. Recovery omits carrier/note: apply to then-live sync, copy note and regenerate. Current pinning worktree contains PACK2 waiting, not submitted split45.
Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent. No measured gain or promised promotion.

One active per track, tracks concurrent, MLX independent. NEVER CANCEL. Fresh sync/queue/overlap review required before any dispatch; preserve blacklists. No GPU runtime or target CPU execution claimed.

---

# Current status — 2026-09-28 10:08 UTC

This header supersedes historical active/waiting labels below. Both tracks remain on live source 8d07d3ebad41a017dfaa5906b164f883a9b59348. Subset best708411009/jacklightChen; pinning best1008206828/kaankolcu.

Pinning symmetric-square489fa7b9 naturally REJECTED979150238 at09:35:29UTC, verified=true,140252 hits,elapsed1201.5715. Exact symmetric-square package CLOSED; no retry.

New pinning e130e912-8b10-4d44-9c0c-1426fc5055d4 submitted10:03:56UTC from freshly synced8d07 after empty own queue. VALIDATING. Isolated QSB_CG_VL_SHA native256-bit rotates; original promoted field arithmetic. Host/native builds passed again;15 zero-spill records,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Archive gpu-lab/prepared/vlsha-submitted-e130e912.patch and gpu-lab/submission-note-vlsha-submitted.md are SUBMITTED, not waiting. No cancellation.

Subset9ae6f186-00d1-4004-88f3-6331eb838c98 X4PS remains VALIDATING. Waiting KH16 remains unchanged on8d07: candidates/subset/prepared-kh16-8d07.patch and submission-note-kh16.md,10155B. Native/host passed13 zero-spill,unchanged device image. Do not duplicate current active.

NEW WAITING PINNING: QSB_CG_SPLIT45=1 splits the high/low accumulators in CPU IFMA fmul columns c4/c5 only. Each nine-update recurrence becomes independent4/5-update branches plus one add. Every product and reduction preserved; no VL SHA, symmetric square, GPU/host-policy changes. Structural model20004 legal W-form input pairs matched exact unreduced columns. Isolated compiled wrappers both62 IFMA sites, adds10->12,zero stack-reference sites; these are static code checks, not timings. Native/host CUDA12.8.93 builds passed;15 zero-spill,prepare128/finish64,five LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Extra adds/register pressure can hurt; no measured gain or promised promotion.
Patch gpu-lab/prepared/split45-8d07.patch SHA25677cb0a928f8ae67d440d6afa896d8bc62ef463d2a18653075856d09654a23395; note gpu-lab/submission-note-split45.md9326B; evidence gpu-lab/prepared/split45-evidence.json. Recovery patch omits carrier/note: apply to fresh then-live source, copy note and regenerate carrier. Current pinning tree holds waiting split45, not submitted VL SHA.
Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent.

One own active per Bitcoin track; tracks concurrent; MLX independent. NEVER CANCEL. At natural completion reassess result/tip/overlap and rebuild on moved source before dispatch. All previous blacklists remain; no identical/noise retries. No local CPU/GPU runtime or performance claim.

---

# Current status — 2026-09-28 08:15 UTC

This header supersedes older active/waiting labels. Source both tracks8d07d3ebad41a017dfaa5906b164f883a9b59348; subset best708411009/jacklightChen; pinning best1008206828/kaankolcu.

Subset MRG d1cb6d56 naturally REJECTED703871269 at07:26:47UTC. Exact MRG-only package CLOSED. No noise retry.
New subset9ae6f186-00d1-4004-88f3-6331eb838c98 submitted08:10:02UTC from fresh8d07 after empty own queue, status VALIDATING. Isolated X4PS shared immutable schedule loads. Host/native builds exit0 again,13 zero-spill records,3 LTC64B,cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc unchanged. Actual GPT/Codex attribution and coauthors. Archive candidates/subset/prepared-x4ps-submitted-9ae6f186.patch and submission-note-x4ps-submitted.md are SUBMITTED, not waiting.
Pinning489fa7b9-6ce4-4e0a-88d5-f0902a350ed5 (symmetric IFMA square) remains VALIDATING. Never cancel/duplicate either active.

WAITING SUBSET: isolated QSB_CPU_KH16 from terrapinelf a33e04c3/source87d9ebfd20a635536b69fa24dbcc60b1a6dce7e3. Sixteen compressed-key messages use AVX512 schedule expansion and four SHA-NI chains; guards preserve fallback, bad masks and exact host gate. Includes only required KH16 functions, buffers/context/call sites; no MRG/X4PS/SHC/worker/table/prefetch/GPU changes. Donor reports+1.17% CPU-only; not our timing and not aggregate prediction; complete donor official704265138 is confounded. Model3232 messages passed serialization, recurrence, round-pair addressing and scalar digest vs hashlib, NOT SIMD execution. Native/host CUDA12.8.93 exit0,13 zero-spill,3 digest LTC64B,462496B cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc equals promoted. Patch candidates/subset/prepared-kh16-8d07.patch SHA256bf8f1a0deee72644d5e993a47ea0801dd6742ded0c0880dd79aa3466da89dd2a; note candidates/subset/submission-note-kh16.md10155B. Recovery patch omits note/carrier; copy note and regenerate carrier. Source manifest updated. Credits terrapinelf jacklightChen i34-9 ercumentyildirim HyeokxC RealAdii kshitij-hash fkiene. Current subset execution tree holds waiting KH16, not submitted X4PS.

WAITING PINNING unchanged: QSB_CG_VL_SHA=1 explicit256-bit rotates only in IFMA vector-hash branch, original promoted fsqr retained. Patch gpu-lab/prepared/vlsha-8d07.patch; note gpu-lab/submission-note-vlsha.md. Builds passed15 zero-spill,5 LTC64B,476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. No local runtime score.

One own active per track; Bitcoin tracks concurrent; MLX independent. Never cancel. Before dispatch sync then-live source and assess result/overlap. No promised promotion. All prior blacklists remain. Preserve live inherited components without reopening old experiments.

---

# Current status — 2026-09-28 07:19 UTC

This header supersedes historical active/waiting labels below.
Live source both tracks: 8d07d3ebad41a017dfaa5906b164f883a9b59348. Subset best708411009/jacklightChen5c7e36c5; pinning best1008206828/kaankolcu b9736ce1.

Pinning HIGH15-only3d812741 naturally rejected922059642 at06:13:20UTC. Exact isolated package CLOSED; no replay. The live promoted source contains inherited HIGH15 components; this does not reopen that experiment.
Pinning489fa7b9-6ce4-4e0a-88d5-f0902a350ed5 submitted07:14:56UTC on fresh live8d07 after empty own queue and remains VALIDATING. This is the symmetric IFMA CPU square. Host/native builds passed again;15 zero-spill records;prepare128/finish64;5 LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Public note10307B, actual GPT/Codex metadata and coauthors. Archive gpu-lab/prepared/ifma-square-submitted-489fa7b9.patch and gpu-lab/submission-note-ifma-square-submitted.md. This is SUBMITTED, not waiting.
Subset d1cb6d56-457b-4ee8-9f48-2b4af9b11bcc (MRG) remains VALIDATING. Never cancel or duplicate either active package.

WAITING SUBSET: X4PS on8d07 unchanged; patch candidates/subset/prepared-x4ps-8d07.patch and note candidates/subset/submission-note-x4ps-8d07.md. Builds already passed13 zero-spill/native+host; carrier f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc equals promoted. No MRG in waiting source.

NEW WAITING PINNING: QSB_CG_VL_SHA=1, explicit 256-bit native rotates for four SHA sigma helpers only in IFMA EC vector-hash branch. Original promoted fsqr/fmul retained; no submitted square. Copied compression schedule/round body text matches original after helper/macro/target substitutions. Existing IFMA dispatch already requires F/VL; SHA-NI and AVX2-only paths unchanged. Integer model20034 words x4 functions passed. Compiled wrapper comparison:1411->948 static vector instruction sites,544->32 shift sites,0->256 rotate sites,80->60 stack references. These are static code sites, NOT executed instructions or timings.
Host/native CUDA12.8.93 builds exit0;15 zero-spill records;prepare128/finish64;5 LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 equals promoted. Patch gpu-lab/prepared/vlsha-8d07.patch SHA2564f9a5e50b82773fc5133f561363cad2d8734c4a007a93081067ef954b7ad273d; note gpu-lab/submission-note-vlsha.md9081B. No local CPU/GPU runtime or measured gain. May have no benefit when controller selects SHA-NI. Credits kaankolcu terrapinelf ercumentyildirim cefika DPZZxlz hybridnoise i34-9 ItlaStudent. Recovery patch omits note/carrier; copy note and regenerate carrier. Current pinning worktree contains waiting VL SHA, not submitted square.

One own active per track; concurrent tracks and MLX independence. Never cancel. Sync/reassess then-live source, result and overlap before dispatch. No guaranteed promotion. Preserve all prior blacklists and no noise retries. W8, weighted-prefix and v3 producer waiting archives remain subsumed.

---

# Current Bitcoin frontier status — 2026-09-28 05:19 UTC check

This header supersedes historical candidate and queue labels below.

Live source for both tracks: 8d07d3ebad41a017dfaa5906b164f883a9b59348.
Subset best 708411009 / jacklightChen 5c7e36c5. Pinning best 1008206828 / kaankolcu b9736ce1.
Own subset d1cb6d56-457b-4ee8-9f48-2b4af9b11bcc (MRG) and pinning 3d812741-55ac-4d00-bf10-8a40ce7ac5f0 (HIGH15) remain validating in refreshed queries. Both were submitted from former tip6343a38 and must finish naturally. No submission or cancellation this check.

Waiting subset: X4PS shared immutable SHA-schedule loads, rebased to8d07. Native/host builds exit0,13 zero-spill records,3 digest LTC64B, cubin462496B SHA256 f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc equals promoted. Patch candidates/subset/prepared-x4ps-8d07.patch; note candidates/subset/submission-note-x4ps-8d07.md. No active MRG or other knobs in this waiting package.

Old waiting pinning W8 is SUBSUMED: new promoted code already enables QSB_FIN_W8S0. Never submit that archive.
New waiting pinning: symmetric IFMA CPU square in cpu_cogrind3_ifma.h, QSB_CG_IFMA_SQR=1, inheriting all promoted GPU/host policy unchanged. Ten off-diagonal products are computed once and doubled, plus five diagonal products; unchanged reduction. Structural model 20002 cases passed; isolated compiled wrappers show62 versus42 IFMA instructions including reduction, no stack references. Neither is a runtime speed measurement. Native/host builds exit0;15 zero-spill records;prepare128/finish64;5 prepare LTC64B;476832B cubin913a97b2a8e6354e7632a2f41a997a05bf0e61e5a8b9a5c5c793f931e983b463 exactly promoted. Patch gpu-lab/prepared/ifma-square-8d07.patch SHA2564a420022c9a17ff70602da2e3ae85093d6cf8762fc1951c3cf642f5922545544; note gpu-lab/submission-note-ifma-square.md9804B. Attribution terrapinelf symmetric-square lineage, kaankolcu current base and cited co-grinder lineage. No GPU/CPU runtime or measured aggregate gain claimed.

Both recovery patches omit generated carrier and note. Apply to freshly synchronized live source, copy corresponding note, regenerate carrier, assess current results and overlap before dispatch. Current execution worktrees contain waiting candidates. Do not duplicate active submissions. One active per track; never cancel; MLX independent. Compile-qualified evidence-backed hypotheses are authorized but promotion is uncertain. No identical/noise retries or blacklisted combinations. Inherited promoted register-root code does not reopen that investigation.

---

# Bitcoin frontier loop — 2026-09-28 04:03 UTC

Latest user authorization: "Submit them. Let's see the possibility." Evidence-backed compile-qualified hypotheses may be tested on Yukon. No measured local gain is required and no promotion is guaranteed. One own active per Bitcoin track; tracks concurrent; MLX independent. NEVER CANCEL.

## Live frontier and active packages
Source for both: 6343a38d3dde830b079cb95b0e2e99c7f9a812e9.
Subset best708411009 / jacklightChen5c7e36c5. Pinning best995329477 / cefika54ca2f74.
- Subset d1cb6d56-457b-4ee8-9f48-2b4af9b11bcc VALIDATING, submitted04:00:58UTC from fresh6343a38 with empty own queue. Isolated QSB_CPU_MRG: merged IFMA product-column accumulators from terrapinelf87d9ebfd/a33e04c3. All other host/device policy remains promoted. Donor reports+1.21% CPU-only, not an aggregate prediction. Structural model checked all50 terms and20,004 seeded cases; not native execution. Host/native exit0,13 zero-spill records,3 digest LTC64B,cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc byte-identical promoted. Coauthors terrapinelf i34-9 cefika ercumentyildirim HyeokxC RealAdii kshitij-hash fkiene. Archive candidates/subset/prepared-mrg-submitted-d1cb6d56.patch and submission-note-mrg.md are SUBMITTED, not waiting.
- Pinning3d812741-55ac-4d00-bf10-8a40ce7ac5f0 VALIDATING, isolated HIGH15_NOFB, submitted03:55:17UTC from6343a38. Never duplicate or cancel. Older high15 patch is SUBMITTED.

## Waiting subset: X4PS only
On6343a38, original field multiplication; no MRG, KH16, SHC, worker, prefetch, table or GPU edits.
Imports only qsha_x4p from terrapinelf87d9ebfd/a33e04c3 and QSB_CPU_X4PS=1.
When four immutable schedule pointers are identical, load each W+K pair once and apply to all four independent SHA states; original path for unequal pointers. Same per-lane operation order and input words. No isolated performance measurement claimed.
Host/native builds exit0;13 zero-spill records;3 LTC64B;462496B cubin f74548427859ec03273f05e9151c810716c6475596e0213a0db3915e468aa5dc matches promoted.
Patch candidates/subset/prepared-x4ps-6343.patch SHA2562620b2e2e6dcc6bb1538d23931ece952a080abce68b2b33cb1c1f7fa0e5d96d1; note candidates/subset/submission-note-x4ps.md, over8KiB.
Recovery patch omits carrier and note; apply code patch, copy note, regenerate carrier. Current subset worktree contains waiting source, not submitted MRG.
Assess MRG result/current tip/overlap first. Do not submit while d1cb active. This candidate is not a measured frontier-beater.

## Waiting pinning: W8 sigma identity only
On6343a38, promoted coefficient fallback and zero-half checks retained. No HIGH15, NZ, carry, slots, register-root or host-policy changes.
QSB_FIN_W8S0=1 from ercumentyildirim c12006c2/source2bf8415: exact small-sigma expression for padded W8=(byte<<24)|0x800000. Exhaustive integer identity checked for all256 bytes; no native GPU test.
Host/native exit0;14 zero-spill records;prepare128/finish64;5 prepare LTC64B;391072B cubin f736ae0220e786931a0c69f2117610aa908c88e491fd93989e0a14647090fb3c differs from base.
Patch gpu-lab/prepared/w8s0-6343.patch SHA2562bbb1bc616e7f7486c2a29c05b878aadfc360d458ddfaead8a4e82606827f957; note gpu-lab/submission-note-w8s0.md, over8KiB.
Recovery patch omits carrier and note; apply code patch, copy note, regenerate carrier. Current pinning worktree contains W8 waiting source, not submitted HIGH15.
Credits ercumentyildirim cefika DPZZxlz terrapinelf hybridnoise. Assess current active result/tip/overlap first. No isolated speed claim.

## Closed and subsumed
Pinning: GLV_NZ925750928; T5V923684990; SAS2-only965644964; paired128963230719; slots3; PMIX per-warp; busy counters; GREEN24; ring6; dualroot; RegisterRoots/WarpInverse/CyclicField compositions. ADDOFF/deferred-Qy prep spilled; chain-P inert.
Subset: Q_MIX2-only691857188; L2cap24; v3+r7; isolated r7; paired-SHA ALU/unroll; prep overlap; split verify; flag sweeps; chain-loop unroll/spills; GPU affine batch chain. Weighted-prefix and v3-producer waiting patches SUBSUMED by promoted trees.
No identical/noise retries or arbitrary sweeps.

## Operation and recovery
Read latest status first. Source patches and notes are saved on designated fork branches; those branches are archives and may not directly contain executable candidate source.
Before edits/fire preserve delta, Yukon sync --force, verify source/score/owner, reassess and rebuild if moved. Immediately before submit re-sync and check own queue. Do not run git fetch concurrently with Yukon sync: both touch FETCH_HEAD and can select the wrong source! Confirm actual HEAD against benchmark sourceRef after sync.
No local GPU available; CPU advertises neither IFMA nor SHA-NI. Build/model checks are not runtime scores. CUDA12.8.93 full native/host builds required, retain exact symbol/LTC64B checks and existing nvdisasm fallback. Notes>=5KiB honest; actual GPT(exact variant not exposed)/Codex metadata; proper space-separated coauthors. Candidate-directory code only, no harness/scorer/measurement edits/binaries/stamps. No GPU spend.
