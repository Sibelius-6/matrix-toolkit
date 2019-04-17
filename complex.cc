#include <string>
#include <stdexcept>
#include <map>
#include <iostream>
#include <utility>
#include <cmath>
#include "fraction.h"
#include "complex.h"

using namespace std;

Complex::Complex(Frac r, Frac i) : real{move(r)}, im{move(i)} {}

// This creates the integers
Complex::Complex(int n) : real{(Frac) {{n, {}},
                                       {1, {}}}}, im{(Frac) {{0, {}},
                                                             {1, {}}}} {}

int Complex::placeHolder() const { return pretty_print().length(); }

string Complex::pretty_print() const {
    string im_tmp = im.pretty_print();
    string real_tmp = real.pretty_print();
    if (im_tmp == "(0)") {
        if (real_tmp != "(0)") return real_tmp;
        else return "0";
    }

    if (real_tmp == "(0)") real_tmp = "";
    else if (im_tmp == "(1)") return real_tmp + "+i";
    else if (im_tmp == "(-1)") return real_tmp + "-i";
    return real_tmp + "+" + im_tmp + "i";
}

string Complex::reformat(int n) const {
    if (n < placeHolder()) return "ERROR";
    int spaces = placeHolder() - n;
    int left_space = spaces / 2;
    int right_space = spaces - left_space;
    return string(left_space, ' ') + pretty_print() + string(right_space, ' ');
}

Complex Complex::conjugate() const {
    const Frac minus_one{{-1, {{}}},
                         {1,  {{}}}};
    return {real, im * minus_one};
}

Complex Complex::sqr_norm() const { return (*this) * conjugate(); }


Complex Complex::operator+(const Complex &other) {
    return {real + other.real, im + other.im};
}

Complex Complex::operator-(const Complex &other) {
    return {real - other.real, im - other.im};
}

Complex Complex::operator*(const Complex &other) const {
    return {real * other.real - im * other.im,
            real * other.im + im * other.real};
}

Complex Complex::operator/(const Complex &other) {
    Frac denom = other.sqr_norm().real;
    Complex tmp = (*this) * other.conjugate();
    return {tmp.real / denom, tmp.im / denom};
}

bool Complex::operator==(const Complex &other) const {
    return real == other.real && im == other.im;
}

bool Complex::operator!=(const Complex &other) const {
    return !(*this == other);
}

static Complex zero{{{0, {}}, {1, {}}},
                    {{0, {}}, {1, {}}}};
static Complex one{{{1, {}}, {1, {}}},
                   {{0, {}}, {1, {}}}};

Complex pow(const Complex &c, size_t n) {
    if (c == zero && n == 0)
        throw domain_error("can't have 0^0");
    if (n == 0) return one;

    Complex temp = pow(c, n / 2);

    if ((n % 2) == 0) return temp * temp;
    else return c * temp * temp;
}


// pow_(c, n) finds c^(-n)
Complex pow_(const Complex &c, size_t n) {
    return one / pow(c, n);
}

// note that I have restricted the numbers can be square rooted, they can't be
//	sqrt (√3), imaginary part not zero (1 + 2i)
//	thus the only number can be square rooted is  rational numbers
Complex sqrt(const Complex &c) {
    if (c.im != zero.im) throw domain_error("complex number can't be sqrt-ed");
    if (c.real.numer.irrational.size()) throw domain_error("sqrt can't be sqrt-ed");
    int numer_ = c.real.numer.rational;
    int denom_ = c.real.denom.rational;
    if (numer_ * denom_ >= 0)
        return {{{0, {{numer_, 1}}}, {0, {{denom_, 1}}}},
                {{0, {}},            {1, {}}}};
    else {
        numer_ = abs(numer_);
        denom_ = abs(denom_);
        return {{{0, {}},            {1, {}}},
                {{0, {{numer_, 1}}}, {0, {{denom_, 1}}}}};
    }
}
