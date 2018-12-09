#include <string>
#include <map>
#include <iostream>
#include <utility>
#include <cmath>
#include <cassert>
#include <stdexcept>
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


static int gcd(int a, int b) {
  if (a == 0) return b;
  return gcd(b % a, a);
}

// divide the gcd of the numer and denom
static void simplify(Sqrt &n, Sqrt &d) {
  assert((d.irrational.size() == 0) && "denom has sqrt");
  if (d.rational == 1) return;
  if (d.rational == -1) {
    d.rational = 1;
    Sqrt zero = {0, {}};
    n = zero - n;
    return;
  }
  int gcdd = gcd(abs(n.rational), abs(d.rational));
  if (gcdd == 1) return;

  for (auto p : n.irrational) gcdd = gcd(gcdd, abs(p.second));

  n.rational /= gcdd; 
  d.rational /= gcdd;

  for (auto &p : n.irrational) p.second /= gcdd;
}


Frac::Frac(Sqrt n, Sqrt d) : numer{n}, denom{d} {
  if (d.rational == 0 && d.irrational.size() == 0)
    throw domain_error("denominator can't be zero");
  rationalize(numer, denom);
  simplify(numer, denom);
}

string Frac::pretty_print() {
  if (denom.rational == 1) return numer.pretty_print();
  return "(" + numer.pretty_print() + "/"
              + denom.pretty_print() + ")";
}

