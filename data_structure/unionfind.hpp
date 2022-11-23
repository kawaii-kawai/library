#pragma once
#include <bits/stdc++.h>
using namespace std;

struct unionfind {
  public:
    vector<long long> par, sz;
    unionfind(int sz_) : par(sz_), sz(sz_, 1LL) {
        for (long long i = 0; i < sz_; i++) par[i] = i;
    }
    void init(long long sz_) {
        par.resize(sz_);
        sz.assign(sz_, 1LL);
        for (long long i = 0; i < sz_; i++) par[i] = i;
    }
    long long root(long long x) {
        while (par[x] != x) x = par[x] = par[par[x]];
        return x;
    }
    bool merge(long long x, long long y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        sz[x] += sz[y];
        par[y] = x;
        return true;
    }
    bool same(long long x, long long y) {
        return root(x) == root(y);
    }
    long long size(long long x) {
        return sz[root(x)];
    }
    
};