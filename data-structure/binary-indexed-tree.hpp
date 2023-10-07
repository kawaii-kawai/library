#pragma once

#include <vector>

template <class T> class BinaryIndexedTree {
  private:
    int size_;
    std::vector<T> data_;

    void init(int sz) {
        size_ = sz + 2;
        data_.assign(size_ + 1, 0);
    }

    // sum of [0, k)
    T sum(int k) const {
        T res = 0;
        while (k) {
            res += data_[k];
            k -= k & -k;
        }
        return res;
    }

  public:
    BinaryIndexedTree() = default;
    BinaryIndexedTree(int sz) { init(sz); }
    BinaryIndexedTree(std::vector<T> vec) {
        init(vec.size());
        for (int i = 0; i < size_; i++) add(i, vec[i]);
    }

    // add x to data[k]
    void add(int k, T x) {
        k++;
        while (k <= size_) {
            data_[k] += x;
            k += k & -k;
        }
    }

    // sum of [l, r)
    inline T sum(int l, int r) const { return sum(r) - sum(l); }

    // data[k]
    inline T operator[](int k) const { return sum(k + 1) - sum(k); }

    // sum of [0, k) >= w
    int lower_bound(T w) {
        if (w <= 0) return 0;
        int x = 0;
        for (int k = 1 << std::__lg(size_); k; k >>= 1) {
            if (x + k <= size_ - 1 && data_[x + k] < w) {
                w -= data_[x + k];
                x += k;
            }
        }
        return x + 1;
    }

    // sum of [0, k) > w
    int upper_bound(T w) {
        if (w < 0) return 0;
        int x = 0;
        for (int k = 1 << std::__lg(size_); k; k >>= 1) {
            if (x + k <= size_ - 1 && data_[x + k] <= w) {
                w -= data_[x + k];
                x += k;
            }
        }
        return x + 1;
    }
};