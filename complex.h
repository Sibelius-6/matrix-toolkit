#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include "fraction.h"
#include <string>

class Complex {
public:
    Frac real, im;

    Complex(Frac r, Frac i);

    Complex(int n = 0);

    std::string pretty_print() const;

    int placeHolder();

    Complex conjugate() const;

    Complex sqr_norm() const;

    Complex operator+(const Complex &other);

    Complex operator-(const Complex &other);

    Complex operator*(const Complex &other) const;

    Complex operator/(const Complex &other);

    bool operator==(const Complex &other) const;

    bool operator!=(const Complex &other) const;
};

Complex pow(const Complex &c, size_t n);

Complex pow_(const Complex &c, size_t n);

Complex sqrt(const Complex &c);

#endif

