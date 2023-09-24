#pragma once

#include <vector>

template <class T> class Binomial {
  private:
    static std::vector<T> factorial;
    static std::vector<T> factinv;

  public:
    static void init(int n) {
        const int b = factorial.size();
        if (n < b) return;
        factorial.resize(n + 1);
        for (int i = b; i < n + 1; i++) factorial[i] = factorial[i - 1] * i;
        factinv.resize(n + 1);
        factinv[n] = T(1) / factorial[n];
        for (int i = n; i > b; i--) factinv[i - 1] = factinv[i] * i;
    }
    // x!
    static T fact(int x) {
        init(x);
        return factorial[x];
    }
    // 1 / x!
    static T finv(int x) {
        init(x);
        return factinv[x];
    }
    // 1 / x
    static T inv(int x) {
        init(x);
        return factorial[x - 1] * factinv[x];
    }
    // nPr
    static T perm(int n, int r) {
        if (r < 0 || r > n) return 0;
        init(n);
        return factorial[n] * factinv[n - r];
    }
    // nCr
    static T comb(int n, int r) {
        if (n < 0) return 0;
        if (r < 0 || r > n) return 0;
        init(n);
        return factorial[n] * factinv[n - r] * factinv[r];
    }
    // nHr
    static T homo(int n, int r) { return comb(n + r - 1, r); }
};

template <class T> std::vector<T> Binomial<T>::factorial = std::vector<T>(1, 1);
template <class T> std::vector<T> Binomial<T>::factinv = std::vector<T>(1, 1);