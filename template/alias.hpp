#pragma once

#include "template.hpp"

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

template <class T> using prique = std::priority_queue<T>;
template <class T>
using prique_rev = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <class T> struct Infinity {
    static constexpr T value = std::numeric_limits<T>::max() / 2;
    static constexpr T mvalue = std::numeric_limits<T>::min() / 2;
    static constexpr T max = std::numeric_limits<T>::max();
    static constexpr T min = std::numeric_limits<T>::min();
};
template <class T> constexpr T INF = Infinity<T>::value;

constexpr ld EPS = 1e-8;
constexpr ld PI = 3.1415926535897932384626;
constexpr std::array<int, 8> dx = {1, 0, -1, 0, 1, 1, -1, -1};
constexpr std::array<int, 8> dy = {0, 1, 0, -1, -1, 1, 1, -1};