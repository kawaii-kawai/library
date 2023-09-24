#pragma once

#include "template.hpp"

inline ull next_combination(int n, ull x) {
    if (n == 0) return 1;
    ull a = x & -x;
    ull b = x + a;
    return (x & ~b) / a >> 1 | b;
}

#define rep_comb(i, n, k)                              \
    for (ull i = (1ULL << (k)) - 1; i < (1ULL << (n)); \
         i = next_combination((n), i))

inline constexpr int msb(ull x) {
    return x ? 63 - __builtin_clzll(x) : -1;
}

inline constexpr int ceil_log2(ull x) {
    return x ? msb(x - 1) + 1 : 0;
}

inline constexpr int popcount(ull x) {
    return __builtin_popcountll(x);
}