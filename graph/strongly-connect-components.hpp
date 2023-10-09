#pragma once

#include "graph-template.hpp"

#include <algorithm>

template <class T> class StronglyConnectedComponents {
  private:
    int scc_size_, v_size_;
    std::vector<bool> used;
    std::vector<int> order, component;
    std::vector<std::vector<int>> group;
    const Graph<T>& g_;
    Graph<T> rg_;

    void dfs(int v) {
        used[v] = true;
        for (auto& e : g_[v]) {
            if (!used[e.to]) dfs(e.to);
        }
        order.push_back(v);
    }

    void rdfs(int v) {
        component[v] = scc_size_;
        for (auto& e : rg_[v]) {
            if (component[e.to] == -1) rdfs(e.to);
        }
    }

    void init() {
        v_size_ = g_.size();
        rg_ = Graph<T>(v_size_);
        for (int i = 0; i < v_size_; i++) {
            for (auto& e : g_[i]) {
                rg_.add_edge(e.to, e.from, e.cost);
            }
        }
        used.assign(v_size_, false);
        for (int i = 0; i < v_size_; i++) {
            if (!used[i]) dfs(i);
        }
        std::reverse(order.begin(), order.end());
        scc_size_ = 0;
        component.assign(v_size_, -1);
        for (auto& v : order) {
            if (component[v] == -1) {
                rdfs(v);
                scc_size_++;
            }
        }
        group.resize(scc_size_);
        for (int i = 0; i < v_size_; i++) {
            group[component[i]].push_back(i);
        }
    }

  public:
    explicit StronglyConnectedComponents(const Graph<T>& g) : g_(g) { init(); }

    int size() const { return scc_size_; }

    int operator[](int k) const { return component[k]; }

    std::vector<std::vector<int>> groups() const { return group; }

    bool same(int u, int v) const { return (component[u] == component[v]); }

    Graph<T> dag() const {
        Graph<T> res(scc_size_);
        for (int i = 0; i < v_size_; i++) {
            for (auto& e : g_[i]) {
                int x = component[i], y = component[e.to];
                if (x == y) continue;
                res.add_edge(x, y, e.cost);
            }
        }
        return res;
    }
};