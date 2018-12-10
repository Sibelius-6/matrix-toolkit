#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <cmath>
#include "fraction.h"
#include "sqrt.h"
using namespace std;

int main() {
  Sqrt a {2, {{3, 1}}};
  cout << "a is " << a.pretty_print() << endl;
  Sqrt b {3, {{3, -1}}};
  cout << "b is " << b.pretty_print() << endl;
  Sqrt c = a - b;
  cout << "a-b is " << c.pretty_print() << endl;
  Sqrt d = a * b;
  cout << "a*b is " << d.pretty_print() << endl;
  Frac e = a / b;
  cout << "a/b is " << e.pretty_print() << endl;
  Frac f = a / c;
  cout << "a/c is " << f.pretty_print() << endl;

  cout << endl << "Now fractions operation..." << endl << endl;

  cout << "e+f is " << (e+f).pretty_print() << endl;
  cout << "e-f is " << (e-f).pretty_print() << endl;
  cout << "e*f is " << (e*f).pretty_print() << endl;
  cout << "e/f is " << (e/f).pretty_print() << endl;
}
