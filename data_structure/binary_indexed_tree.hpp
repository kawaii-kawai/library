#pragma once
#include <bits/stdc++.h>
using namespace std;

template <class T> struct binary_indexed_tree {
  public:
    binary_indexed_tree(int n_) : n(n_) { bit.resize(n + 1); }
    void add(int a, T x) {
        a++;
        while (a <= n) {
            bit[a] += x;
            a += -a & a;
        }
    }
    T sum(int l, int r) { return sum(r) - sum(l); }

  private:
    int n;
    vector<T> bit;
    T sum(int a) {
        T r = 0;
        while (0 < a) {
            r += bit[a];
            a -= -a & a;
        }
        return r;
    }
};