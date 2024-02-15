#include <iostream>
#include "LongNumber.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto
            a = LongNumber({1, 2, 3, 5}, {1, 1}, Sign::POSITIVE),
            b = LongNumber({1, 2, 3, 5}, {0, 1}, Sign::POSITIVE);
    bool greater = a > b;
    return 0;
    }
