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

    bool all_negative = n.rational <= 0 && d.rational <= 0;

    for (auto p : n.irrational) {
        if (all_negative) { all_negative = p.second <= 0; }
        gcdd = gcd(gcdd, abs(p.second));
    }

    gcdd *= (all_negative ? -1 : 1);
    n.rational /= gcdd;
    d.rational /= gcdd;

    for (auto &p : n.irrational) p.second /= gcdd;
}


Frac::Frac(Sqrt n, Sqrt d) : numer{move(n)}, denom{move(d)} {
    if (d.rational == 0 && d.irrational.size() == 0)
        throw domain_error("denominator can't be zero");
    rationalize(numer, denom);
    simplify(numer, denom);
}

// precise specifies whether use approximate value => 1.414 = 1414/1000 or not (√2)
Frac::Frac(double d, bool precise): numer{Sqrt (0)}, denom{Sqrt (1)} {

    if (!precise || !d) {
        int tmp_numer = d * 10000;
        numer = Sqrt {tmp_numer};
        denom = Sqrt {10000};
        simplify(numer, denom);
        return;
    }

    int sign = abs(d) / d;
    d = abs(d);
    for (int i = 1; i <= 10; ++i) {
        try {
            numer = Sqrt {d * i};
            denom = Sqrt {sign * i};
            simplify(numer, denom);
            return;
        }
        catch (...) { // use Sqrt constructor to tell whether this guess of denom works
            if (i == 10) throw logic_error("Have tried to convert this double: " + to_string(d) + " with ten denominators but can't find one. Consider using non-precise conversion.");
        }
    }
}

string Frac::pretty_print() const {
    if (denom.rational == 1) return numer.pretty_print();
    return "(" + numer.pretty_print() + "/"
           + denom.pretty_print() + ")";
}


Frac Frac::operator+(const Frac &other) {
    return {numer * other.denom + denom * other.numer,
            denom * other.denom};
}


Frac Frac::operator-(const Frac &other) {
    return {numer * other.denom - denom * other.numer,
            denom * other.denom};
}


Frac Frac::operator*(const Frac &other) const {
    return {numer * other.numer, denom * other.denom};
}


Frac Frac::operator/(const Frac &other) {
    return {numer * other.denom, denom * other.numer};
}

bool Frac::operator==(const Frac &other) const {
    return numer == other.numer && denom == other.denom;
}

bool Frac::operator!=(const Frac &other) const {
    return !(*this == other);
}

double Frac::doublelize() const {
    return numer.doublelize() / denom.doublelize();
}