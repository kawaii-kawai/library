#pragma once

#include "graph-template.hpp"
#include <queue>

template <class T> std::vector<int> topological_sort(const Graph<T>& g) {
    const int n = g.size();
    std::vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        for (const auto& e : g[i]) deg[e.to]++;
    }
    std::queue<int> que;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) que.push(i);
    }
    std::vector<int> res;
    while (!que.empty()) {
        int idx = que.front();
        que.pop();
        res.emplace_back(idx);
        for (const auto& e : g[idx]) {
            deg[e.to]--;
            if (deg[e.to] == 0) que.push(e.to);
        }
    }
    if ((int)res.size() != n) return {};
    return res;
}