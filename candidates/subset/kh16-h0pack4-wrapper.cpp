#include <immintrin.h>
#include <cstdint>
#include <cstring>
#define QSB_ZEROS_N 24
#define QSHA16 __attribute__((target("sha,sse4.1,ssse3,avx,avx2,avx512f,avx512vl")))
alignas(16) static const uint32_t qsha_k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
QSHA16 static unsigned kh16_pass(const uint32_t *m, uint32_t *wk
#ifdef QSB_CPU_DEVBENCH
                                 , uint32_t *h0_out = nullptr
#endif
                                 ) {
#define R16(x, n) _mm512_ror_epi32((x), (n))
#define S0_16(x) _mm512_ternarylogic_epi32(R16(x, 7), R16(x, 18), _mm512_srli_epi32(x, 3), 0x96)
#define S1_16(x) _mm512_ternarylogic_epi32(R16(x, 17), R16(x, 19), _mm512_srli_epi32(x, 10), 0x96)
    __m512i W[16];
#pragma GCC unroll 9
    for (int i = 0; i < 9; i++) W[i] = _mm512_load_si512((const void *)(m + 16 * i));
    for (int i = 9; i < 15; i++) W[i] = _mm512_setzero_si512();
    W[15] = _mm512_set1_epi32(264);
    __m512i prev = _mm512_setzero_si512();
#pragma GCC unroll 64
    for (int t = 0; t < 64; t++) {
        __m512i wt;
        if (t < 16) wt = W[t];
        else {
            /* W[t] = s1(W[t-2]) + W[t-7] + s0(W[t-15]) + W[t-16]; the zero words W9..W14 drop out at compile time */
            const int a2 = (t - 2) & 15, a7 = (t - 7) & 15, a15 = (t - 15) & 15, a16 = t & 15;
            const bool z2 = (t - 2) >= 9 && (t - 2) <= 14, z7 = (t - 7) >= 9 && (t - 7) <= 14, z15 = (t - 15) >= 9 && (t - 15) <= 14,
                       z16 = (t - 16) >= 9 && (t - 16) <= 14;
            wt = z16 ? _mm512_setzero_si512() : W[a16];
            if (!z15) wt = _mm512_add_epi32(wt, S0_16(W[a15]));
            if (!z7) wt = _mm512_add_epi32(wt, W[a7]);
            if (!z2) wt = _mm512_add_epi32(wt, S1_16(W[a2]));
            W[a16] = wt;
        }
        const __m512i wkt = _mm512_add_epi32(wt, _mm512_set1_epi32((int)qsha_k[t]));
        if (t & 1) {                                     /* rounds t - 1, t as dword pairs, key-major within 128-bit lanes */
            _mm512_store_si512((void *)(wk + 32 * (t >> 1)), _mm512_unpacklo_epi32(prev, wkt));
            _mm512_store_si512((void *)(wk + 32 * (t >> 1) + 16), _mm512_unpackhi_epi32(prev, wkt));
        } else prev = wkt;
    }
#undef S0_16
#undef S1_16
#undef R16
    /* key 4L + e: pair p at wk + 32 p + (e >= 2 ? 16 : 0) + 4 L + 2 (e & 1) */
    const __m128i IV0 = _mm_set_epi32((int)0x6a09e667, (int)0xbb67ae85, (int)0x510e527f, (int)0x9b05688c);
    const __m128i IV1 = _mm_set_epi32((int)0x3c6ef372, (int)0xa54ff53a, (int)0x1f83d9ab, (int)0x5be0cd19);
    alignas(64) uint32_t h0[16];
#pragma GCC unroll 1
    for (int L = 0; L < 4; L++) {
        __m128i S0[4], S1[4];
        const uint32_t *base[4] = {wk + 4 * L, wk + 4 * L + 2, wk + 16 + 4 * L, wk + 16 + 4 * L + 2};
#pragma GCC unroll 4
        for (int e = 0; e < 4; e++) { S0[e] = IV0; S1[e] = IV1; }
#pragma GCC unroll 16
        for (int r = 0; r < 16; r++) {
#pragma GCC unroll 4
            for (int e = 0; e < 4; e++) S1[e] = _mm_sha256rnds2_epu32(S1[e], S0[e], _mm_loadl_epi64((const __m128i *)(base[e] + 64 * r)));
#pragma GCC unroll 4
            for (int e = 0; e < 4; e++) S0[e] = _mm_sha256rnds2_epu32(S0[e], S1[e], _mm_loadl_epi64((const __m128i *)(base[e] + 64 * r + 32)));
        }
#if QSB_CPU_KH16_H0PACK4
        const __m128i a0 = _mm_add_epi32(S0[0], IV0), a1 = _mm_add_epi32(S0[1], IV0);
        const __m128i a2 = _mm_add_epi32(S0[2], IV0), a3 = _mm_add_epi32(S0[3], IV0);
        const __m128i h01 = _mm_unpackhi_epi32(a0, a1), h23 = _mm_unpackhi_epi32(a2, a3);
        _mm_store_si128((__m128i *)(h0 + 4 * L), _mm_unpackhi_epi64(h01, h23));
#else
#pragma GCC unroll 4
        for (int e = 0; e < 4; e++) h0[4 * L + e] = (uint32_t)_mm_extract_epi32(_mm_add_epi32(S0[e], IV0), 3);
#endif
    }
#ifdef QSB_CPU_DEVBENCH
    if (h0_out) memcpy(h0_out, h0, sizeof h0);
#endif
    const __m512i hv = _mm512_load_si512((const void *)h0);   /* pk_prefilter of the 16 keys: bit k = key k passes */
    return (unsigned)_mm512_cmpeq_epi32_mask(_mm512_srli_epi32(hv, 32 - (QSB_ZEROS_N < 32 ? QSB_ZEROS_N : 32)), _mm512_setzero_si512());
}
extern "C" QSHA16 unsigned probe(const uint32_t*m,uint32_t*w){return kh16_pass(m,w);}
