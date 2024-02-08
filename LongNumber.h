//
// Created by Daniel Chiliaev on 08/02/2024.
//

#include "string"

using namespace std;

#ifndef LONGNUM_LONGNUMBER_H
#define LONGNUM_LONGNUMBER_H

class LongNumber {
public:
    vector<long long> number;
    int length;
    int exponent;

    LongNumber() {
        number = {0};
        length = 0;
        exponent = 0;
    }

    explicit LongNumber(string str);

    string to_string();
};

LongNumber operator+(LongNumber a, LongNumber b);

LongNumber operator-(LongNumber a, LongNumber b);

LongNumber operator*(LongNumber a, LongNumber b);

LongNumber operator/(LongNumber a, LongNumber b);

LongNumber operator>(LongNumber a, LongNumber b);

LongNumber operator<(LongNumber a, LongNumber b);

LongNumber operator==(LongNumber a, LongNumber b);

LongNumber operator!=(LongNumber a, LongNumber b);


#endif //LONGNUM_LONGNUMBER_H
