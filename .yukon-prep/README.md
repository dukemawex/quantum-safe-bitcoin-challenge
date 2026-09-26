Prepared Yukon subset submissions (outside the editable path; never archived).
- n2-on-b159670.patch: apply with `git am` on b159670 (unrolled const SHA + QSB_PAIR_SHA_ALU_ADD). Use if 600e95a7 is promoted.
- n1-vs-b159670.diff: `git apply` on b159670 gives the promoted frontier's rolled SHA + QSB_PAIR_SHA_ALU_ADD. Use if 600e95a7 is rejected.
Both include the regenerated qsb_carrier_sm89.h and the submission note.
