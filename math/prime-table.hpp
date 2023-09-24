#pragma once

#include <vector>

std::vector<bool> prime_table(int n) {
    std::vector<bool> prime(n + 1, true);
    if (0 <= n) prime[0] = false;
    if (1 <= n) prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (!prime[i]) continue;
        for (int j = i * i; j <= n; j += i) {
            prime[j] = false;
        }
    }
    return prime;
}