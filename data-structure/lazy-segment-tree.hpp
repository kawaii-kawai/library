#pragma once

#include "../other/monoid.hpp"
#include "../template/bitop.hpp"

template <class A> class LazySegmentTree {
  private:
    using M = typename A::M;
    using E = typename A::E;
    using T = typename M::value_type;
    using U = typename E::value_type;

    int n_, size_, log_;
    std::vector<T> data_;
    std::vector<U> lazy_;
    std::vector<bool> lazy_flag_;

    void init(const std::vector<T>& vec) {
        size_ = (int)vec.size();
        log_ = cp_library::ceil_log2(size_);
        n_ = 1 << log_;
        data_.assign(2 * n_, M::identity());
        lazy_.resize(n_);
        lazy_flag_.assign(n_, false);
        for (int i = 0; i < size_; i++) data_[n_ + i] = vec[i];
        for (int i = n_ - 1; i >= 1; i--) {
            data_[i] = M::op(data_[2 * i], data_[2 * i + 1]);
        }
    }

    void all_apply(int k, const U& x, int d) {
        data_[k] = A::op(x, data_[k], d);
        if (k < n_) {
            if (lazy_flag_[k]) {
                lazy_[k] = E::op(lazy_[k], x);
            } else {
                lazy_[k] = x;
                lazy_flag_[k] = true;
            }
        }
    }

    void eval(int k, int d) {
        if (lazy_flag_[k]) {
            all_apply(2 * k, lazy_[k], d >> 1);
            all_apply(2 * k + 1, lazy_[k], d >> 1);
            lazy_flag_[k] = false;
        }
    }

    void calc(int k) { data_[k] = M::op(data_[2 * k], data_[2 * k + 1]); }

  public:
    LazySegmentTree() : LazySegmentTree(0) {}
    LazySegmentTree(int sz)
        : LazySegmentTree(std::vector<T>(sz, M::identity())) {}
    LazySegmentTree(int sz, const T& v)
        : LazySegmentTree(std::vector<T>(sz, v)) {}
    LazySegmentTree(const std::vector<T>& vec) { init(vec); }

    // op(data[l], ..., data[r - 1])
    T prod(int l, int r) {
        if (l == r) return M::identity();
        l += n_, r += n_;
        for (int i = log_; i >= 1; i--) {
            bool seen = false;
            if (((l >> i) << i) != l) eval(l >> i, 1 << i), seen = true;
            if (((r >> i) << i) != r) eval((r - 1) >> i, 1 << i), seen = true;
            if (!seen) break;
        }

        T lsm = M::identity(), rsm = M::identity();
        while (l != r) {
            if (l & 1) lsm = M::op(lsm, data_[l++]);
            if (r & 1) rsm = M::op(data_[--r], rsm);
            l >>= 1, r >>= 1;
        }
        return M::op(lsm, rsm);
    }

    // data[k]
    T get(int k) {
        k += n_;
        for (int i = log_; i >= 1; i--) eval(k >> i, 1 << i);
        return data_[k];
    }

    // op(data[0], ..., data[n - 1])
    T all_prod() { return data_[1]; }

    // apply x to op(data[l], ..., data[r - 1])
    void apply(int l, int r, const T& x) {
        if (l == r) return;

        l += n_, r += n_;
        for (int i = log_; i >= 1; i--) {
            if (((l >> i) << i) != l) eval(l >> i, 1 << i);
            if (((r >> i) << i) != r) eval((r - 1) >> i, 1 << i);
        }

        for (int l2 = l, r2 = r, d = 1; l2 != r2; l2 >>= 1, r2 >>= 1, d <<= 1) {
            if (l2 & 1) all_apply(l2++, x, d);
            if (r2 & 1) all_apply(--r2, x, d);
        }

        for (int i = 1; i <= log_; i++) {
            if (((l >> i) << i) != l) calc(l >> i);
            if (((r >> i) << i) != r) calc((r - 1) >> i);
        }
    }

    // max k s.t. f(op(data[l], ..., data[k - 1])) == true
    template <class F> int max_right(int l, const F& f) const {
        if (l == size_) return size_;
        l += n_;
        for (int i = log_; i >= 1; i--) {
            if (((l >> i) << i) != l)
                eval(l >> i, 1 << i);
            else
                break;
        }

        T sm = M::identity();
        int d = 1;
        do {
            while ((l & 1) == 0) l >>= 1, d <<= 1;
            if (!f(M::op(sm, data_[l]))) {
                while (l < n_) {
                    eval(l, d);
                    l <<= 1;
                    d >>= 1;
                    if (f(M::op(sm, data_[l]))) sm = M::op(sm, data_[l++]);
                }
            }
            sm = M::op(sm, data_[l++]);
        } while ((l & -l) != l);
        return size_;
    }

    // min k s.t. f(op(data[k], ..., data[r - 1])) == true
    template <class F> int min_left(int r, const F& f) const {
        if (r == 0) return 0;

        r += n_;
        for (int i = log_; i >= 1; i--) {
            if (((r >> i) << i) != r)
                eval((r - 1) >> i, 1 << i);
            else
                break;
        }

        T sm = M::identity();
        int d = 1;
        do {
            r--;
            while ((r & 1) && r > 1) r >>= 1, d <<= 1;
            if (!f(data_[r], sm)) {
                while (r < n_) {
                    eval(r, n_);
                    r = 2 * r + 1;
                    d >>= 2;
                    if (f(M::op(data_[r], sm))) sm = M::op(data_[r--], sm);
                }
                return r + 1 - n_;
            }
            sm = M::op(data_[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};

template <class T, T max_value = std::numeric_limits<T>::max()>
using UpdateMinLazySegmentTree =
    LazySegmentTree<Monoid::AssignMin<T, max_value>>;

template <class T, T min_value = std::numeric_limits<T>::min()>
using UpdateMaxLazySegmentTree =
    LazySegmentTree<Monoid::AssignMax<T, min_value>>;

template <class T>
using UpdateSumLazySegmentTree = LazySegmentTree<Monoid::AssignSum<T>>;

template <class T, T max_value = std::numeric_limits<T>::max()>
using AddMinLazySegmentTree = LazySegmentTree<Monoid::AddMin<T, max_value>>;

template <class T, T min_value = std::numeric_limits<T>::min()>
using AddMaxLazySegmentTree = LazySegmentTree<Monoid::AddMax<T, min_value>>;

template <class T>
using AddSumLazySegmentTree = LazySegmentTree<Monoid::AddSum<T>>;

template <class T, T max_value = std::numeric_limits<T>::max()>
using ChminMinLazySegmentTree = LazySegmentTree<Monoid::ChminMin<T>>;

template <class T, T min_value = std::numeric_limits<T>::min()>
using ChminMaxLazySegmentTree = LazySegmentTree<Monoid::ChminMax<T>>;

template <class T, T max_value = std::numeric_limits<T>::max()>
using ChmaxMinLazySegmentTree = LazySegmentTree<Monoid::ChmaxMin<T>>;

template <class T, T min_value = std::numeric_limits<T>::min()>
using ChmaxMaxLazySegmentTree = LazySegmentTree<Monoid::ChmaxMax<T>>;