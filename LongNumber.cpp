//
// Created by Daniel Chiliaev on 08/02/2024.
//

#include "LongNumber.h"


using namespace std;


LongNumber LongNumber::copy() {
    return LongNumber{decimal, fractional, sign};
}

LongNumber::LongNumber(string str) {
//    auto number = LongNumber{};
//
//    int64_t curr_chunk;
//    int chunk_pos = 0;
//
//    for (int i = 0; i < str.size(); ++i) {
//        if (str[i] == '.') {
//            // decimal separator
//        }
//        {
//
//        }
//
//    }

}

string LongNumber::to_string() {
//    return std::string();
}

LongNumber LongNumber::operator-() const {
    return LongNumber{decimal, fractional, sign == Sign::POSITIVE ? NEGATIVE : POSITIVE};
}

LongNumber::LongNumber(const vector<uint64_t> &decimal, const vector<uint64_t> &fractional, Sign sign)
        : decimal(decimal), fractional(fractional), sign(sign) {};

const int64_t MAX_NUM = ULONG_LONG_MAX;

LongNumber operator+(LongNumber a, LongNumber b) {
//    LongNumber c;
//
//    if (a.sign != b.sign) {
//        return a - (-b);
//    }
//    c.sign = a.sign;
//
//
//    uint64_t rest;

//    for (int i = 0; i < max<size_t>(a.decimal.size(), b.decimal.size()); ++i) {
//        int64_t ai = a.fractional[i], bi = b.fractional[i];
//        bool overflow;
//        if (rest) {
//            overflow = ai - (MAX_NUM - bi) - 1 >= 0;
//        } else {
//            overflow = ai - (MAX_NUM - bi) >= 0;
//        }
//        int64_t result;
//        if (overflow) {
//            rest = 1;
//            result = MAX_NUM - ((MAX_NUM - ai) + (MAX_NUM - bi));
//        } else {
//            rest = 0;
//            result = ai + bi;
//        }
//        c.fractional[i] = result;
//    }
//    if (rest) {
//        c.fractional.push_back(1);
//    }

//    for (int i = 0; i < max<size_t>(a.fractional.size(), b.fractional.size()); ++i) {
//        int64_t ai = a.decimal[i], bi = b.decimal[i];
//        bool overflow;
//        if (rest) {
//            overflow = ai - (MAX_NUM - bi) - 1 >= 0;
//        } else {
//            overflow = ai - (MAX_NUM - bi) >= 0;
//        }
//        int64_t result;
//        if (overflow) {
//            rest = 1;
//            result = MAX_NUM - ((MAX_NUM - ai) + (MAX_NUM - bi));
//        } else {
//            rest = 0;
//            result = ai + bi;
//        }
//        c.decimal[i] = result;
//    }
//    if (rest) {
//        c.decimal.push_back(1);
//    }
//    return c;
}

LongNumber operator-(LongNumber a, LongNumber b) {
    return {};
}

LongNumber operator*(LongNumber a, LongNumber b) {
    return {};
}

LongNumber operator/(LongNumber a, LongNumber b) {
    return {};
}

bool compare_sign_regardless(LongNumber a, LongNumber b) {
    if (a.decimal.size() > b.decimal.size()) {
        return true;
    } else if (a.decimal.size() < b.decimal.size()) {
        return false;
    }
    for (int i = a.decimal.size() - 1; i >= 0; --i) {
        int64_t chunk_a = a.decimal[i], chunk_b = b.decimal[i];
        if (a.decimal[i] != b.decimal[i]) {
            return chunk_a > chunk_b;
        }
    }
    size_t fraction_length_a = a.fractional.size(), fraction_length_b = b.fractional.size();
    for (int i = 0; i < min<size_t>(fraction_length_a, fraction_length_b); ++i) {
        int64_t chunk_a = a.fractional[i], chunk_b = b.fractional[i];
        if (chunk_a != chunk_b) {
            return chunk_a > chunk_b;
        }
    }
    return a.fractional.size() > b.fractional.size();
}

bool operator>(LongNumber a, LongNumber b) {
    if (a.sign != b.sign) {
        return a.sign == Sign::POSITIVE;
    } else if (a.sign == Sign::NEGATIVE && b.sign == Sign::NEGATIVE) {
        return compare_sign_regardless(b, a);
    }
    return compare_sign_regardless(a, b);

}

bool operator<(LongNumber a, LongNumber b) {
    return b > a;
}

bool operator==(LongNumber a, LongNumber b) {
    if (a.decimal.size() != b.decimal.size() || a.fractional.size() != b.fractional.size()) {
        return false;
    }
    for (int i = 0; i < a.decimal.size(); ++i) {
        if (a.decimal[i] != b.decimal[i]) {
            return false;
        }
    }
    for (int i = 0; i < a.fractional.size(); ++i) {
        if (a.fractional[i] != b.fractional[i]) {
            return false;
        }
    }
    return true;

}

bool operator!=(LongNumber& a, LongNumber b) {
    return !(a == b);
}

