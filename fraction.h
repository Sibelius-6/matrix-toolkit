#ifndef _FRACTION_H_
#define _FRACTION_H_

#include "sqrt.h"
#include <string>


class Frac {
public:
    Sqrt numer, denom;

    Frac(Sqrt n, Sqrt d);

    Frac(double d, bool precise = true);

    std::string pretty_print() const;

    Frac operator+(const Frac &other) const;

    Frac operator-(const Frac &other) const;

    Frac operator*(const Frac &other) const;

    Frac operator/(const Frac &other) const;

    bool operator==(const Frac &other) const;

    bool operator!=(const Frac &other) const;

    double doublelize() const;
};

#endif

