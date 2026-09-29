#include <cstdint>
#include <immintrin.h>
namespace v4i {
#define QI_TGT "avx2,avx512f,avx512vl,avx512ifma"
#define QI_INL __attribute__((target(QI_TGT), always_inline)) inline
#define QI_FN  __attribute__((target(QI_TGT), noinline))
typedef uint64_t V __attribute__((vector_size(32)));
struct vfe { V n[5]; };

static QI_INL V vs1(uint64_t x) { return (V){x, x, x, x}; }
#define QI_LO(acc, a, b) ((V)_mm256_madd52lo_epu64((__m256i)(acc), (__m256i)(a), (__m256i)(b)))
#define QI_HI(acc, a, b) ((V)_mm256_madd52hi_epu64((__m256i)(acc), (__m256i)(a), (__m256i)(b)))
#define QI_M52 0xFFFFFFFFFFFFFULL
#define QI_M48 0xFFFFFFFFFFFFULL
#define QI_C   0x1000003D1ULL                 /* 2^256 mod p */
#define QI_R   0x1000003D10ULL                /* 2^260 mod p */
/* 2p in radix 2^52 */
#define QI_2P0 (2 * 0xFFFFEFFFFFC2FULL)
#define QI_2P1 (2 * 0xFFFFFFFFFFFFFULL)
#define QI_2P4 (2 * 0x0FFFFFFFFFFFFULL)

/* r = a b mod p (W form in, W form out, n4 <= 2^48); r may alias a or b */
static QI_INL void fmul(vfe *r, const vfe *A, const vfe *B) {
    const V a0 = A->n[0], a1 = A->n[1], a2 = A->n[2], a3 = A->n[3], a4 = A->n[4];
    const V b0 = B->n[0], b1 = B->n[1], b2 = B->n[2], b3 = B->n[3], b4 = B->n[4];
    const V z = vs1(0), M = vs1(QI_M52), R = vs1(QI_R), C = vs1(QI_C);
    /* columns: c_k = sum lo(a_i b_j) over i+j = k, plus sum hi(a_i b_j) over i+j = k-1; each < 10 * 2^52 */
    V c0 = QI_LO(z, a0, b0);
    V c1 = QI_LO(QI_LO(QI_HI(z, a0, b0), a0, b1), a1, b0);
    V c2 = QI_LO(QI_LO(QI_LO(QI_HI(QI_HI(z, a0, b1), a1, b0), a0, b2), a1, b1), a2, b0);
    V c3 = QI_LO(QI_LO(QI_LO(QI_LO(QI_HI(QI_HI(QI_HI(z, a0, b2), a1, b1), a2, b0), a0, b3), a1, b2), a2, b1), a3, b0);
    V c4 = QI_HI(QI_HI(QI_HI(QI_HI(z, a0, b3), a1, b2), a2, b1), a3, b0);
    c4 = QI_LO(QI_LO(QI_LO(QI_LO(QI_LO(c4, a0, b4), a1, b3), a2, b2), a3, b1), a4, b0);
    V c5 = QI_HI(QI_HI(QI_HI(QI_HI(QI_HI(z, a0, b4), a1, b3), a2, b2), a3, b1), a4, b0);
    c5 = QI_LO(QI_LO(QI_LO(QI_LO(c5, a1, b4), a2, b3), a3, b2), a4, b1);
    V c6 = QI_HI(QI_HI(QI_HI(QI_HI(z, a1, b4), a2, b3), a3, b2), a4, b1);
    c6 = QI_LO(QI_LO(QI_LO(c6, a2, b4), a3, b3), a4, b2);
    V c7 = QI_HI(QI_HI(QI_HI(z, a2, b4), a3, b3), a4, b2);
    c7 = QI_LO(QI_LO(c7, a3, b4), a4, b3);
    V c8 = QI_LO(QI_HI(QI_HI(z, a3, b4), a4, b3), a4, b4);
    V c9 = QI_HI(z, a4, b4);                                   /* < 2^46 (a4, b4 < 2^49) */
    /* high columns to 52-bit limbs (c9 stays < 2^52) */
    c6 += c5 >> 52; c5 &= M;
    c7 += c6 >> 52; c6 &= M;
    c8 += c7 >> 52; c7 &= M;
    c9 += c8 >> 52; c8 &= M;
    /* fold 2^(52k) = 2^(52(k-5)) 2^260, 2^260 = R mod p: lo(c_k R) -> column k-5, hi -> k-4 */
    V d0 = QI_LO(c0, c5, R);
    V d1 = QI_LO(QI_HI(c1, c5, R), c6, R);
    V d2 = QI_LO(QI_HI(c2, c6, R), c7, R);
    V d3 = QI_LO(QI_HI(c3, c7, R), c8, R);
    V d4 = QI_LO(QI_HI(c4, c8, R), c9, R);
    const V e5 = QI_HI(z, c9, R);                              /* weight 2^260, < 2^32 */
    d4 += d3 >> 52; d3 &= M;
    const V top = (d4 >> 48) + (e5 << 4);                      /* weight 2^256, < 2^37 */
    d4 &= vs1(QI_M48);
    d0 = QI_LO(d0, top, C);
    d1 = QI_HI(d1, top, C);
    d1 += d0 >> 52; d0 &= M;
    d2 += d1 >> 52; d1 &= M;
    d3 += d2 >> 52; d2 &= M;
    d4 += d3 >> 52; d3 &= M;
    r->n[0] = d0; r->n[1] = d1; r->n[2] = d2; r->n[3] = d3; r->n[4] = d4;
}
static QI_INL void fsqr(vfe *r, const vfe *a) { fmul(r, a, a); }

/* any limbs < 2^62 -> W form (libsecp256k1 fe_normalize_weak, radix 2^52) */
static QI_INL void fwk(vfe *r) {
    const V M = vs1(QI_M52);
    V t0 = r->n[0], t1 = r->n[1], t2 = r->n[2], t3 = r->n[3], t4 = r->n[4];
    const V x = t4 >> 48; t4 &= vs1(QI_M48);
    t0 = QI_LO(t0, x, vs1(QI_C));                               /* x < 2^14: x C < 2^47 */
    t1 += t0 >> 52; t0 &= M;
    t2 += t1 >> 52; t1 &= M;
    t3 += t2 >> 52; t2 &= M;
    t4 += t3 >> 52; t3 &= M;
    r->n[0] = t0; r->n[1] = t1; r->n[2] = t2; r->n[3] = t3; r->n[4] = t4;
}
/* canonical value in [0, p) from limbs < 2^62 (libsecp256k1 fe_normalize, radix 2^52) */
#ifndef QSB_CG_NORM_MASK
#define QSB_CG_NORM_MASK 1 /* predicate construction in mask registers only */
#endif
static QI_INL void fnorm(vfe *r) {
    const V M = vs1(QI_M52);
    V t0 = r->n[0], t1 = r->n[1], t2 = r->n[2], t3 = r->n[3], t4 = r->n[4], m;
    V x = t4 >> 48; t4 &= vs1(QI_M48);
    t0 = QI_LO(t0, x, vs1(QI_C));
    t1 += t0 >> 52; t0 &= M;
    t2 += t1 >> 52; t1 &= M; m = t1;
    t3 += t2 >> 52; t2 &= M; m &= t2;
    t4 += t3 >> 52; t3 &= M; m &= t3;
    /* value < 2p here; subtract p once if value >= p (limbs < 2^53: signed compares are exact) */
#if QSB_CG_NORM_MASK
    const __mmask8 correction = _mm256_cmpge_epu64_mask((__m256i)t0, (__m256i)vs1(0xFFFFEFFFFFC2FULL))
        & _mm256_cmpeq_epi64_mask((__m256i)t4, (__m256i)vs1(QI_M48))
        & _mm256_cmpeq_epi64_mask((__m256i)m, (__m256i)M);
    x = (t4 >> 48) | (V)_mm256_maskz_set1_epi64(correction, 1);
#else
    const V ge = (V)_mm256_cmpgt_epi64((__m256i)t0, (__m256i)vs1(0xFFFFEFFFFFC2FULL - 1));
    x = (t4 >> 48) | ((V)_mm256_cmpeq_epi64((__m256i)t4, (__m256i)vs1(QI_M48)) & (V)_mm256_cmpeq_epi64((__m256i)m, (__m256i)M) & ge & vs1(1));
#endif
    t0 += (vs1(0) - x) & vs1(QI_C);                             /* x in {0, 1} */
    t1 += t0 >> 52; t0 &= M;
    t2 += t1 >> 52; t1 &= M;
    t3 += t2 >> 52; t2 &= M;
    t4 += t3 >> 52; t3 &= M;
    t4 &= vs1(QI_M48);
    r->n[0] = t0; r->n[1] = t1; r->n[2] = t2; r->n[3] = t3; r->n[4] = t4;
}

}
extern "C" __attribute__((target("avx2,avx512f,avx512vl,avx512ifma"))) void probe(v4i::vfe *out,const v4i::vfe *in){v4i::vfe v=*in;v4i::fnorm(&v);*out=v;}
