#pragma once

#include <vector>

template <class T> class CumulativeSum2D {
  private:
    std::vector<std::vector<T>> data_;

  public:
    CumulativeSum2D(int H, int W) : data_(H + 3, std::vector<T>(W + 3, 0)) {}

    void add(int i, int j, T x) {
        i++, j++;
        if ((int)(data_.size()) <= i || (int)(data_[0].size()) <= j) return;
        data_[i][j] += x;
    }

    void imos(int i1, int j1, int i2, int j2, T x) {
        add(i1, j1, x);
        add(i1, j2, -x);
        add(i2, j1, -x);
        add(i2, j2, x);
    }

    void build() {
        for (int i = 1; i < (int)(data_.size()); i++) {
            for (int j = 1; j < (int)(data_[i].size()); j++) {
                data_[i][j] +=
                    data_[i][j - 1] + data_[i - 1][j] - data_[i - 1][j - 1];
            }
        }
    }

    T imos_get(int i, int j) { return data_[i + 1][j + 1]; }

    T get(int i1, int j1, int i2, int j2) {
        return data_[i2][j2] - data_[i1][j2] - data_[i2][j1] + data_[i1][j1];
    }
};