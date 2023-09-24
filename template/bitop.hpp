#pragma once

#include "template.hpp"

namespace cp_library {

inline int lsb(const unsigned long long& a) {
    return a ? __builtin_ctzll(a) : 64;
}
inline int ctz(const unsigned long long& a) {
    return a ? __builtin_ctzll(a) : 64;
}
inline int msb(const unsigned long long& a) {
    return a ? 63 - __builtin_clzll(a) : -1;
}
inline int popcount(const unsigned long long& a) {
    return __builtin_popcountll(a);
}

template <class T> inline int gbit(const T& a, int i) { return (a >> i) & 1; }
template <class T> inline void sbit(T& a, int i, bool b) {
    if (gbit(a, i) != b) a ^= T(1) << i;
}
constexpr unsigned long long POW2(int n) { return (1ULL << n); }
constexpr unsigned long long MASK(int n) { return POW2(n) - 1; }

inline unsigned long long next_combination(int n, unsigned long long x) {
    if (n == 0) return 1;
    unsigned long long a = x & -x;
    unsigned long long b = x + a;
    return (x & ~b) / a >> 1 | b;
}
#define rep_comb(i, n, k)                                             \
    for (unsigned long long i = (1ULL << (k)) - 1; i < (1ULL << (n)); \
         i = next_combination((n), i))

inline constexpr int ceil_log2(unsigned long long x) {
    return x ? msb(x - 1) + 1 : 0;
}

}  // namespace cp_library