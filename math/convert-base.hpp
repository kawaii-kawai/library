#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

template <class T>
std::vector<T> convert_base(T x, T b) {
    std::vector<T> res;
    T t = 1, k = std::abs(b);
    while (x) {
        res.emplace_back((x * t) % k);
        if (res.back() < 0) res.back() += k;
        x -= res.back() * t;
        x /= k;
        t *= b / k;
    }
    std::reverse(res.begin(), res.end());
    return res;
}