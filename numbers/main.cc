#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <cmath>
#include "fraction.h"
#include "sqrt.h"
using namespace std;

int main() {
  map<radicand, multiple> i {
    {2, 3}, {3, 1}
  };
  map<radicand, multiple> j {
    {5, 1}, {6, -1}
  };
  Sqrt a {2, i};
  cout << "a is " << a.pretty_print() << endl;
  Sqrt b {-1, j};
  cout << "b is " << b.pretty_print() << endl;
  Sqrt c = a - b;
  cout << "a-b is " << c.pretty_print() << endl;
  Sqrt d = a * b;
  cout << "a*b is " << d.pretty_print() << endl;
  Frac e = a / b;
  cout << "a/b is " << e.pretty_print() << endl;
}
