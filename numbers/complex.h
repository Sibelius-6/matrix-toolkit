#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include "fraction.h"
#include <string>

class Complex {
public:
  Frac real, im;

  Complex(Frac r, Frac i);

  std::string pretty_print();

  Complex conjugate() const;
  Complex sqr_norm() const;  

  Complex operator+(const Complex &other);
  Complex operator-(const Complex &other);
  Complex operator*(const Complex &other) const;
  Complex operator/(const Complex &other);
  
};

Complex power(const Complex &c, size_t n);

#endif

