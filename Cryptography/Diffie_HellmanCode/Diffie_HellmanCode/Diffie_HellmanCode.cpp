// Diffie Hellman Key Exchange Algorithm 
#include <iostream>
#include <cmath>
#include "mpir.h"
#include "bigint.h"
#include "Diffie.h"
using namespace std;
using namespace iamtcs;

void static print(BigInt& num)   // Function to print the value.
{
    char* str = NULL;
    unsigned int len;
    num.toStr(str, len, 10);
    cout << "num: " << str << endl;
    

}

int main() {
    BigInt n, g;
     n = 37; // Prime number n
     g = 41; // Prime number g
     
    DiffieHellman dh(n, g);

    BigInt x, y, a, b, key_1, key_2;

    x = dh.getPrivateKeyx(); // Private key calculation for User 1
    print(x);

    a = dh.generatePublicKeyx(x); // Public key calculation for User 1
    print(a);

    y = dh.getPrivateKeyy(); // Private key calculation for User 2
    print(y);
    
    b = dh.generatePublicKeyy(y); // Public key calculation for User 2
    print(b);
    
    key_1 = dh.generateSecretKeyx(x, b); // Secret Key Calculation of User 1
    print(key_1);
    
    key_2 = dh.generateSecretKeyy(y, a); // Secret Key Calculation of User 2
    print(key_2);


  
  
    return 0;
}
