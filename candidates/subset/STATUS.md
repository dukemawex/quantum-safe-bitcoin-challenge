# Current status — 2026-09-27
Both Bitcoin tracks are active, one own validation per track. MLX is independent. Never cancel.

Live promoted source: f0e453daaf8b1af848e0bf4afd42fb730018c041.
Subset best 691630437 / kshitij-hash d052bc3d. Pinning best 995329477 / cefika 54ca2f74.

Subset 49f1ab79-c0e9-4723-828b-85d592210957 naturally rejected at 693254524, updated 12:09:08 UTC. It beat the live score by 0.2348%, but missed the required 1% promotion margin. Verified=true, elapsed1201.8168,99321 hits. This does not establish repeatable gain; no identical retry.

NEW subset 9d56c6fb-8e8b-43fc-abdf-774fb631ef56 submitted and validating. Base freshly synchronized f0e453d, live best unchanged, own subset queue empty before fire. Mechanism: v3 cached SHA schedules for the three floating host producers, composed with the previously tested r7 CPU lane. Keeps original spinning waits/main-core reservation and unchanged GPU code. Producer header is byte-identical to ercumentyildirim donor3b4fce1213a41ab5e2e96d7f038fdd88a07f2878 (a141df2b); donor's published score696429794 and component evidence are confounded and not claimed as this candidate's performance. Credits terrapinelf ercumentyildirim i34-9 Ryun1 Meganpark980320 kshitij-hash fkiene.

Full native carrier build and standard host nvcc build exit0.13 native zero-spill records. Cubin91948fc251250a6607615c28327b62892a26cc7ef1d62047eb9e42148fdb98b1 byte-equals frontier.3 digest LTC64B loads. tree.cu unchanged. Note9552 bytes. No local GPU/runtime/score claim; actual GPT(exact variant not exposed)/Codex metadata.

Archive: candidates/subset/prepared-r7-v3-f0e453d.patch and candidates/subset/submission-note-r7-v3.md. These are SUBMITTED records, not a waiting candidate. Older r7 patch is also submitted; do not replay.

Pinning07af5750-deb9-450f-91cc-e759f5ee4a5b remained validating at this check. Its busy-counter patch/note are archived on the pinning branch. Do not duplicate or cancel.
No qualified replacement waiting candidate for either track yet. Continue preparing credible distinct replacements on live tip while these validations run.

Closed pinning: GREEN24 958188986; ring6 950985831; dualroot953239579; RegisterRoots/WarpInverse/CyclicField combinations; PMIX12 warp replay draft dropped. Closed subset: paired-SHA ALU/full unroll, prep overlap, split verify, flag sweeps, chain-loop unroll/spills, GPU affine batch chain. A scored rejection below tip closes its exact approach; elapsed classes never justify identical retries.

Before edits/submission save delta, yukon sync --force, confirm live base, reassess/rebuild if moved. Only candidates/<track>/ executable changes, no harness/measurement changes, no binaries/stamps. Notes>=5KiB, actual attribution and proper coauthors. No GPU spend. Fetch explicit fork refs before connector commits and force:false updates; sync rewrites origin to upstream. Only designated branches.
