#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include "fraction.h"
#include <string>
#include <complex>

class Complex {
public:
    Frac real, im;

    Complex(Frac r, Frac i);

    Complex(int n = 0);

    std::string pretty_print() const;

    std::string reformat(int n) const;

    int placeHolder() const;

    Complex conjugate() const;

    Complex sqr_norm() const;

    Complex operator+(const Complex &other);

    Complex operator-(const Complex &other);

    Complex operator*(const Complex &other) const;

    Complex operator/(const Complex &other);

    bool operator==(const Complex &other) const;

    bool operator!=(const Complex &other) const;

    std::complex<double> doublelize() const;
};

Complex complex_double_to_Complex(std::complex<double> c);

Complex pow(const Complex &c, size_t n);

Complex pow_(const Complex &c, size_t n);

Complex sqrt(const Complex &c);

std::ostream &operator<<(std::ostream &out, const Complex &c);

#endif

