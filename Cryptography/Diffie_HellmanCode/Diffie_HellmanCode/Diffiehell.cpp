
#include "gmp.h" // Added gmp 
#include "mpir.h"  // Added Mpir 
#include "../../../big_int_libraryfiles/bigint_demo/3rd-party.out/win64/mpir/include/bigint.h"// Assuming that BigInt is defined in a separate header file
#include "Diffie.h"

// DiffieHellman Class Defination for Diffie.h Header file

DiffieHellman::DiffieHellman(BigInt n, BigInt g) : n_(n), g_(g) {}

BigInt DiffieHellman::getPrivateKeyx() {
    // Generate a random private key
    BigInt x = 431; // For example purposes, a fixed value is used
    return x;
}

BigInt DiffieHellman::getPrivateKeyy() {
    // Generate a random private key
    BigInt y = 231; // For example purposes, a fixed value is used
    return y;
}

BigInt DiffieHellman::generatePublicKeyx(BigInt x) {
    // Calculate the public key using the private key, prime number n, and prime number g
    BigInt a;
    g_.powmod(x, n_, &a);
    return a;
}

BigInt DiffieHellman::generatePublicKeyy(BigInt y) {
    // Calculate the public key using the private key, prime number n, and prime number g
    BigInt b;
    g_.powmod(y, n_, &b);
    return b;
}

BigInt DiffieHellman::generateSecretKeyx(BigInt x, BigInt b) {
    // Calculate the secret key using the private key, prime number n, and public key of the other user
    BigInt key_1;
    b.powmod(x, n_, &key_1);
    return key_1;
}

BigInt DiffieHellman::generateSecretKeyy(BigInt y, BigInt b) {
    BigInt key_2;
    b.powmod(y, n_, &key_2);
    return key_2;
}
