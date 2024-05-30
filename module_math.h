//
// Created by Sviatoslav Bidzilia on 12.05.2024.
//

#ifndef CRYPTO_MODULE_MATH_H


template<typename T>
T mul(T a, T b, T mod) {
    if (a == 0) {
        return (T) 0;
    }
    if (a % 2 == 0) {
        T ret = mul(a >> 1, b, mod);
        return (ret + ret) % mod;
    }
    return (mul(a - 1, b, mod) + b) % mod;
}

template<typename T>
T pow(T a, T p, T mod) {
    if (p == 0) {
        return (T) 1;
    }
    if (p % 2 == 0) {
        T ret = pow(a, p >> 1, mod);
        return mul(ret, ret, mod);
    }
    return mul(pow(a, p - 1, mod), a, mod);
}

#define CRYPTO_MODULE_MATH_H

#endif //CRYPTO_MODULE_MATH_H
