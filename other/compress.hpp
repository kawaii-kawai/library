#pragma once

#include <algorithm>
#include <vector>

template <class T> class Compress {
  private:
    std::vector<T> raws_;

  public:
    Compress(const std::vector<T>& raws = {}) : raws_(raws) {}

    void add(const T& x) { raws_.emplace_back(x); }

    void build() {
        std::sort(raws_.begin(), raws_.end());
        raws_.erase(std::unique(raws_.begin(), raws_.end()), raws_.end());
    }

    T operator[](int k) const { return raws_[k]; }

    int get(const T& x) const {
        return std::lower_bound(raws_.begin(), raws_.end(), x) - raws_.begin();
    }

    int lower_bound(const T& x) const {
        return std::lower_bound(raws_.begin(), raws_.end(), x) - raws_.begin();
    }

    int upper_bound(const T& x) const {
        return std::upper_bound(raws_.begin(), raws_.end(), x) - raws_.begin();
    }

    int size() const { return (int)(raws_.size()); }
};