#include <iostream>
#include <string>
#include "rsa.h"
#include "primes.h"

#define ll long long

using namespace std;

template<typename T>
void assertEquals(T expected, T actual) {
    if (expected != actual) {
        cout << "Expected: " << expected << ", but was: " << actual << '\n';
        exit(1);
    }
}

void test_odd_gen() {
    int num = generate_odd_number<int>(11);
    string bit2 = parse_base_k(num, 2);
    assertEquals<int>(11, bit2.size());
}

void test_prime_gen() {
    int num = generate_prime<int>(11, 100);
    string bit2 = parse_base_k(num, 2);
    assertEquals<int>(11, bit2.size());
    assertEquals<bool>(true, miller_rabin(num));
}

void test_miller() {
    assertEquals<bool>(true, miller_rabin(127));
    assertEquals<bool>(false, miller_rabin(128));
    assertEquals<bool>(true, miller_rabin((int) (1e9) + 7));
    assertEquals<bool>(true, miller_rabin((int) (1e9) + 9));
    assertEquals<bool>(true, miller_rabin(998244353));
    assertEquals<bool>(true, miller_rabin(1000000000039));
    assertEquals<bool>(false, miller_rabin(31 * 1000000000039));
    assertEquals<bool>(false, miller_rabin(31 * 127 * 1000000000039));
    assertEquals<bool>(false, miller_rabin(62298863484143));
    assertEquals<bool>(true, miller_rabin(73275315729173));
}

void test_rsa() {
    auto alice = RSASender<ll>(16);
    pair<ll, ll> key = alice.get_public_key();
    auto bob = RSAReceiver<ll>(key, 16);
    alice.set_public_keys(bob.get_public_keys());

    std::uniform_int_distribution<ll> msg_distr(0, key.first - 1);
    ll message = msg_distr(gen);
    pair<ll, vector<ll> > encoded = bob.encode_message(message);
    ll decoded = alice.decode_message(encoded.first, encoded.second);
    cout << parse_base_k(decoded, 64) << ' ' << parse_base_k(encoded.first, 64)  << ' ' << parse_base_k(message, 64) << '\n';
    assertEquals(message, decoded);
}


void test() {
    test_odd_gen();
    test_prime_gen();
    test_miller();
    for (int i = 0; i < 25; i++)
        test_rsa();
}

int main() {
    test();
    __int128 ret = generate_prime<__int128>(100, 1000);
    std::cout << parse_base_k<__int128>(ret, 10) << '\n';
    return 0;
}
