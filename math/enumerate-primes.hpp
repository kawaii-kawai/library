#pragma once

#include "prime-table.hpp"
#include <algorithm>

std::vector<int> enumerate_primes(int n) {
    if (n <= 1) return {};
    auto d = prime_table(n);
    std::vector<int> primes;
    primes.reserve(std::count(d.begin(), d.end(), true));
    for (int i = 0; i <= n; i++) {
        if (d[i]) primes.push_back(i);
    }
    return primes;
}