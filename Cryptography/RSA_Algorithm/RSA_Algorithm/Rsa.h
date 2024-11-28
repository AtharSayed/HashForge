#pragma once
// RSA Header file for RSA Class 
#include <string>
#include <vector>
#include "InfInt.h"

class RSA {
private:
    InfInt p, q, n, t, e, d;
    std::vector<InfInt> encrypted, decrypted;

public:
    RSA();
    RSA(InfInt p_, InfInt q_);  // Taking prime numbers p & q
    InfInt gcd(InfInt a, InfInt b);  
    void generate_keys();
    InfInt pow_mod(InfInt base, InfInt exponent, InfInt modulus);
    void encrypt(std::string message);
    void decrypt();
    std::string get_encrypted_message() const;
    std::string get_decrypted_message() const;
    InfInt get_public_key() const;
    InfInt get_private_key() const;
};
