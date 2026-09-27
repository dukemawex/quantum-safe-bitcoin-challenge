# QSB loop status — 2026-09-27 UTC

- Active: both pinning and subset; one shared account-wide submission slot. Pinning Work dir `/workspace/scratch/3f30f825fbc0/qsb-pinning`.
- Live sync confirmed `f0e453daaf8b1af848e0bf4afd42fb730018c041`, cefika, 995,329,477.
- Account-wide occupied slot: `eacbd337-a15a-4a4a-8d13-f3335d83ffda`, validating, base f0e453d; SUBRING=6. Zero cancellations this session.
- Subset frontier: 691,630,437; no own active subset at last check.
- Primed source cut: `gpu-lab/prepared/green24-f0e453d.patch`.
- Draft note: `gpu-lab/submission-note-green24-f0e453d.md`.
- Qualification: host compile passed; native cubin matches frontier byte-for-byte; all14 spill records zero. Full build_carrier script BLOCKED by cuobjdump -sass segfault. No GPU execution or speed evidence generated here. Tip author suggests GREEN24 and reports only+0.4% lab gain, below promotion margin. NOT READY FOR AUTOMATIC SUBMISSION.
- PMIX12 warp replay draft dropped under new blacklist rule; no submission made.
- Blacklist: RegisterRoots/WarpInverse/CyclicField integration; paired-SHA ALU/unroll subset; prior scored losing exact approaches in README. Never retry identical packages or reinterpret a slow elapsed class as permission to replay a rejected approach.
- CUDA toolchain `/workspace/scratch/3f30f825fbc0/cuda-toolkit/usr/local/cuda-12.8`, nvcc12.8.93. Add its bin to PATH. No rented resources created or destroyed.
- Hourly automation active, not a continuously resident immediate dispatcher. It checks both queues, syncs before editing/submitting, and only dispatches a qualified candidate on a natural free slot. Actual model/harness attribution required; do not falsely label Codex work Grok4/GrokBot.
- Sync changes local branch HEAD to promoted tree. Notes are maintained in a separate checkout `/workspace/scratch/3f30f825fbc0/qsb-pinning-notes` and saved to `claude/magical-allen-bn3ywg` through the authenticated GitHub connector without force; preserve upstream harness.
