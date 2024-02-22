//
// Created by Daniel Chiliaev on 08/02/2024.
//

#include <list>
#include <sstream>
#include "LongNumber.h"


using namespace std;


inline bool check_overflow_addition(uint32_t a, uint32_t b) {
    return a <= MAX_NUM - b;
}

inline bool check_overflow_multiplication(uint32_t a, uint32_t b) {
    return a <= MAX_NUM / b;
}


OperationResult sum(uint32_t a, uint32_t b) {
    uint64_t res = (uint64_t) a + b;

    return {
            (uint32_t) ((res / (1ULL << 32))),
            (uint32_t) ((res % (1ULL << 32)))
    };
}

OperationResult multiply(uint32_t a, uint32_t b) {
    uint64_t res = (uint64_t) a * b;
    return {
            (uint32_t) ((res / (1ULL << 32))),
            (uint32_t) ((res % (1ULL << 32)))
    };

}

LongNumber LongNumber::shift_chunks(int chunks) const {
    if (!chunks) {
        return {*this};
    }
    LongNumber res{*this};
    if (chunks < 0) {
        if (chunks < -fractional.size()) {
            res.fractional.insert(res.fractional.begin(), decimal.rbegin(), decimal.rend());
            res.fractional.insert(res.fractional.begin(), -fractional.size() - chunks, 0);
            res.decimal.erase(res.decimal.begin(), res.decimal.end());
        } else {
            res.fractional.insert(res.fractional.begin(), decimal.rend() + chunks, decimal.rend());
            res.decimal.erase(res.decimal.begin(), res.decimal.begin() - chunks);
        }
    } else {
        if (chunks > fractional.size()) {
            res.decimal.insert(res.decimal.begin(), fractional.rbegin(), fractional.rend());
            res.decimal.insert(res.decimal.begin(), chunks - decimal.size(), 0);
            res.fractional.erase(res.fractional.begin(), res.fractional.end());
        } else {
            res.decimal.insert(res.decimal.begin(), fractional.rend() - chunks, fractional.rend());
            res.fractional.erase(res.fractional.begin(), res.fractional.begin() + chunks);
        }
    }
    return res;

}

struct ParsedNumString {
    Sign sign;
    string decimal_string;
    string fractional_string;
};

ParsedNumString parse_string_num(const string &str) {
    if (str.empty()) {
        return {POSITIVE, "", ""};
    }
    string new_str;

    ParsedNumString result{};

    if (str[0] == '+' || str[0] == '-') {
        result.sign = str[0] == '+' ? Sign::POSITIVE : Sign::NEGATIVE;
        new_str = str.substr(1);
    } else {
        result.sign = Sign::POSITIVE;
        new_str = str;
    }

    stringstream stream(new_str);
    getline(stream, result.decimal_string, '.');
    getline(stream, result.fractional_string);
    return result;
}


LongNumber::LongNumber(string &str) : decimal({}), fractional({}), sign(Sign::POSITIVE) {
    if (str.empty()) {
        return;
    }
    auto result = parse_string_num(str);
    sign = result.sign;

    uint32_t curr_power = 1;
    uint32_t chunk = 0;

    for (int i = result.fractional_string.size() - 1; i >= 0; --i) {
        int digit = result.fractional_string[i] - '0';
        if (!check_overflow_multiplication(i, curr_power)) {
            // TODO overflow case
        }
        uint32_t summand = digit * curr_power;
        if (!check_overflow_addition(chunk, summand)) {
            // TODO overflow case
        }
        chunk += digit * curr_power;
        if (!check_overflow_multiplication(curr_power, 10)) {
            // TODO overflow case
        }
        curr_power *= 10;

    }
}

string LongNumber::to_string() {
    list<char> reversed_string;
    for (long long chunk: decimal) {
        while (chunk) {
            int digit = chunk % 10;
            reversed_string.push_back(digit + '0');
            chunk /= 10;
        }
    }
    reversed_string.reverse();
    return {reversed_string.begin(), reversed_string.end()};
}

LongNumber LongNumber::operator-() const {
    return LongNumber{decimal, fractional, sign == Sign::POSITIVE ? Sign::NEGATIVE : Sign::POSITIVE};
}

LongNumber::LongNumber(const vector<uint32_t> &decimal, const vector<uint32_t> &fractional, Sign sign)
        : decimal(decimal), fractional(fractional), sign(sign) {};

LongNumber::LongNumber(const LongNumber &num) {
    sign = num.sign;
    decimal = num.decimal;
    fractional = num.fractional;
}

LongNumber::LongNumber(const int32_t &num) {
    sign = num >= 0 ? Sign::POSITIVE : Sign::NEGATIVE;
    decimal = {(uint32_t) abs(num)};
}


