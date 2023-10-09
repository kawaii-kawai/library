#pragma once

#include <vector>
#include "../template/bitop.hpp"

template <class S, S (*op)(S, S), S (*e)()>
class SegmentTree {
  private:
    int n_, size_, log_;
    std::vector<S> data_;

    void init(const std::vector<S>& vec) {
        size_ = (int)(vec.size());
        log_ = ceil_log2(size_);
        n_ = 1 << log_;
        data_.assign(2 * n_, e());
        for (int i = 0; i < size_; i++) data_[n_ + i] = vec[i];
        for (int i = n_ - 1; i >= 1; i--) update(i);
    }

    void update(int k) { data_[k] = op(data_[2 * k], data_[2 * k + 1]); }

  public:
    SegmentTree() = default;
    explicit SegmentTree(int sz) : SegmentTree(std::vector<S>(sz, e())) {}
    explicit SegmentTree(int sz, S x) : SegmentTree(std::vector<S>(sz, x)) {}
    explicit SegmentTree(const std::vector<S>& vec) { init(vec); }

    void set(int k, S x) {
        k += n_;
        data_[k] = x;
        for (int i = 1; i <= log_; i++) update(k >> i);
    }

    S get(int k) const { return data_[k + n_]; }

    S prod(int l, int r) const {
        S sml = e(), smr = e();
        l += n_;
        r += n_;

        while (l < r) {
            if (l & 1) sml = op(sml, data_[l++]);
            if (r & 1) smr = op(data_[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return data_[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        if (l == size_) return size_;
        l += n_;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, data_[l]))) {
                while (l < n_) {
                    l = (2 * l);
                    if (f(op(sm, data_[l]))) {
                        sm = op(sm, data_[l]);
                        l++;
                    }
                }
                return l - n_;
            }
            sm = op(sm, data_[l]);
            l++;
        } while ((l & -l) != l);
        return size_;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        if (r == 0) return 0;
        r += n_;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(data_[r], sm))) {
                while (r < n_) {
                    r = (2 * r + 1);
                    if (f(op(data_[r], sm))) {
                        sm = op(data_[r], sm);
                        r--;
                    }
                }
                return r + 1 - n_;
            }
            sm = op(data_[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};