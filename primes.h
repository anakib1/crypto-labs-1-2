//
// Created by Sviatoslav Bidzilia on 12.05.2024.
//
#include "module_math.h"
#include <string>
#include <random>

#define ll long long

#ifndef CRYPTO_PRIMES_H


using namespace std;


std::mt19937_64 gen;
std::uniform_int_distribution<ll> dist_01(0, 1);

template<typename T>
bool miller_rabin(T n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    T d = n - 1;
    T s = 0;
    while (d % 2 == 0) {
        s++;
        d >>= 1;
    }

    for (T a: {2, 3, 5, 7, 11}) {
        T x = pow(a, d, n);
        for (int i = 0; i < s; i++) {
            T y = mul(x, x, n);
            if (y == 1 && x != 1 and x != n - 1)
                return false;
            x = y;
        }

        if (x != 1) return false;
    }
    return true;
}

string output_symbols = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-";

template<typename T>
string parse_base_k(T num, int base) {
    string ret = "";
    string sign = "";
    if (num < 0) {
        sign = "-";
        num = -num;
    }
    while (num > 0) {
        ret.push_back(output_symbols[num % base]);
        num /= base;
    }
    reverse(ret.begin(), ret.end());
    return sign + ret;
}


template<typename T>
T generate_odd_number(int bit_len) {
    T num(1);
    for (int i = 0; i < bit_len - 2; i++) {
        num = num * (T)(2) + (T)(dist_01(gen));
    }
    num = num * (T)(2) + (T)(1);
    return num;
}

template<typename T>
T generate_prime(int bit_len, int random_tries) {
    for (int i = 0; i < random_tries; i++) {
        T number = generate_odd_number<T>(bit_len);
        int is_prime = miller_rabin(number);
        if (is_prime)
            return number;
    }
    return (T)(1);
}

#define CRYPTO_PRIMES_H

#endif //CRYPTO_PRIMES_H
