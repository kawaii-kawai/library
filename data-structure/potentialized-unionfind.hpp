#pragma once

#include <vector>

template <class S, S (*op)(S, S), S (*e)(), S (*inv)(S)>
class PotentializedUnionFind {
  private:
    int size_;
    std::vector<int> par_;
    std::vector<S> potential_;

  public:
    PotentializedUnionFind() = default;
    explicit PotentializedUnionFind(int sz) : size_(sz), par_(sz, -1), potential_(sz, e()) {}

    int root(int x) {
        if (par_[x] < 0) return x;
        int r = root(par_[x]);
        potential_[x] = op(potential_[par_[x]], potential_[x]);
        return par_[x] = r;
    }

    bool merge(int x, int y, S d) {
        d = op(op(potential(x), d), inv(potential(y)));
        x = root(x), y = root(y);
        if (x == y) return false;
        if (par_[x] > par_[y]) {
            std::swap(x, y);
            d = inv(d);
        }
        par_[x] += par_[y];
        par_[y] = x;
        potential_[y] = d;
        return true;
    }

    S potential(int x) {
        root(x);
        return potential_[x];
    }

    S diff(int x, int y) {
        return op(inv(potential(x)), potential(y));
    }

    bool same(int x, int y) { return root(x) == root(y); }

    int size(int x) { return -par_[root(x)]; }
};