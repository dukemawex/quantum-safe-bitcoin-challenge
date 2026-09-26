Prepared Yukon subset submissions (outside the editable path; never archived).
- n2-on-b159670.patch: apply with `git am` on b159670 (unrolled const SHA + QSB_PAIR_SHA_ALU_ADD). Use if 600e95a7 is promoted.
- n1-vs-b159670.diff: `git apply` on b159670 gives the promoted frontier's rolled SHA + QSB_PAIR_SHA_ALU_ADD. Use if 600e95a7 is rejected.
Both include the regenerated qsb_carrier_sm89.h and the submission note.
- n3-pair_shared-outer-alu.diff: on top of n1 or n2, extends QSB_PAIR_SHA_ALU_ADD to the outer SHA-256d block (+124 FMA->ALU adds/pair); regenerate the carrier after applying.
- n1b-vs-a137e28.diff: QSB_PAIR_SHA_ALU_ADD on frontier 9f8a33d8/a137e28 (675.5M); git apply on upstream a137e28 (carrier + note included).
- n3b-vs-a137e28.diff: N1b + outer SHA-256d ALU adds on a137e28 (second candidate).
- n5-vs-a137e28.diff: waiting candidate after 1abaec4a: N3b + full const SHA unroll (~1,780 fewer FMA-pipe instrs/pair).
- n6-vs-a137e28.diff: NEXT SUBMISSION. Meganpark980320 296e5e53 co-grinder tree (681.9M) + QSB_PAIR_SHA_ALU_ADD GPU change; --coauthors Meganpark980320.
- n7-vs-a137e28.diff: waiting after 6975ad8c: Meganpark co-grinder tree + const SHA unroll + ALU adds (--coauthors Meganpark980320).

## N8 (waiting, 2026-09-26 19:1x UTC) — branch `prep-n8` (3c37f01)
New record kshitij-hash `d052bc3d` (61cb94f, 691,630,437). N7's GPU change (paired SHA
`QSB_PAIR_SHA_ALU_ADD` + const-suffix unroll) ported onto it; record CPU side kept. Carrier
`df82b24f…` (574,368 B), 0 spills; record image reproduces byte for byte locally; setup.sh smoke
test passed. Patch (excluding carrier): `n8-vs-61cb94f.diff`. Submit with
`--coauthors kshitij-hash,Meganpark980320`.
