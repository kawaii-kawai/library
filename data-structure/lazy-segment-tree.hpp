#pragma once

#include "../template/bitop.hpp"

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
class LazySegmentTree {
  private:
    int n_, size_, log_;
    std::vector<S> data_;
    std::vector<F> lazy_;

    void init(const std::vector<S> &vec) {
        size_ = (int)(vec.size());
        log_ = ceil_log2(size_);
        n_ = 1 << log_;
        data_.assign(2 * n_, e());
        lazy_.assign(n_, id());
        for (int i = 0; i < size_; i++) data_[n_ + i] = vec[i];
        for (int i = n_ - 1; i >= 1; i--) update(i);
    }

    void update(int k) { data_[k] = op(data_[2 * k], data_[2 * k + 1]); }

    void all_apply(int k, F f) {
        data_[k] = mapping(f, data_[k]);
        if (k < n_) lazy_[k] = composition(f, lazy_[k]);
    }

    void push(int k) {
        if (lazy_[k] == id()) return;
        all_apply(2 * k, lazy_[k]);
        all_apply(2 * k + 1, lazy_[k]);
        lazy_[k] = id();
    }
  
  public:
    LazySegmentTree() = default;
    explicit LazySegmentTree(int sz) : LazySegmentTree(std::vector<S>(sz, e())) {}
    explicit LazySegmentTree(int sz, S x) : LazySegmentTree(std::vector<S>(sz, x)) {}
    explicit LazySegmentTree(const std::vector<S> &vec) { init(vec); }

    void set(int k, S x) {
        k += n_;
        for (int i = log_; i >= 1; i--) push(k >> i);
        data_[k] = x;
        for (int i = 1; i <= log_; i++) update(k >> i);
    }

    S get(int k) {
        k += n_;
        for (int i = log_; i >= 1; i--) push(k >> i);
        return data_[k];
    }

    S prod(int l, int r) {
        if (l == r) return e();

        l += n_;
        r += n_;

        for (int i = log_; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, data_[l++]);
            if (r & 1) smr = op(data_[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return data_[1]; }

    void apply(int k, F f) {
        k += n_;
        for (int i = log_; i >= 1; i--) push(k >> i);
        data_[k] = mapping(f, data_[k]);
        for (int i = 1; i <= log_; i++) update(k >> i);
    }

    void apply(int l, int r, F f) {
        if (l == r) return;

        l += n_;
        r += n_;

        for (int i = log_; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log_; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        if (l == size_) return size_;
        l += n_;
        for (int i = log_; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, data_[l]))) {
                while (l < n_) {
                    push(l);
                    l = 2 * l;
                    if (g(op(sm, data_[l]))) {
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

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        if (r == 0) return 0;
        r += n_;
        for (int i = log_; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(data_[r], sm))) {
                while (r < n_) {
                    push(r);
                    r = 2 * r + 1;
                    if (g(op(data_[r], sm))) {
                        sm = op(data_[r], sm);
                        r--;
                    }
                }
                return r + 1 - n_;
            }
        } while ((r & -r) != r);
        return 0;
    }
};