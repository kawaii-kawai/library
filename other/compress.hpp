#pragma once

#include <algorithm>
#include <vector>

template <class T> std::vector<T> compress(std::vector<T>& vec) {
    std::vector<T> vals = vec;
    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    for (auto& e : vec) {
        e = std::lower_bound(vals.begin(), vals.end(), e) - vals.begin();
    }
    return vals;
}

template <class T>
std::vector<T> compress2d(std::vector<T>& c1, std::vector<T>& c2, int D = 1) {
    std::vector<T> vals;
    const int n = (int)(c1.size());
    for (int i = 0; i < n; i++) {
        for (int d = 0; d <= D; d++) {
            T tc1 = c1[i] + d;
            T tc2 = c2[i] + d;
            vals.emplace_back(tc1);
            vals.emplace_back(tc2);
        }
    }
    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < n; i++) {
        c1[i] =
            std::lower_bound(vals.begin(), vals.end(), c1[i]) - vals.begin();
        c2[i] =
            std::lower_bound(vals.begin(), vals.end(), c2[i]) - vals.begin();
    }
    return vals;
}