LongNumber operator+(const LongNumber &a, const LongNumber &b) {
    LongNumber c;

    c.fractional.resize(max<size_t>(a.fractional.size(), b.fractional.size()));
    c.decimal.resize(max<size_t>(a.decimal.size(), b.decimal.size()));

    if (a.fractional.size() > b.fractional.size()) {
        for (int i = a.fractional.size() - 1; i >= 0; --i) {

            c.fractional[i] = a.fractional[i];
        }
    } else if (a.fractional.size() < b.fractional.size()) {
        for (int i = b.fractional.size() - 1; i >= 0; --i) {
            c.fractional[i] = b.fractional[i];
        }
    }

    uint32_t overflow = 0;

    for (int i = min<size_t>(a.fractional.size(), b.fractional.size()) - 1; i >= 0; --i) {
        uint32_t ai = a.fractional[i], bi = b.fractional[i];
        auto result = sum(ai, bi);
        auto _overflow = result.overflow;
        result = sum(result.remainder, overflow);
        overflow = _overflow + result.overflow;

        c.fractional[i] = result.remainder;
    }

    for (int i = 0; i < max<size_t>(a.decimal.size(), b.decimal.size()); ++i) {
        if (i >= a.decimal.size()) {
            c.decimal[i] = b.decimal[i] + overflow;
            overflow = 0;
        } else if (i >= b.decimal.size()) {
            c.decimal[i] = a.decimal[i] + overflow;
            overflow = 0;
        } else {
            uint32_t ai = a.decimal[i], bi = b.decimal[i];
            auto result = sum(ai, bi);
            auto _overflow = result.overflow;
            result = sum(result.remainder, overflow);
            overflow = _overflow + result.overflow;

            c.decimal[i] = result.remainder;
        }
    }
    if (overflow) {
        c.decimal.push_back(overflow);
    }
    c.normalise();
    return c;
}

LongNumber operator-(const LongNumber &a, const LongNumber &b) {
    return {};
}

LongNumber operator*(const LongNumber &a, const LongNumber &b) {
    LongNumber c;
    c.fractional.resize(a.fractional.size() * b.fractional.size());
    c.decimal.resize(a.decimal.size() * b.decimal.size());
    int n = max<size_t>(a.decimal.size(), b.decimal.size());
    auto a_copy = a.shift_chunks(a.fractional.size()), b_copy = b.shift_chunks(b.fractional.size());
    a_copy.decimal.resize(n);
    b_copy.decimal.resize(n);
    c.decimal.resize(2 * n + 1, 0);

    c = c.shift_chunks(-a.fractional.size() * b.fractional.size());
    for (int i = 0; i <= 2 * n - 1; ++i) {
        LongNumber coeff(0);
        for (int j = 0; j <= i; ++j) {
            auto res = multiply(a.decimal[j], b.decimal[i - j]);
            coeff += LongNumber({res.remainder, res.overflow}, {}, Sign::POSITIVE);

        }
        uint32_t overflow = 0;

        for (int j = 0; j < coeff.decimal.size(); ++j) {
            auto res = sum(c.decimal[i + j], coeff.decimal[j]);
            auto _overflow = res.overflow;
            res = sum(res.remainder, overflow);
            c.decimal[i + j] = res.remainder;
            overflow = _overflow + res.overflow;
        }

    }
    c.normalise();
    c = c.shift_chunks(-a.fractional.size() * b.fractional.size());

    return c;
}

LongNumber operator/(const LongNumber &a, const LongNumber &b) {
    return {0};
}

bool compare_sign_regardless(LongNumber &a, LongNumber &b) {
    if (a.decimal.size() > b.decimal.size()) {
        return true;
    } else if (a.decimal.size() < b.decimal.size()) {
        return false;
    }
    for (int i = a.decimal.size() - 1; i >= 0; --i) {
        int32_t chunk_a = a.decimal[i], chunk_b = b.decimal[i];
        if (a.decimal[i] != b.decimal[i]) {
            return chunk_a > chunk_b;
        }
    }
    size_t fraction_length_a = a.fractional.size(), fraction_length_b = b.fractional.size();
    for (int i = 0; i < min<size_t>(fraction_length_a, fraction_length_b); ++i) {
        int32_t chunk_a = a.fractional[i], chunk_b = b.fractional[i];
        if (chunk_a != chunk_b) {
            return chunk_a > chunk_b;
        }
    }
    return a.fractional.size() > b.fractional.size();
}

bool operator>(LongNumber &a, LongNumber &b) {
    if (a.sign != b.sign) {
        return a.sign == Sign::POSITIVE;
    } else if (a.sign == Sign::NEGATIVE && b.sign == Sign::NEGATIVE) {
        return compare_sign_regardless(b, a);
    }
    return compare_sign_regardless(a, b);

}

bool operator<(LongNumber &a, LongNumber &b) {
    return b > a;
}

bool operator==(LongNumber &a, LongNumber &b) {
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

bool operator!=(LongNumber &a, LongNumber &b) {
    return !(a == b);
}

void LongNumber::normalise() {
    vector<uint32_t> new_decimal{}, new_fractional{};
    bool decimal_normalised = false, fractional_normalised = false;
    for (int i = decimal.size() - 1; i >= 0; --i) {
        if (decimal_normalised) {
            new_decimal.insert(new_decimal.begin(), decimal[i]);
        } else {
            if (decimal[i] != 0) {
                new_decimal.insert(new_decimal.begin(), decimal[i]);
                decimal_normalised = true;
            }
        }
    }
    for (int i = fractional.size() - 1; i >= 0; --i) {
        if (fractional_normalised) {
            new_fractional.insert(new_fractional.begin(), fractional[i]);
        } else {
            if (fractional[i] != 0) {
                new_fractional.insert(new_fractional.begin(), fractional[i]);
                fractional_normalised = true;
            }
        }
    }
    if (new_decimal.empty()) {
        new_decimal = {0};
    }
    decimal = new_decimal;
    fractional = new_fractional;

}

LongNumber LongNumber::operator+=(const LongNumber &b) {
    *this = *this + b;
    return *this;
}

LongNumber LongNumber::operator-=(const LongNumber &b) {
    return *this - b;
}

LongNumber LongNumber::operator*=(const LongNumber &b) {
    return *this * b;
}

LongNumber LongNumber::operator/=(const LongNumber &b) {
    return *this / b;
}
