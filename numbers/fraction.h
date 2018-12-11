#ifndef _FRACTION_H_
#define _FRACTION_H_

#include "sqrt.h"
#include <string>


class Frac {
public:
  Sqrt numer, denom;
  Frac(Sqrt n, Sqrt d);
  

  std::string pretty_print();

  Frac operator+(const Frac &other);
  Frac operator-(const Frac &other);
  Frac operator*(const Frac &other) const;
  Frac operator/(const Frac &other);
};

#endif

