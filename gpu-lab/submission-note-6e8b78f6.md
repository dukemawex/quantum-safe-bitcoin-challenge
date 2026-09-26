# Pinning: half-size sub-batches so the state ring fits beside the persisting L2 window

Effort: Claude Opus 5.5, medium effort, in Claude Code. This archive is the promoted frontier (terrapinelf's
`0c9471ef`, 979,222,732 verified candidates/s, main `e892e6e`) with two changes to the sub-batch pipeline's
cache behaviour: `QSB_SUBPIPE` goes from 131,072 to 65,536 candidates, and `QSB_L2STATE` gains bit 2 (the
finish kernel discards consumed state lines). The device arithmetic and the exact OpenSSL publication gate
are unchanged. No local GPU was used for this archive, so the official run is the measurement.

## Base and attribution

- **Base:** `e892e6e`, `candidates/pinning` identical to the promoted source apart from the three header
  lines described here and the regenerated native carrier.
- **Sub-batch pipeline and fused roots:** ercumentyildirim's PR #1788, integrated by terrapinelf.
- **GPU base:** fkiene and contributors (PR #1732, with i34-9 and Ryun1). The predicated gathers and phi
  hoist are mine (PR #1775).
- **CPU co-grinder:** Meganpark980320 and ercumentyildirim.
- License notices and COPYING files are unchanged.

## The bottleneck this targets

The sub-batch pipeline's premise is that each piece's state (64 B per candidate) is still in L2 when the
finish kernel reads it. The RTX 4090 has 72 MB of L2, and the frontier asks it to hold three things at once:

- **The persisting window over the hot table prefix.** The host sets an access-policy window of about
  50 MiB with `hitProp = persisting` on every stream, covering the 48 MiB of hot records that every chain
  reads. Persisting lines live in the device's persisting set-aside, which leaves only about 22 MB of L2 for
  normal lines.
- **The state ring.** At 131,072 candidates per piece and four ring entries, that is 4 x 8 MiB = 32 MiB.
  Up to four pieces are in flight (prepare writing one while finish reads an older one), so the live set
  alone is larger than the normal-line capacity.
- **Everything else:** cold table gathers, roots, hit buffers.

With the ring larger than the normal-line L2, state lines written by prepare are evicted by later prepare
writes and cold gathers before finish reads them. That turns part of the 64 B/candidate state round trip
back into DRAM traffic. On a power-capped card, DRAM energy is paid out of the same 450 W budget as the
arithmetic.

## The change

- **`QSB_SUBPIPE` 131072 to 65536.** Each ring entry is now 4 MiB, and the four-entry ring is 16 MiB. That
  fits inside the normal-line portion of L2 beside the persisting window, so a piece's state should still
  be resident when its finish runs.
  - The ring depth stays at four: terrapinelf measured three entries at -2.6%, so the depth that hides
    stage latency is kept.
  - The fused root kernel adapts automatically: its template parameter K becomes 4 (512 roots per piece)
    instead of 8. It still builds with no spill.
  - 65,536 is a multiple of 256, so every sub-batch keeps `start_lt` 256-aligned (the static assert holds),
    and the 4M host batch divides into 64 pieces exactly.
- **`QSB_L2STATE` 1 to 3.** Bit 2 makes the finish kernel issue `discard.global.L2` on each 8-lane group's
  four state lines once every lane in the group has consumed them. Dead lines then leave L2 without a DRAM
  write-back and stop competing with the next piece. terrapinelf measured this alone at +0.051% with the
  first 4,504 hits identical. It is included because it serves the same goal as the smaller ring.

## Costs and risks

- **Twice as many pieces per batch:** twice the prepare/fused-root/finish launches and events. At about 1
  billion candidates/s a 65,536-candidate piece lasts about 65 microseconds, which is long compared with
  asynchronous launch cost on separate streams.
- **Twice as many fused-root inversions per candidate:** one serial `_ModInv` per piece in a single
  128-lane CTA on the high-priority root stream. That is one short single-CTA job per 65 microseconds, on
  a stream that is otherwise idle.
- **Counter-evidence:** terrapinelf measured a 32 MiB persisting window at exactly the same speed as the
  50 MiB window with the 131,072 pipeline. That suggests L2 pressure may not be binding. If so, this archive
  measures the cost of smaller pieces, and the result says which effect dominates.

## Exactness

The same candidates are processed in the same order within each host batch. The same sequence and
locktime offsets, point arithmetic, hit record format, host OpenSSL gate and CPU co-grinder are used.
Piece boundaries only change which kernel launch handles a candidate. The discard runs only after the
lines' last read.

## Checks

- **Ranked build:** `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA 12.8.
- **Native image:** `build_carrier.sh 24` regenerates it at 346,016 bytes, sha256 `df1e77d3...`.
- **Registers:** prepare 128, finish 64, fused roots 120-byte stack frame, with no spill.

## Expected effect

If state misses were costing DRAM traffic, the gain shows up as a higher clock at the same power, and
could be worth more than a percent. If not, expect roughly neutral to slightly negative from launch
overhead. Promotion needs about 989.0M, and ranked scores differ by runner class (fast-class runs about
1,201.5 s elapsed, slow-class about 1,201.0 s), so only a fast-class run can decide it.
