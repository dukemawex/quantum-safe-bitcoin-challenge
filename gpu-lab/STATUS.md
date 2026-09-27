# Quantum Safe Bitcoin loop status

Updated 2026-09-27 approximately05:00UTC. Both tracks active; one shared account-wide validation slot.

## Live board and account queue
- Promoted source: f0e453daaf8b1af848e0bf4afd42fb730018c041 (confirmed by subset sync this run).
- Pinning frontier:995329477, cefika54ca2f74.
- Subset frontier:691630437, kshitij-hash d052bc3d.
- Current own in-flight:pinning2402ebc0-b474-4933-bbd7-b716d8717003, validating, GREEN24, parentf0e453d.
- Prior pinningeacbd337 naturally rejected950985831, elapsed1201.0178. Ring6 is closed. No cancellation.
- Own subset in-flight:none.

## Prepared and submitted work
GREEN24 was SUBMITTED; do not resubmit its saved patch. Complete build passed CUDA12.8.93 host compile and full carrier script with NVIDIA nvdisasm fallback. Fourteen zero-spill records, five prepare LTC64B loads, cubin byte-identical625c22c4. No local GPU execution or performance claim. The saved source patch and note remain under gpu-lab/prepared/green24-complete-f0e453d.patch and gpu-lab/submission-note-green24-ready.md; the submitted note also records ring6's rejection and final attribution. Current changes on the local pinning tree are the submitted package.

Neither track currently has a second qualified waiting package. Preparing one for each remains highest priority while2402ebc0 validates. Do not label a hypothesis qualified or fill the slot with an inert replay.

## Subset review this run
Fetched and diffed i34-9eb9ee8f3/9591808166fe1ce417278f66ee4b3032f41bb9fc against promotedf0e453d. It replaces much of CpuGrindSubset.h and host_producers.h, includes blocking waits, and changes a GPU-source default. It also contains a compiled subset executable and .subset.build: never copy those into a candidate. New public note8009bfb9 attributes59.85M CPU throughput to that package versus48.31M at the crown, but its GPU part is634.72M versus643.32M. This is not proof of an independently stackable >1percent total gain. Its co-grinder derives from terrapinelfr7 and includes safegcd, fused arithmetic, prefetch and10-window geometry.
New ercumentyildirim6f332218 reuses the already-scored a7727680 host composition (689.87M) and changes Q_MIX4to2. fkiene8009bfb9 bundles four GPU settings with i34's host; its own note admits that exact host/GPU composition was not measured before submission. Both remain validating. No speculative port or parameter sweep performed. Need isolate and validate a genuine improvement, or wait for stronger ranked evidence, before subset qualification.
Pinning newjordan1a116ba7 and ercumentyildirimb5ed5218 IFMA co-grinder submissions remain validating; their notes identify potentially useful CPU work, not a license to duplicate their unpromoted packages.

## Rules and operational facts
Sync --force before edits and before submit; if tip moves rebuild. Preserve work as patches before sync. It resets local branch HEAD and rewrites origin to upstream, so never rely on origin for fork pushes; use GitHub connector or explicit fork URL. Push only designated branch per track. Exact rejected approaches closed: register-tree combinations, ring6, paired-SHA ALU/unroll subset, PMIX12 warp replay. Never cancel, never fabricate local score/model identity, never alter harness or measurement code. Use actual exposed model/harness attribution and public notes>=5KiB, credit contributors. GPU spend requires prior approval; none incurred.
GitHub connector authenticated asdukemawex with write access. Shell git has no push credentials. Notes persist on claude/magical-allen-bn3ywg. Subset persistence branch claude/awesome-franklin-izo2f3. Scheduled checks are hourly, not a guarantee of immediate dispatch.
