#pragma once
#include <bits/stdc++.h>
using namespace std;

template <class T, T (*op)(T, T), T (*e)()> struct segtree {
  private:
    int n;
    vector<T> data;

  public:
    segtree(int n_) {
        n = 1;
        while (n_ > n) n *= 2;
        data.resize(2 * n, e());
    }
    int operator[](int i) { return data[i + n]; }
    void set(int i, T x) {
        i += n;
        data[i] = x;
        while (i > 0) {
            i = i / 2;
            data[i] = op(data[i * 2], data[i * 2 + 1]);
        }
    }
    T prod(int l, int r) { //[l, r) 0-idx
        T Lres = e(), Rres = e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) Lres = op(Lres, data[l++]);
            if (r & 1) Rres = op(data[--r], Rres);
        }
        return op(Lres, Rres);
    }
};