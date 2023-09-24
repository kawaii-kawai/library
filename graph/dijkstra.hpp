#pragma once

#include "graph-template.hpp"
#include <limits>
#include <queue>

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