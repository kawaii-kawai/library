#pragma once

#include "graph-template.hpp"
#include <limits>
#include <queue>

template <class T> std::vector<T> bfs(const Graph<T>& g, int s) {
    const auto inf = std::numeric_limits<T>::max();
    std::vector<T> dist(g.size(), inf);
    std::queue<int> que;
    dist[s] = 0;
    que.emplace(s);
    while (!que.empty()) {
        int idx = que.front();
        que.pop();
        for (const auto& e : g[idx]) {
            if (dist[e.to] != inf) continue;
            dist[e.to] = dist[idx] + 1;
            que.emplace(e.to);
        }
    }
    return dist;
}