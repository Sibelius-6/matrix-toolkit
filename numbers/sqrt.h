#ifndef _SQRT_H_
#define _SQRT_H_

#include <string>
#include <map>

class Frac;

typedef size_t radicand;
typedef int multiple;

class Sqrt {
public:
  int rational;
  std::map<radicand, multiple> irrational;
  // = rational + multiple * √radicand

  Sqrt(int rational_, std::map<radicand, multiple> irrational_);
  Sqrt(const Sqrt &other);
  Sqrt(const Sqrt &&other);
  Sqrt &operator=(Sqrt other);

  std::string pretty_print();

  Sqrt operator+(const Sqrt &other);
  Sqrt operator-(const Sqrt &other);
  Sqrt operator*(const Sqrt &other) const;
  Frac operator/(const Sqrt &other);

  bool operator==(const Sqrt &other) const;
  bool operator!=(const Sqrt &other) const;
};

#endif

