#include "/workspace/scratch/3f30f825fbc0/qsb-pinning/candidates/pinning/cg_sha.h"
#define QSB_ZEROS_N 24
#define QI_INL __attribute__((target("avx2,avx512f,avx512vl,avx512ifma"),always_inline)) inline
typedef uint64_t V __attribute__((vector_size(32)));
struct vfe {V n[5];};
__attribute__((target("sha,sse4.1"), noinline)) static void pub_hash8_shani_wm(const uint32_t Wt[9][8], uint32_t h0[8]) {
    using namespace qcg_sha;
    for (int k = 0; k < 8; k += 2) {
        uint32_t wa[16], wb[16], sa[8], sb[8];
        for (int j = 0; j < 9; j++) { wa[j] = Wt[j][k]; wb[j] = Wt[j][k + 1]; }
        for (int j = 9; j < 15; j++) { wa[j] = 0; wb[j] = 0; }
        wa[15] = 264; wb[15] = 264;
        memcpy(sa, IV256, 32); memcpy(sb, IV256, 32);
        shani_compress2(sa, wa, sb, wb);
        h0[k] = sa[0]; h0[k + 1] = sb[0];
    }
}
static QI_INL void to_w(V w[4], const vfe *a) {
    const V *n = a->n;
    w[0] = n[0] | (n[1] << 52);
    w[1] = (n[1] >> 12) | (n[2] << 40);
    w[2] = (n[2] >> 24) | (n[3] << 28);
    w[3] = (n[3] >> 36) | (n[4] << 16);
}
static QI_INL unsigned hash_block(const vfe *xp, const vfe *yp, const vfe *xm, const vfe *ym, int use_ni) {
    using namespace qcg_sha;
    V wp[4], wm[4];
    to_w(wp, xp); to_w(wm, xm);
    const __m256i idx_lo = _mm256_setr_epi32(0, 2, 4, 6, 0, 2, 4, 6), idx_hi = _mm256_setr_epi32(1, 3, 5, 7, 1, 3, 5, 7);
    v8u X[8];
    for (int k = 0; k < 4; k++) {
        __m256i pl = _mm256_permutevar8x32_epi32((__m256i)wp[k], idx_lo), ml = _mm256_permutevar8x32_epi32((__m256i)wm[k], idx_lo);
        __m256i ph = _mm256_permutevar8x32_epi32((__m256i)wp[k], idx_hi), mh = _mm256_permutevar8x32_epi32((__m256i)wm[k], idx_hi);
        X[2 * k] = _mm256_blend_epi32(pl, ml, 0xF0);
        X[2 * k + 1] = _mm256_blend_epi32(ph, mh, 0xF0);
    }
    __m256i par = _mm256_blend_epi32(_mm256_permutevar8x32_epi32((__m256i)yp->n[0], idx_lo),
                                     _mm256_permutevar8x32_epi32((__m256i)ym->n[0], idx_lo), 0xF0);
    par = _mm256_and_si256(par, _mm256_set1_epi32(1));
    v8u W[16];
    W[0] = _mm256_or_si256(_mm256_slli_epi32(_mm256_or_si256(par, _mm256_set1_epi32(2)), 24), _mm256_srli_epi32(X[7], 8));
    for (int j = 1; j < 8; j++) W[j] = _mm256_or_si256(_mm256_slli_epi32(X[8 - j], 24), _mm256_srli_epi32(X[7 - j], 8));
    W[8] = _mm256_or_si256(_mm256_slli_epi32(X[0], 24), _mm256_set1_epi32(0x00800000));
    for (int j = 9; j < 15; j++) W[j] = _mm256_setzero_si256();
    W[15] = _mm256_set1_epi32(264);
    __m256i h0;
    if (use_ni) {
        alignas(32) uint32_t Wt[9][8], hh[8];
        for (int j = 0; j < 9; j++) _mm256_store_si256((__m256i *)Wt[j], W[j]);
        pub_hash8_shani_wm(Wt, hh);
        h0 = _mm256_load_si256((const __m256i *)hh);
    } else {
        v8u st[8];
        for (int j = 0; j < 8; j++) st[j] = _mm256_set1_epi32((int)IV256[j]);
        s8_compress_full(st, W);
        h0 = st[0];
    }
#if QSB_CG_H0BOUND
    const uint32_t max_h0 = QSB_ZEROS_N >= 32 ? 0u : (0xffffffffu >> QSB_ZEROS_N);
    return (unsigned)_mm256_cmple_epu32_mask(h0, _mm256_set1_epi32((int)max_h0));
#else
#if QSB_ZEROS_N >= 32
    __m256i ok = _mm256_cmpeq_epi32(h0, _mm256_setzero_si256());
#else
    __m256i ok = _mm256_cmpeq_epi32(_mm256_srli_epi32(h0, 32 - QSB_ZEROS_N), _mm256_setzero_si256());
#endif
    return (unsigned)_mm256_movemask_ps(_mm256_castsi256_ps(ok));
#endif
}
extern "C" __attribute__((target("avx2,avx512f,avx512vl,avx512ifma"))) unsigned probe(const vfe*a,const vfe*b,const vfe*c,const vfe*d,int ni){return hash_block(a,b,c,d,ni);}
