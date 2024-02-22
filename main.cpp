#include <iostream>
#include "LongNumber.h"

int main() {
    auto
            a = LongNumber({1,1}, {}, Sign::POSITIVE),
            b = LongNumber({1,1}, {}, Sign::POSITIVE);
    auto result = a * b;

    return 0;
}

// https://yandex.ru
// 321.456 -> -2 3.21456
// 321.456 -> -5 0.00321456

// 321.456 -> +2 32145.
// 321.456 -> +4 3214560.0

