#!/usr/bin/env python3
"""Summarize ab.sh runs: sustained throughput after warm-up, and hit-set equality.

Throughput comes from the grinder's cumulative progress lines
("[GPU 0] seq #N (...), <M>M total, <r>M/s, <t>s"), measured over the window
after WARMUP seconds, so it reflects sustained (thermally settled) speed rather
than the cold peak. Hits are compared on sequences every run fully completed.
"""
import glob, os, re, statistics, sys

WARMUP = float(os.environ.get("WARMUP", "60"))
PROG = re.compile(r"seq #(\d+) \(0x([0-9A-Fa-f]+)\), (\d+)M total, ([0-9.]+)M/s, (\d+)s")
HIT = re.compile(r"sequence=(\d+) locktime=(\d+) recid=(\d)")


def parse(run):
    prog, seqval = [], {}
    for m in PROG.finditer(open(f"{run}/out.log").read()):
        i, hx, tot, r, t = m.groups()
        prog.append((float(i), float(tot), float(r), float(t)))
        seqval[int(i)] = int(hx, 16)
    hits = set()
    for f in glob.glob(f"{run}/results/pinning_hit_*.txt"):
        hits |= {tuple(map(int, m.groups())) for m in HIT.finditer(open(f).read())}
    temps = []
    if os.path.exists(f"{run}/smi.csv"):
        for line in open(f"{run}/smi.csv"):
            p = [x.strip() for x in line.split(",")]
            if len(p) >= 5 and p[1].isdigit():
                temps.append((int(p[1]), p[2], p[4]))
    return prog, hits, temps, seqval


def sustained(prog):
    after = [p for p in prog if p[3] >= WARMUP]
    if len(after) < 2:
        return None
    (_, m0, _, t0), (_, m1, _, t1) = after[0], after[-1]
    return (m1 - m0) / (t1 - t0) if t1 > t0 else None


root, variants = sys.argv[1], sys.argv[2:]
rates, hitsets, lastseq, seqvals = {}, {}, {}, {}
for v in variants:
    for run in sorted(glob.glob(f"{root}/{v}-r*")):
        prog, hits, temps, seqval = parse(run)
        seqvals[run] = seqval
        s = sustained(prog)
        rates.setdefault(v, []).append(s)
        hitsets[run] = hits
        lastseq[run] = int(prog[-1][0]) if prog else 0
        peak = max((t[0] for t in temps), default=None)
        print(f"{os.path.basename(run):28s} sustained {s and round(s,1)} M/s  "
              f"cold-first {prog and prog[0][2]} M/s  seqs {len(prog)}  hits {len(hits)}  peakT {peak}")

print()
base = variants[0]
bmean = statistics.mean([r for r in rates[base] if r])
for v in variants:
    rr = [r for r in rates[v] if r]
    if not rr:
        print(f"{v}: no data"); continue
    m = statistics.mean(rr); sd = statistics.stdev(rr) if len(rr) > 1 else 0.0
    print(f"{v:20s} mean {m:8.1f} M/s  sd {sd:6.1f}  n={len(rr)}  vs {base}: {100*(m/bmean-1):+.2f}%")

# Hit equality on sequences every run finished: a progress line for seq #i is printed after
# seq #i completes, so indices < min(last index) are complete everywhere.
common = min(lastseq.values()) if lastseq else 0
ref = None
for run, hits in hitsets.items():
    # printed seq #i carries value SEQ_MIN + i - 1 (one GPU); lines appear every 10 sequences
    i0, v0 = next(iter(seqvals[run].items()))
    done = set(range(v0 - (i0 - 1), v0 - (i0 - 1) + common))
    h = {x for x in hits if x[0] in done}
    if ref is None:
        ref, refrun = h, run
    elif h != ref:
        print(f"HIT MISMATCH on seq<{common}: {os.path.basename(run)} vs {os.path.basename(refrun)}: "
              f"{len(h - ref)} extra, {len(ref - h)} missing")
if ref is not None:
    print(f"hit sets over seq<{common}: {len(ref)} hits, compared across {len(hitsets)} runs")
