#pragma once

#include <vector>

class LowestCommonAncestor {
  private:
    std::vector<std::vector<int>> parent_;
    std::vector<int> depth_;
    int size_, root_;

    void init(const std::vector<std::vector<int>>& graph, int root) {
        size_ = graph.size();
        root_ = root;
        int log_size = 1;
        while ((1 << log_size) < size_) log_size++;
        parent_.assign(log_size, std::vector<int>(size_, -1));
        depth_.assign(size_, -1);
        dfs(graph, root, -1, 0);
        for (int k = 0; k + 1 < log_size; k++) {
            for (int v = 0; v < size_; v++) {
                if (parent_[k][v] < 0) {
                    parent_[k + 1][v] = -1;
                } else {
                    parent_[k + 1][v] = parent_[k][parent_[k][v]];
                }
            }
        }
    }

    void dfs(const std::vector<std::vector<int>>& graph, int v, int p, int d) {
        parent_[0][v] = p;
        depth_[v] = d;
        for (int e : graph[v]) {
            if (e != p) dfs(graph, e, v, d + 1);
        }
    }

  public:
    LowestCommonAncestor(const std::vector<std::vector<int>>& graph, int root) {
        init(graph, root);
    }

    int query(int u, int v) {
        if (depth_[u] < depth_[v]) std::swap(u, v);
        int log_size = parent_.size();
        for (int k = 0; k < log_size; k++) {
            if ((depth_[u] - depth_[v]) >> k & 1) {
                u = parent_[k][u];
            }
        }
        if (u == v) return u;
        for (int k = log_size - 1; k >= 0; k--) {
            if (parent_[k][u] != parent_[k][v]) {
                u = parent_[k][u];
                v = parent_[k][v];
            }
        }
        return parent_[0][u];
    }
};