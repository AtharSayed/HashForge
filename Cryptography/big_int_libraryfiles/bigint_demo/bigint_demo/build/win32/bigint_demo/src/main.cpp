#include <iostream>
#include <mpir.h>
#include "bigint.h"

using std::cout;
using std::endl;

int main()
{
    unsigned int len;
    char* str = nullptr;
    iamtcs::BigInt bigint("10910910", 8, 10);
    bigint.toStr(str, len, 10);
    cout << "hello world!: " << str << endl;
    return 0;
}