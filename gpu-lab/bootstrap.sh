#!/usr/bin/env bash
# Recreate the pinning-track work directory in a fresh session.
#
# `yukon clone eigenlabs/quantum-safe-bitcoin-challenge/pinning` currently fails
# with 404 (the API has no /api/challenges route), so clone the source repo with
# git and write the same repository-local link config `yukon clone` would.
#
#   YUKON_API_TOKEN must be set (environment secret), or run `yukon login` yourself.
#   ./bootstrap.sh [target-dir]      (default /home/user/qsb-pinning)
set -euo pipefail
LAB="$(cd "$(dirname "$0")" && pwd)"
T=${1:-/home/user/qsb-pinning}
SRC=https://github.com/Layr-Labs/quantum-safe-bitcoin-challenge

command -v yukon >/dev/null || { curl -fsSL https://api.yukon.org/yukon/install.sh | sh; }
export PATH="$HOME/.local/bin:$PATH"

[[ -d $T/.git ]] || git clone --branch main --single-branch "$SRC" "$T"
cd "$T"
git config yukon.benchmark-id b352879c-669f-44ef-98cd-ad3d34d0fefa
git config yukon.benchmark-name eigenlabs/quantum-safe-bitcoin-challenge/pinning
git config yukon.source-url "$SRC"
git config yukon.source-branch main
git config yukon.source-ref "$(git rev-parse HEAD)"
git config yukon.challenge '{"id":"f1a40cdb-2170-4f70-9ca2-ef7e2fe4bb20","name":"eigenlabs/quantum-safe-bitcoin-challenge","sourceUrl":"https://github.com/Layr-Labs/quantum-safe-bitcoin-challenge","tracks":[{"name":"subset","benchmarkId":"eafd2f3d-e64f-49c1-b98a-6b825b0cdc82","benchmarkName":"eigenlabs/quantum-safe-bitcoin-challenge/subset"},{"name":"pinning","benchmarkId":"b352879c-669f-44ef-98cd-ad3d34d0fefa","benchmarkName":"eigenlabs/quantum-safe-bitcoin-challenge/pinning"}]}'

# Lab tooling lives outside the editable path and is git-excluded, so it can never ride a submission.
mkdir -p .gpu-lab
[[ "$LAB" -ef .gpu-lab ]] || cp "$LAB"/{pod_agent.py,ab.sh,analyze.py,runpod.sh,bootstrap.sh,README.md} .gpu-lab/
grep -qx '.gpu-lab/' .git/info/exclude || echo '.gpu-lab/' >> .git/info/exclude
chmod +x .gpu-lab/*.sh

# CUDA 12.8 (same toolkit as the ranked runner) for compile and native-image checks.
if [[ ! -x /usr/local/cuda-12.8/bin/nvcc ]]; then
  curl -fsSLO https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2404/x86_64/cuda-keyring_1.1-1_all.deb
  dpkg -i cuda-keyring_1.1-1_all.deb >/dev/null && rm -f cuda-keyring_1.1-1_all.deb
  apt-get update -qq && DEBIAN_FRONTEND=noninteractive apt-get install -y -qq cuda-nvcc-12-8 cuda-cudart-dev-12-8 >/dev/null
fi
yukon tracks
echo "ready: cd $T ; export PATH=/usr/local/cuda-12.8/bin:\$PATH"
