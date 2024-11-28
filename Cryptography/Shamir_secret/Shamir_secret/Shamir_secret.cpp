// C++ Program to implement Shamir Secret Algorthm
#include<iostream>
#include<vector>
#include<cmath>
#include "InfInt.h" // Include Infint library header file
#include"SSA.h"
// ask the users wth the numbers of shares 
// x values should be random numbers 
// consider a large prime and to all the modular arithmetic operations as mod p .
// Use BigInt library 
using namespace std;

int main()
{
    InfInt secret, n, k;
    cout << "                                       SHAMIR SECRET SHARING ALGORITHM " << endl;
    cout << "Enter the secret key :";
    cin >> secret;
    cout << "Enter the number of shares : ";
    cin >> n;
    cout << "Enter the minimum required shares: ";
    cin >> k;

    // Create SSA object  
    SSA ssa(secret.toString(), n.toInt(), k.toInt());

    // Perform secret sharing
    ssa.operation();
   
    return 0;
}