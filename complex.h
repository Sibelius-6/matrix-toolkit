#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include "./numbers/fraction.h"
#include <string>

class Complex {
public:
  Frac real, im;

  Complex(Frac r, Frac i);
  Complex(int n);

  std::string pretty_print();
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

