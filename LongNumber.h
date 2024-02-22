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
    vector<uint32_t> decimal; // stored from lower to higher. Normalised. Ex: 121123 <-
    vector<uint32_t> fractional; // stored from higher to lower. Normalised. Ex: 0.19123 ->

    Sign sign;
public:
    explicit LongNumber(const string str);


    LongNumber(const vector<uint32_t> &decimal, const vector<uint32_t> &fractional, Sign sign);

    LongNumber(const LongNumber &num);

    explicit LongNumber(const int32_t &num);


    LongNumber() {
        decimal = {0};
        fractional = {0};
        sign = Sign::POSITIVE;
    }


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


    friend bool operator>(const LongNumber &a, const LongNumber &b);

    friend bool operator<(const LongNumber &a, const LongNumber &b);

    friend bool operator==(const LongNumber &a, const LongNumber &b);

    friend bool operator!=(const LongNumber &a, const LongNumber &b);

    friend bool compare_sign_regardless(const LongNumber &a, const LongNumber &b);

    LongNumber shift_chunks(int chunks) const;

    void normalise();
};

LongNumber operator+(const LongNumber &a, const LongNumber &b);

LongNumber operator-(const LongNumber &a, const LongNumber &b);

LongNumber operator*(const LongNumber &a, const LongNumber &b);

LongNumber operator/(const LongNumber &a, const LongNumber &b);

bool operator>(const LongNumber &a, const LongNumber &b);

bool operator<(const LongNumber &a, const LongNumber &b);

bool operator==(const LongNumber &a, const LongNumber &b);

bool operator!=(const LongNumber &a, const LongNumber &b);

bool compare_sign_regardless(const LongNumber &a, const LongNumber &b);


struct OperationResult {
    uint32_t overflow;
    uint32_t remainder;
};

OperationResult sum(uint32_t a, uint32_t b);

OperationResult subtract(uint32_t a, uint32_t b);

OperationResult subtract(uint32_t a, uint32_t b, uint32_t overflow);

OperationResult multiply(uint32_t a, uint32_t b);

#endif //LONGNUM_LONGNUMBER_H

