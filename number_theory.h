//
// Created by Sviatoslav Bidzilia on 12.05.2024.
//

#ifndef CRYPTO_NUMBER_THEORY_H

template<typename T>
T gcd(T a, T b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

template<typename T>
T lcm(T a, T b) {
    return a / gcd<T>(a, b) * b;
}

template<typename T>
void euclid(const T &a, const T &b, T &x, T &y, T &d) {
    if (a == 0) {
        x = 0;
        y = 1;
        d = b;
        return;
    }
    if (b == 0) {
        x = a;
        y = 0;
        d = a;
        return;
    }
    if (a >= b) {
        T q = a / b;
        T r = a - b * q;
        euclid(r, b, x, y, d);
        y = y + q * x;
    }
    else {
        T q = b / a;
        T r = b - a * q;
        euclid(a, r, x, y, d);
        x = x + q * y;
    }
}
template<typename T>
T inverse_module(const T& a, const T& p) {
    T b = a % p;
    if (b == 0)
        return b;
    T x = 0, y = 0, d = 0;
    euclid(b, p, x, y, d);
    if (b * x > p * y)
        return x;
    else
        return p - x;
}

#define CRYPTO_NUMBER_THEORY_H

#endif //CRYPTO_NUMBER_THEORY_H
