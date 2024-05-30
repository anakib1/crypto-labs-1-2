//
// Created by Sviatoslav Bidzilia on 12.05.2024.
//

#include "primes.h"
#include "number_theory.h"
#include <random>

#ifndef CRYPTO_RSA_H

std::uniform_int_distribution<ll> dist_random(0, (1LL << 63));

template<typename T>
T generate_key() {
    return dist_random(gen);
}

template<typename T>
T hash_key(T a) {
    return (a >> 11) ^ (a ^ 0xEEE6F123445) - (a << 7) ^ (a & 0xFE657E);
}


template<typename T>
class RSASender {
private:
    T n;
    T phi;
    T d;
    T e;
    int _bits_size;
    vector<pair<T, T> > _public_keys;
public:
    RSASender(int bits_size = 32) {
        _bits_size = bits_size;
        T p = generate_prime<T>(bits_size, 100);
        T q = generate_prime<T>(bits_size, 100);
        while (q == p) {
            q = generate_prime<T>(bits_size, 100);
        }
        n = p * q;
        phi = lcm(p - 1, q - 1);
        std::uniform_int_distribution<T> dist_big(2, phi - 1);

        e = dist_big(gen);
        while (gcd(e, phi) != 1)
            e = dist_big(gen);
        d = inverse_module<T>(e, phi);
    }

    void set_public_keys(vector<pair<T, T> > public_keys) {
        _public_keys = public_keys;
    }

    pair<T, T> get_public_key() {
        return {n, e};
    }

    T decode_message(T m, vector<T> signature) {
        for (int i = 0; i < _bits_size; i++) {
            int bit = m >> i & 1;
            T expected = bit ? _public_keys[i].second : _public_keys[i].first;
            if (hash_key(signature[i]) != expected) {
                std::cout << "Signature is invalid.";
                exit(1);
            }
        }
        return pow(m, d, n);
    }
};

template<typename T>
class RSAReceiver {
private:
    T n;
    T e;
    int _bit_size;
    vector<pair<T, T>> private_keys;
public:
    RSAReceiver(pair<T, T> public_key, int bit_size = 32) {
        n = public_key.first;
        e = public_key.second;
        _bit_size = bit_size;
        for (int i = 0; i < bit_size; i++) {
            private_keys.push_back(make_pair(generate_key<T>(), generate_key<T>()));
        }
    }

    vector<pair<T, T> > get_public_keys() {
        vector<pair<T, T>> ret;
        for (int i = 0; i < _bit_size; i++) {
            ret.push_back(make_pair(hash_key(private_keys[i].first), hash_key(private_keys[i].second)));
        }
        return ret;
    }

    pair<T, vector<T>> encode_message(T m) {
        T ret = pow(m, e, n);
        vector<T> signature;
        for (int i = 0; i < _bit_size; i++) {
            int bit = ret >> i & 1;
            signature.push_back(bit ? private_keys[i].second : private_keys[i].first);
        }
        return make_pair(ret, signature);
    }
};

#define CRYPTO_RSA_H

#endif //CRYPTO_RSA_H
