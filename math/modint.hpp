#pragma once

#include <iostream>

template <std::uint_fast64_t Modulus> class StaticModInt {
    using u64 = std::uint_fast64_t;

  public:
    u64 val;

    StaticModInt(const int64_t x = 0) noexcept
        : val(x >= 0 ? x % Modulus : (Modulus - (-x) % Modulus) % Modulus) {}
    u64& value() noexcept { return val; }
    const u64& value() const noexcept { return val; }
    StaticModInt operator+(const StaticModInt rhs) const noexcept {
        return StaticModInt(*this) += rhs;
    }
    StaticModInt operator-(const StaticModInt rhs) const noexcept {
        return StaticModInt(*this) -= rhs;
    }
    StaticModInt operator*(const StaticModInt rhs) const noexcept {
        return StaticModInt(*this) *= rhs;
    }
    StaticModInt operator/(const StaticModInt rhs) const noexcept {
        return StaticModInt(*this) /= rhs;
    }
    StaticModInt& operator+=(const StaticModInt rhs) noexcept {
        val += rhs.val;
        if (val >= Modulus) val -= Modulus;
        return *this;
    }
    StaticModInt& operator-=(const StaticModInt rhs) noexcept {
        if (val < rhs.val) val += Modulus;
        val -= rhs.val;
        return *this;
    }
    StaticModInt& operator*=(const StaticModInt rhs) noexcept {
        val = val * rhs.val % Modulus;
        return *this;
    }
    StaticModInt& operator/=(StaticModInt rhs) noexcept {
        return *this *= rhs.inv();
    }
    StaticModInt operator+() const { return *this; }
    StaticModInt operator-() const { return StaticModInt() - *this; }
    StaticModInt pow(long long n) const {
        StaticModInt x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    StaticModInt inv() const { return pow(Modulus - 2); }

    friend std::ostream& operator<<(std::ostream& os, const StaticModInt& rhs) {
        return os << rhs.val;
    }
    friend std::istream& operator>>(std::istream& is, StaticModInt& rhs) {
        return is >> rhs.val;
    }
};

using modint1000000007 = StaticModInt<1000000007>;
using modint998244353 = StaticModInt<998244353>;

class DynamicModInt {
    using u64 = std::uint_fast64_t;

    static u64& mod() {
        static u64 mod_ = 0;
        return mod_;
    }

  public:
    u64 val;

    DynamicModInt(const int64_t x = 0)
        : val(x >= 0 ? x % get_mod()
                     : (get_mod() - (-x) % get_mod()) % get_mod()) {}
    u64& value() noexcept { return val; }
    const u64& value() const noexcept { return val; }
    DynamicModInt operator+(const DynamicModInt rhs) const {
        return DynamicModInt(*this) += rhs;
    }
    DynamicModInt operator-(const DynamicModInt rhs) const {
        return DynamicModInt(*this) -= rhs;
    }
    DynamicModInt operator*(const DynamicModInt rhs) const {
        return DynamicModInt(*this) *= rhs;
    }
    DynamicModInt operator/(const DynamicModInt rhs) const {
        return DynamicModInt(*this) /= rhs;
    }
    DynamicModInt& operator+=(const DynamicModInt rhs) {
        val += rhs.val;
        if (val >= get_mod()) val -= get_mod();
        return *this;
    }
    DynamicModInt& operator-=(const DynamicModInt rhs) {
        if (val < rhs.val) val += get_mod();
        val -= rhs.val;
        return *this;
    }
    DynamicModInt& operator*=(const DynamicModInt rhs) {
        val = val * rhs.val % get_mod();
        return *this;
    }
    DynamicModInt& operator/=(DynamicModInt rhs) { return *this *= rhs.inv(); }
    DynamicModInt operator+() const { return *this; }
    DynamicModInt operator-() const { return DynamicModInt() - *this; }
    DynamicModInt pow(long long n) const {
        DynamicModInt x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    DynamicModInt inv() const { return pow(get_mod() - 2); }
    friend std::ostream& operator<<(std::ostream& os,
                                    const DynamicModInt& rhs) {
        return os << rhs.val;
    }
    friend std::istream& operator>>(std::istream& is, DynamicModInt& rhs) {
        return is >> rhs.val;
    }

    static void set_mod(const u64 x) { mod() = x; }
    static u64 get_mod() { return mod(); }
};