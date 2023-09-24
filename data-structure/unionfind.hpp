#pragma once

#include <algorithm>
#include <vector>

struct UnionFind {
    int size_;
    std::vector<int> par;

    UnionFind(int sz) : size_(sz), par(sz, -1) {}

    // return root of x
    int root(int x) {
        if (par[x] < 0) return x;
        return par[x] = root(par[x]);
    }

    // merge x and y
    bool merge(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) std::swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    // return true if x and y are in the same group
    bool same(int x, int y) { return root(x) == root(y); }

    // return size of group including x
    int size(int x) { return -par[root(x)]; }

    // return groups
    std::vector<std::vector<int>> groups() {
        std::vector<std::vector<int>> res(size_);
        for (int i = 0; i < size_; i++) res[root(i)].push_back(i);
        res.erase(
            std::remove_if(res.begin(), res.end(),
                           [](const std::vector<int>& v) { return v.empty(); }),
            res.end());
        return res;
    }
};