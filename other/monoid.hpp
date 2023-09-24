#pragma once

#include <algorithm>
#include <limits>

struct Monoid {
    template <class T> struct Sum {
        using value_type = T;
        static constexpr T identity() { return T(0); }
        static constexpr T op(T a, T b) { return a + b; }
    };

    template <class T, T max_value = std::numeric_limits<T>::max()> struct Min {
        using value_type = T;
        static constexpr T identity() { return max_value; }
        static constexpr T op(T a, T b) { return std::min(a, b); }
    };

    template <class T, T min_value = std::numeric_limits<T>::min()> struct Max {
        using value_type = T;
        static constexpr T identity() { return min_value; }
        static constexpr T op(T a, T b) { return std::max(a, b); }
    };

    template <class T> struct Assign {
        using value_type = T;
        static constexpr T op(const T&, const T& b) { return b; }
    };

    template <class T, T max_value = std::numeric_limits<T>::max()>
    struct AssignMin {
        using M = Min<T, max_value>;
        using E = Assign<T>;
        static constexpr T op(const T& a, const T&, int) { return a; }
    };

    template <class T, T min_value = std::numeric_limits<T>::min()>
    struct AssignMax {
        using M = Max<T, min_value>;
        using E = Assign<T>;
        static constexpr T op(const T& a, const T&, int) { return a; }
    };

    template <class T> struct AssignSum {
        using M = Sum<T>;
        using E = Assign<T>;
        static constexpr T op(const T& a, const T&, int c) { return a * c; }
    };

    template <class T, T max_value = std::numeric_limits<T>::max()>
    struct AddMin {
        using M = Min<T, max_value>;
        using E = Sum<T>;
        static constexpr T op(const T& a, const T& b, int) { return a + b; }
    };

    template <class T, T min_value = std::numeric_limits<T>::min()>
    struct AddMax {
        using M = Max<T, min_value>;
        using E = Sum<T>;
        static constexpr T op(const T& a, const T& b, int) { return a + b; }
    };

    template <class T> struct AddSum {
        using M = Sum<T>;
        using E = Sum<T>;
        static constexpr T op(const T& a, const T& b, int c) {
            return b + a * c;
        }
    };

    template <class T, T max_value = std::numeric_limits<T>::max()>
    struct ChminMin {
        using M = Min<T, max_value>;
        using E = Min<T>;
        static constexpr T op(const T& a, const T& b, int) {
            return std::min(a, b);
        }
    };

    template <class T, T min_value = std::numeric_limits<T>::min()>
    struct ChminMax {
        using M = Max<T, min_value>;
        using E = Min<T>;
        static constexpr T op(const T& a, const T& b, int) {
            return std::min(a, b);
        }
    };

    template <class T, T max_value = std::numeric_limits<T>::max()>
    struct ChmaxMin {
        using M = Min<T, max_value>;
        using E = Max<T>;
        static constexpr T op(const T& a, const T& b, int) { std::max(a, b); }
    };

    template <class T, T min_value = std::numeric_limits<T>::min()>
    struct ChmaxMax {
        using M = Max<T, min_value>;
        using E = Max<T>;
        static constexpr T op(const T& a, const T& b, int) {
            return std::max(a, b);
        }
    };
};