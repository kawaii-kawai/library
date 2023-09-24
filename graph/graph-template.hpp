#pragma once

#include <vector>

template <class T = int> struct Edge {
    int from, to;
    T cost;
    int idx;
    Edge(int from, int to, T cost = 1, int idx = -1)
        : from(from), to(to), cost(cost), idx(idx) {}
};
template <class T = int> using Edges = std::vector<Edge<T>>;

template <class T = int> struct Graph {
    std::vector<std::vector<Edge<T>>> g;
    int es;

    Graph(int sz) : g(sz), es(0) {}

    int size() const { return (int)(g.size()); }

    void add_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es);
        es++;
    }

    inline std::vector<Edge<T>>& operator[](const int& k) { return g[k]; }
    inline const std::vector<Edge<T>>& operator[](const int& k) const {
        return g[k];
    }
};