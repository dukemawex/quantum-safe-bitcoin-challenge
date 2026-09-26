# Pinning: predicated constant-policy table gathers in the hot chain loop

Effort: Claude Opus 5.5, medium effort, in Claude Code. This is one exact change to how the piped chain
gathers attach their L2 cache policy. Each 16-byte gather is issued as a complementary pair of predicated
loads: one carries the cold policy and one the hot policy, both compile-time constants. That replaces a
per-lane policy select copied into uniform registers for every load.

## Base and attribution

- **Base:** BASE_LINE
- **Prior work:** the L2 policy scheme itself (`QSB_TBL_L2POL=1`: cold-bank gathers `evict_first`, hot
  gathers `evict_normal`) and the pipelined gathers are fkiene's (`ff524fd9`). The chain, decoders and
  field code are fkiene's and earlier contributors'. License notices and COPYING files are unchanged.

## The bottleneck

The hot loop of the prepare kernel is the peeled one-add chain trip, run about ten times per candidate.
In the base SASS, every trip builds the cache-policy operand of its four `LDG` instructions like this:

```
ISETP.GT.U32.AND P1, PT, Rcode, 0xbffff, PT     ; record >= QSB_HOT_RECS
IMAD.MOV.U32 R69, RZ, RZ, 0x12f00000            ; evict_first descriptor (high word)
SEL R91, R69, 0x16f00000, P1                    ; per-lane select against evict_normal
IMAD.MOV.U32 R90, RZ, RZ, RZ                    ; descriptor low word
R2UR UR4..UR13  x8                              ; copy into a uniform pair per LDG
```

That is 12 instructions per trip. The loads need the descriptor in uniform registers, but `qsb_tbl_policy`
returns a per-lane select, so ptxas re-materializes and copies it for each of the four loads. Both
descriptor values are constants (ptxas folds `createpolicy` to `0x12f00000:0` and `0x16f00000:0`), so none
of that per-trip work is needed.

## Implementation

`QSB_TBL_POL_PRED` (default 1), in `qsb_load_glv_y_code` and `qsb_load_glv_x_code`:

- **The loads.** Each gather's two 16-byte loads become four predicated loads in one asm block:
  `setp.ge.u32 c, record, QSB_HOT_RECS`, then `@c ld... %cold` and `@!c ld... %hot`, for each half-record.
  The Y-half pair keeps `L2::64B` on its first load, as before.
- **The policies.** Both come from a new helper, `qsb_tbl_policies`, which uses the same `createpolicy`
  instructions as `qsb_tbl_policy`, and `QSB_TBL_L2POL=2` still selects `evict_last` for the hot policy.
- **The rest.** Same addresses, same destination buffers, same record index mask and same
  `QSB_HOT_RECS` threshold. `QSB_TBL_POL_PRED=0` restores the select form.

The resulting SASS in the loop:

```
ISETP.GE.U32.AND P6, PT, Rrec, 0xc0000, PT
@P6  LDG.E.LTC64B.128.CONSTANT R40, desc[UR6][R46.64+0x20]    ; UR6:7 = 0 : 0x12f00000, set once before the loop
@P6  LDG.E.128.CONSTANT ...
@!P6 LDG.E.LTC64B.128.CONSTANT R40, desc[UR8][R46.64+0x20]    ; UR8:9 = 0 : 0x16f00000, set once
@!P6 LDG.E.128.CONSTANT ...
```

The loop carries no `R2UR` and no policy select. The two constant descriptors are loaded by `UMOV`
outside the loop.

## Exactness and invariants

- **Loads and policies.** Each lane issues exactly one load of every complementary pair, with the policy
  that `qsb_tbl_policy` would have returned for it (record at or above `QSB_HOT_RECS` gets
  `evict_first`, otherwise `evict_normal`). A cache hint never changes the returned bytes. The same
  records land in the same buffers, so every point, every nomination and every published hit is the
  base's.
- **Untouched.** The host OpenSSL gate, CPU co-grind, slot pipeline and L2 persisting window.

## Checks

- **Ranked build.** `nvcc -O3 -DQSB_ZEROS_N=24 -o pinning pinning.cu -lcrypto -lm` builds with CUDA 12.8.
- **Native image.** `build_carrier.sh 24` regenerates it at 304,032 bytes, sha256 `9aafe9d7...`, with the
  prepare kernel at 128 registers and the finish kernel at 64, no spill and no stack frame.
- **Loop size.** The hot loop is 997 SASS instructions, against 1,007 without this change. That count
  already includes the four predicated-off load slots.
- **Load scheduling.** In the base, ptxas sank all four gathers to about 75% of the trip. With
  constant descriptors, the cold (DRAM) pair issues at about 48% of the trip and the hot pair at about
  59%, giving the long-latency cold gathers more of the addition to hide behind.
- **Tests.** `test_priority_pipeline.py` and `test_slot_readback.py` pass.

## Expected effect and limitations

- **Where the gain comes from.** Fewer instructions per trip, and earlier issue of the cold gathers.
  The issue slots of the four predicated-off loads are the cost.
- **Promotion.** The 1% floor over the base is FLOOR_LINE.
