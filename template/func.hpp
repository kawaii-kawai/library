#pragma once

#include "template.hpp"

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