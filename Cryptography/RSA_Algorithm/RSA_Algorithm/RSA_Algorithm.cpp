// RSA Algorithm implementation using InfInt Library 
#include <iostream>
#include <string>
#include <vector>
#include "InfInt.h"
#include"Rsa.h"
#include"Milrrrabbie.h"

using namespace std;
int main() {
    cout << "                                         RSA ALGORITHM " << endl;
   
    InfInt p, q;
    cout << "Enter the value of p :";
    cin >> p;
    cout << "Enter the value of q : ";
    cin >> q;

    if (is_prime(p, 10)) {
        cout << p << " is prime" << endl;
    }

    else {
        cout << p << " is not prime" << endl;
        return -1;
        
    }
    // Check if q is prime
    if (is_prime(q, 10)) {
        cout << q << " is prime" << endl;
    }

    else {
        cout << q << " is not prime " << endl;
        return -1;
    }
  
    RSA rsa(p, q);
    string message;
    cout << "Enter message: ";  
    cin >> message;

    rsa.encrypt(message);
    cout << "Encrypted message: " << rsa.get_encrypted_message() << endl;

    rsa.decrypt();
    cout << "Decrypted message: " << rsa.get_decrypted_message() << endl;

    cout << "Public key: " << rsa.get_public_key() << endl;
    cout << "Private key: " << rsa.get_private_key() << endl;

    return 0;
}
