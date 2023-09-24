#pragma once

#include <vector>

template <class T> class CumulativeSum {
  private:
    std::vector<T> data_;

  public:
    CumulativeSum(int sz) : data_(sz + 1, 0) {}
    CumulativeSum(const std::vector<T>& vec) : data_(vec.size() + 1, 0) {
        for (int i = 0; i < (int)(vec.size()); i++) {
            add(i, vec[i]);
        }
        build();
    }

    void add(int k, T x) { data_[k + 1] += x; }

    void build() {
        for (int i = 1; i < (int)(data_.size()); i++) {
            data_[i] += data_[i - 1];
        }
    }

    T prod(int r) const {
        if (r < 0) return 0;
        return data_[r];
    }

    T prod(int l, int r) const { return prod(r) - prod(l); }
};