#include <string>
#include <map>
#include <iostream>
#include <utility>
#include <cmath>
#include "fraction.h"
#include "complex.h"

using namespace std;

Complex::Complex(Frac r, Frac i): real{move(r)}, im{move(i)} {}


string Complex::pretty_print() {
  string im_tmp = im.pretty_print();
  string real_tmp = real.pretty_print();
  if (im_tmp == "(0)") {
    if (real_tmp != "(0)") return real_tmp;
    else return "0";
  }
 
  if (real_tmp == "(0)") real_tmp = "";
  else if (im_tmp == "(1)") return real_tmp + "+i";
  else if (im_tmp == "(-1)") return real_tmp + "-i";
  return real_tmp  + "+" +im_tmp + "i";
}

Complex Complex::conjugate() const {
  const Frac minus_one {{-1, {{}}}, {1, {{}}}};
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
