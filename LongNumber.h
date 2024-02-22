//
// Created by Daniel Chiliaev on 08/02/2024.
//

#include "string"

using namespace std;

#ifndef LONGNUM_LONGNUMBER_H
#define LONGNUM_LONGNUMBER_H

const uint32_t MAX_NUM = numeric_limits<uint32_t>::max();


enum Sign {
    POSITIVE, NEGATIVE
};

class LongNumber {
private:
    vector<uint32_t> decimal; // stored from lower to higher. Ex: 121123 <-
    vector<uint32_t> fractional; // stored from higher to lower. Ex: 0.19123 ->

    Sign sign;
public:
    LongNumber(const vector<uint32_t> &decimal, const vector<uint32_t> &fractional, Sign sign);

    LongNumber(const LongNumber &num);

    LongNumber(const int32_t &num);


    LongNumber() {
        decimal = {0};
        fractional = {0};
        sign = Sign::POSITIVE;
    }

    explicit LongNumber(string &str);


    string to_string();


    LongNumber operator-() const;

    LongNumber operator+=(const LongNumber &b);

    LongNumber operator-=(const LongNumber &b);

    LongNumber operator*=(const LongNumber &b);

    LongNumber operator/=(const LongNumber &b);


    friend LongNumber operator+(const LongNumber &a, const LongNumber &b);

    friend LongNumber operator-(const LongNumber &a, const LongNumber &b);

    friend LongNumber operator*(const LongNumber &a, const LongNumber &b);

    friend LongNumber operator/(const LongNumber &a, const LongNumber &b);


    friend bool operator>(LongNumber &a, LongNumber &b);

    friend bool operator<(LongNumber &a, LongNumber &b);

    friend bool operator==(LongNumber &a, LongNumber &b);

    friend bool operator!=(LongNumber &a, LongNumber &b);

    friend bool compare_sign_regardless(LongNumber &a, LongNumber &b);

    LongNumber shift_chunks(int chunks) const;

    void normalise();
};

LongNumber operator+(const LongNumber &a, const LongNumber &b);

LongNumber operator-(const LongNumber &a, const LongNumber &b);

LongNumber operator*(const LongNumber &a, const LongNumber &b);

LongNumber operator/(const LongNumber &a, const LongNumber &b);

bool operator>(LongNumber &a, LongNumber &b);

bool operator<(LongNumber &a, LongNumber &b);

bool operator==(LongNumber &a, LongNumber &b);

bool operator!=(LongNumber &a, LongNumber &b);

bool compare_sign_regardless(LongNumber &a, LongNumber &b);


struct OperationResult {
    uint32_t overflow;
    uint32_t remainder;
};

OperationResult sum(uint32_t a, uint32_t b);

OperationResult multiply(uint32_t a, uint32_t b);

#endif //LONGNUM_LONGNUMBER_H

