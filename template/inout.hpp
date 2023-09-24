#pragma once

#include "template.hpp"

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