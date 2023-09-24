#pragma once

#include <algorithm>
#include "../data-structure/unionfind.hpp"
#include "graph-template.hpp"

template <class T> struct MinimumSpanningTree {
    T cost;
    Edges<T> edges;
};

template <class T> MinimumSpanningTree<T> kruskal(Edges<T>& edgee, int v) {
    std::sort(
        edgee.begin(), edgee.end(),
        [](const Edge<T>& a, const Edge<T>& b) { return a.cost < b.cost; });
    UnionFind uf(v);
    T total = 0;
    Edges<T> es;
    for (auto& e : edgee) {
        if (uf.merge(e.from, e.to)) {
            total += e.cost;
            es.push_back(e);
        }
    }
    return {total, es};
}