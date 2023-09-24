#pragma once

#include "../other/monoid.hpp"
#include "../template/bitop.hpp"

template <class M> class SegmentTree {
  private:
    using T = typename M::value_type;
    int n_, size_, log_;
    std::vector<T> data_;

    void init(const std::vector<T>& v) {
        size_ = (int)v.size();
        log_ = ceil_log2(size_);
        n_ = 1 << log_;
        data_.assign(2 * n_, M::identity());
        for (int i = 0; i < size_; i++) data_[n_ + i] = v[i];
        for (int i = n_ - 1; i >= 1; i--) {
            data_[i] = M::op(data_[2 * i], data_[2 * i + 1]);
        }
    }

    void update(int k) { data_[k] = M::op(data_[2 * k], data_[2 * k + 1]); }

  public:
    SegmentTree() : SegmentTree(0) {}
    SegmentTree(int sz) : SegmentTree(std::vector<T>(sz, M::identity())) {}
    SegmentTree(int sz, const T& v) : SegmentTree(std::vector<T>(sz, v)) {}
    SegmentTree(const std::vector<T>& v) { init(v); }

    // data[k] <- x
    void set(int k, const T& x) {
        k += n_;
        data_[k] = x;
        for (int i = 1; i <= log_; i++) update(k >> i);
    }

    // data[k]
    T get(int k) const { return data_[k + n_]; }

    // op(data[l], ..., data[r - 1])
    T prod(int l, int r) const {
        T sml = M::identity(), smr = M::identity();
        l += n_;
        r += n_;

        while (l < r) {
            if (l & 1) sml = M::op(sml, data_[l++]);
            if (r & 1) smr = M::op(data_[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return M::op(sml, smr);
    }

    // op(data[0], ..., data[n - 1])
    T all_prod() const { return data_[1]; }

    // max k s.t. f(op(data[l], ..., data[k - 1])) == true
    template <class F> int max_right(int l, const F& f) const {
        if (l == size_) return size_;
        l += n_;
        T sm = M::identity();
        do {
            while ((l & 2) == 0) l >>= 1;
            if (!f(M::op(sm, data_[l]))) {
                while (l < n_) {
                    l = (2 * l);
                    if (f(M::op(sm, data_[l]))) {
                        sm = M::op(sm, data_[l]);
                        l++;
                    }
                }
                return l - n_;
            }
            l++;
        } while ((l & -l) != l);
        return size_;
    }

    // min k s.t. f(op(data[k], ..., data[r - 1])) == true
    template <class F> int min_left(int r, const F& f) const {
        if (r == 0) return 0;
        r += n_;
        T sm = M::identity();
        do {
            r--;
            while (1 < r && (r % 2)) r >>= 1;
            if (!f(M::op(data_[r], sm))) {
                while (r < n_) {
                    r = (2 * r + 1);
                    if (f(M::op(data_[r], sm))) {
                        sm = M::op(data_[r], sm);
                        r--;
                    }
                }
                return r + 1 - n_;
            }
        } while ((r & -r) != r);
        return 0;
    }
};