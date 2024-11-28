#include "rsa.h"
#include <algorithm>
#include <cstdlib>


RSA::RSA() {}

RSA::RSA(InfInt p_, InfInt q_) : p(p_), q(q_) {
    n = p * q;
    t = (p - 1) * (q - 1);
    generate_keys();
}

InfInt RSA::gcd(InfInt a, InfInt b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

void RSA::generate_keys() {
    InfInt k = 1;
    std::vector<InfInt> possible_e;
    for (InfInt i = 2; i < t; i++) {
        if (t % i == 0) continue;
        if (gcd(i, t) == 1) possible_e.push_back(i);
    }

    e = possible_e[std::rand() % possible_e.size()];

    while (1) {
        k += t;
        if (k % e == 0) {
            d = k / e;
            break;
        }
    }
}

InfInt RSA::pow_mod(InfInt base, InfInt exponent, InfInt modulus) {
    InfInt result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

void RSA::encrypt(std::string message) {
    encrypted.clear();
    for (size_t i = 0; i < message.length(); i++) {
        InfInt c = message[i];
        c = pow_mod(c, e, n);
        encrypted.push_back(c);
    }
}

void RSA::decrypt() {
    decrypted.clear();
    for (size_t i = 0; i < encrypted.size(); i++) {
        InfInt c = encrypted[i];
        c = pow_mod(c, d, n);
        decrypted.push_back(c);
    }
}

std::string RSA::get_encrypted_message() const {
    std::string result;
    for (size_t i = 0; i < encrypted.size(); i++) {
        result += static_cast<char>(encrypted[i].toInt());
    }
    return result;
}

std::string RSA::get_decrypted_message() const {
    std::string result;
    for (size_t i = 0; i < decrypted.size(); i++) {
        result += static_cast<char>(decrypted[i].toInt());
    }
    return result;
}

InfInt RSA::get_public_key() const {
    return e;
}

InfInt RSA::get_private_key() const {
    return d;
}