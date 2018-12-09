#include <string>
#include <map>
#include <iostream>
#include <utility>
#include <cmath>
#include "sqrt.h"
#include "fraction.h"

using namespace std;

static void rationalize(Sqrt &n, Sqrt &d) {
  if (d.irrational.size() == 0) return;
  Sqrt tmp = d;
  (tmp.irrational.begin())->second *= -1;
  n = n * tmp;
  d = d * tmp;
  rationalize(n, d);
}

Frac::Frac(Sqrt n, Sqrt d) : numer{n}, denom{d} {
  rationalize(numer, denom);
}

string Frac::pretty_print() {
  return "(" + numer.pretty_print() + "/"
              + denom.pretty_print() + ")";
}

