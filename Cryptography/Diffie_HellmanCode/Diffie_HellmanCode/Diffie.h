#pragma once
using namespace std;
using namespace iamtcs;
#include <iostream>
#include <string>
#include <vector>

class DiffieHellman {
public:
    DiffieHellman(BigInt n, BigInt g);

    BigInt getPrivateKeyx();

    BigInt getPrivateKeyy();

    BigInt generatePublicKeyx(BigInt x);

    BigInt generatePublicKeyy(BigInt y);

    BigInt generateSecretKeyx(BigInt x, BigInt b);

    BigInt generateSecretKeyy(BigInt y, BigInt b);

private:
    BigInt n_, g_;
};
