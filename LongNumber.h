//
// Created by Daniel Chiliaev on 08/02/2024.
//

#include "string"

using namespace std;

#ifndef LONGNUM_LONGNUMBER_H
#define LONGNUM_LONGNUMBER_H

enum Sign {
    POSITIVE, NEGATIVE
};

class LongNumber {
public:
    vector<uint64_t> decimal; //stored from lower to higher
    vector<uint64_t> fractional; // stored from higher to lower

    Sign sign;

    LongNumber(const vector<uint64_t> &decimal, const vector<uint64_t> &fractional, Sign sign);

    LongNumber() {
        decimal = {0};
        fractional = {0};
        sign = Sign::POSITIVE;
    }


    LongNumber(string str);
    string to_string();

    LongNumber copy();


    LongNumber operator-() const;
};

LongNumber operator+(LongNumber a, LongNumber b);

LongNumber operator-(LongNumber a, LongNumber b);

LongNumber operator*(LongNumber a, LongNumber b);

LongNumber operator/(LongNumber a, LongNumber b);

bool operator>(LongNumber a, LongNumber b);

bool operator<(LongNumber a, LongNumber b);

bool operator==(LongNumber a, LongNumber b);

bool operator!=(LongNumber a, LongNumber b);


#endif //LONGNUM_LONGNUMBER_H
