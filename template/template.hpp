#pragma once

#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
template <class T> using prique = std::priority_queue<T>;
template <class T>
using prique_rev = std::priority_queue<T, std::vector<T>, std::greater<T>>;

#define rep(i, a) for (ll i = 0; i < (ll)(a); i++)
#define reps(i, a, b) for (ll i = (ll)(a); i < (ll)(b); i++)
#define rrep(i, a) for (ll i = (ll)(a)-1; i >= 0; i--)

#define ALL(x) std::begin(x), std::end(x)
#define RALL(x) std::rbegin(x), std::rend(x)

template <class T> constexpr T INF = std::numeric_limits<T>::max() / 2;
constexpr ld EPS = 1e-8;
constexpr std::array<int, 8> dx = {1, 0, -1, 0, 1, 1, -1, -1};
constexpr std::array<int, 8> dy = {0, 1, 0, -1, -1, 1, 1, -1};

template <class T, class U> inline constexpr bool chmin(T& x, U y) {
    return (y < x) ? (x = y, true) : (false);
}
template <class T, class U> inline constexpr bool chmax(T& x, U y) {
    return (x < y) ? (x = y, true) : (false);
}

class IoSetup {
  public:
    IoSetup() {
        std::cin.tie(nullptr);
        std::ios::sync_with_stdio(false);
        std::cout << std::fixed << std::setprecision(15);
        std::cerr << std::fixed << std::setprecision(15);
    }
} iosetup;