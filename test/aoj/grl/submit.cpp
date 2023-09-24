#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A"

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfenv>
#include <cfloat>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <streambuf>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// utility


namespace cp_library {

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

template <class T> using prique = std::priority_queue<T>;
template <class T>
using prique_rev = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <class T, class U> struct P : std::pair<T, U> {
    template <class... Args> P(Args... args) : std::pair<T, U>(args...) {}

    using std::pair<T, U>::first;
    using std::pair<T, U>::second;

    P& operator+=(const P& p) {
        first += p.first;
        second += p.second;
        return *this;
    }
    P& operator-=(const P& p) {
        first -= p.first;
        second -= p.second;
        return *this;
    }
    P& operator*=(const P& p) {
        first *= p.first;
        second *= p.second;
        return *this;
    }
    template <class S> P& operator*=(const S& s) {
        first *= s;
        second *= s;
        return *this;
    }

    P operator+(const P& p) const { return P(*this) += p; }
    P operator-(const P& r) const { return P(*this) -= r; }
    P operator*(const P& r) const { return P(*this) *= r; }
    template <class S> P operator*(const S& s) const { return P(*this) *= s; }

    P operator-() const { return P(-first, -second); }
};

using pl = P<ll, ll>;
using pi = P<int, int>;

template <class T> struct Infinity {
    static constexpr T value = std::numeric_limits<T>::max() / 2;
    static constexpr T mvalue = std::numeric_limits<T>::min() / 2;
    static constexpr T max = std::numeric_limits<T>::max();
    static constexpr T min = std::numeric_limits<T>::min();
};
template <class T> constexpr T INF = Infinity<T>::value;

constexpr ld EPS = 1e-8;
constexpr ld PI = 3.1415926535897932384626;
constexpr std::array<std::pair<int, int>, 4> dxy4 = {
    {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
constexpr std::array<std::pair<int, int>, 8> dxy8 = {
    {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}}};

}  // namespace cp_library

// bit operation


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

// inout


namespace cp_library {

template <class T, class U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    os << p.first << ' ' << p.second;
    return os;
}
template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p) {
    is >> p.first >> p.second;
    return is;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    int sz = (int)vec.size();
    for (int i = 0; i < sz; i++) os << (i ? " " : "") << vec[i];
    return os;
}
template <class T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
    for (auto& x : vec) is >> x;
    return is;
}

std::istream& operator>>(std::istream& is, __int128_t& x) {
    std::string s;
    std::cin >> s;
    x = 0;
    int flag = 0;
    for (auto& c : s) {
        if (c == '-') {
            flag = true;
            continue;
        }
        x *= 10;
        x += c - '0';
    }
    if (flag) x = -x;
    return is;
}
std::istream& operator>>(std::istream& is, __uint128_t& x) {
    std::string s;
    is >> s;
    x = 0;
    for (auto& c : s) {
        x *= 10;
        x += c - '0';
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, __int128_t x) {
    if (x == 0) return os << 0;
    if (x < 0) os << '-', x = -x;
    std::string s;
    while (x) s.push_back('0' + x % 10), x /= 10;
    std::reverse(s.begin(), s.end());
    return os << s;
}
std::ostream& operator<<(std::ostream& os, __uint128_t x) {
    if (x == 0) return os << 0;
    std::string s;
    while (x) s.push_back('0' + x % 10), x /= 10;
    std::reverse(s.begin(), s.end());
    return os << s;
}

void in() {}
template <class T, class... U> void in(T& t, U&... u) {
    std::cin >> t;
    in(u...);
}
void out() { std::cout << '\n'; }
template <class T, class... U> void out(const T& t, const U&... u) {
    std::cout << t;
    if (sizeof...(u)) std::cout << ' ';
    out(u...);
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

}  // namespace cp_library

// function


namespace cp_library {

template <class T, class U> inline constexpr bool chmin(T& x, U y) {
    return (y < x) ? (x = y, true) : (false);
}
template <class T, class U> inline constexpr bool chmax(T& x, U y) {
    return (x < y) ? (x = y, true) : (false);
}

template <class T> inline constexpr T Max(const std::vector<T>& vec) {
    return *std::max_element(vec.begin(), vec.end());
}
template <class T> inline constexpr T Min(const std::vector<T>& vec) {
    return *std::min_element(vec.begin(), vec.end());
}
template <class T> inline long long Sum(const std::vector<T>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 0LL);
}

}  // namespace cp_library

