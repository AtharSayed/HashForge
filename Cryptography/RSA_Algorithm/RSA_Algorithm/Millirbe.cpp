#include "Milrrrabbie.h"
#include "InfInt.h"
#include <cstdlib>
#include <ctime>

// Calculate (a * b) % mod
InfInt mulmod(InfInt a, InfInt b, InfInt mod) {
    InfInt res = 0;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1) {
            res = (res + a) % mod;
        }
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}

// Calculate (a^b) % mod
InfInt power(InfInt a, InfInt b, InfInt mod) {
    InfInt res = 1;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1) {
            res = mulmod(res, a, mod);
        }
        a = mulmod(a, a, mod);
        b /= 2;
    }
    return res;
}

// Miller-Rabin primality test
bool is_prime(InfInt n, int k) {
    // Base cases
    if (n <= 1 || n == 4) {
        return false;
    }
    if (n <= 3) {
        return true;
    }

    // Find r and d such that n = 2^r * d + 1
    InfInt d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
   

    // Seed random number generator
    srand(time(NULL));

    // Repeat k times
    for (int i = 0; i < k; i++) {
        // Generate a random witness in [2, n-2]
        InfInt a = rand();
a %= (n - 3);
a += 2;




        // Compute a^d % n
        InfInt x = power(a, d, n);

        // If x is 1 or n-1, n is probably prime
        if (x == 1 || x == n - 1) {
            continue;
        }

        // Repeat r-1 times
        bool prime = false;
        for (int j = 0; j < r - 1; j++) {
            x = mulmod(x, x, n);
            if (x == n - 1) {
                prime = true;
                break;
            }
        }

        // If n is not prime, return false
        if (!prime) {
            return false;
        }
    }

    // If n passes all tests, return true
    return true;
}
