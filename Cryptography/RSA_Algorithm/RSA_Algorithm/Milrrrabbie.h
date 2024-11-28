#pragma once
#ifndef IS_PRIME_H
#define IS_PRIME_H

#include "InfInt.h"

// Calculate (a * b) % mod
InfInt mulmod(InfInt a, InfInt b, InfInt mod);

// Calculate (a^b) % mod
InfInt power(InfInt a, InfInt b, InfInt mod);

// Miller-Rabin primality test
bool is_prime(InfInt n, int k);

#endif