// macro


namespace cp_library {

#define OVERLOAD5(a, b, c, d, e, ...) e
#define REP1(b) for (ll _i = 0; _i < (ll)(b); _i++)
#define REP2(i, b) for (ll i = 0; i < (ll)(b); i++)
#define REP3(i, a, b) for (ll i = (ll)(a); i < (ll)(b); i++)
#define REP4(i, a, b, c) for (ll i = (ll)(a); i < (ll)(b); i += (ll)(c))
#define rep(...) OVERLOAD5(__VA_ARGS__, REP4, REP3, REP2, REP1)(__VA_ARGS__)

#define RREP1(b) for (ll _i = (ll)(b)-1; _i >= 0; _i--)
#define RREP2(i, b) for (ll i = (ll)(b)-1; i >= 0; i--)
#define RREP3(i, a, b) for (ll i = (ll)(b)-1; i >= (ll)(a); i--)
#define RREP4(i, a, b, c) for (ll i = (ll)(b)-1; i >= (ll)(a); i -= (ll)(c))
#define rrep(...) \
    OVERLOAD5(__VA_ARGS__, RREP4, RREP3, RREP2, RREP1)(__VA_ARGS__)

#define ALL(x) std::begin(x), std::end(x)
#define RALL(x) std::rbegin(x), std::rend(x)

}  // namespace cp_library

#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif



template <class T = int> struct Edge {
    int from, to;
    T cost;
    int idx;
    Edge(int from, int to, T cost = 1, int idx = -1)
        : from(from), to(to), cost(cost), idx(idx) {}
};
template <class T = int> using Edges = std::vector<Edge<T>>;

template <class T = int> struct Graph {
    std::vector<std::vector<Edge<T>>> g;
    int es;

    Graph(int sz) : g(sz), es(0) {}

    int size() const { return (int)(g.size()); }

    void add_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es);
        es++;
    }

    inline std::vector<Edge<T>>& operator[](const int& k) { return g[k]; }
    inline const std::vector<Edge<T>>& operator[](const int& k) const {
        return g[k];
    }
};

/*
dist : 始点からの最短距離(到達不可能ならINF)
from : 最短路木における頂点vの親(到達不可能または始点なら-1)
id   : 最短路木における頂点vの親辺のid(到達不可能または始点なら-1)
*/
template <class T> struct ShortestPath {
    std::vector<T> dist;
    std::vector<int> from, id;
};

template <class T> ShortestPath<T> dijkstra(const Graph<T>& g, int s) {
    const auto inf = std::numeric_limits<T>::max();
    std::vector<T> dist(g.size(), inf);
    std::vector<int> from(g.size(), -1), id(g.size(), -1);
    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>,
                        std::greater<std::pair<T, int>>>
        que;
    dist[s] = 0;
    que.emplace(dist[s], s);
    while (!que.empty()) {
        T cost;
        int idx;
        std::tie(cost, idx) = que.top();
        que.pop();
        if (dist[idx] < cost) continue;
        for (const auto& e : g[idx]) {
            if (dist[e.to] > dist[idx] + e.cost) {
                dist[e.to] = dist[idx] + e.cost;
                from[e.to] = idx;
                id[e.to] = e.idx;
                que.emplace(dist[e.to], e.to);
            }
        }
    }
    return {dist, from, id};
}
using namespace std;
using namespace cp_library;
int main() {
    int v, e, s;
    cin >> v >> e >> s;
    Graph<int> g(v);
    for (int i = 0; i < e; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        g.add_edge(from, to, cost);
    }
    auto res = dijkstra(g, s);
    for (int i = 0; i < v; i++) {
        if (res.dist[i] == numeric_limits<int>::max()) {
            cout << "INF" << endl;
        } else {
            cout << res.dist[i] << endl;
        }
    }
}
