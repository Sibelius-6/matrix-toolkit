#include <string>
#include <map>
#include <iostream>
#include <utility>
#include <cmath>
#include <stdexcept>
#include "sqrt.h"
#include "fraction.h"

using namespace std;

typedef size_t radicand;
typedef int multiple;

// helpers

// returns the biggest factor of p which is perfect square
static int simplify(int p) {
    int n = sqrt(p);
    if (n * n == p) return 0;
    for (int i = n; i > 0; --i) {
        if (p % (i * i) == 0) return i;
    }
    return -1; // should never be reached
}


static void map_add(map <radicand, multiple> &i, size_t r, int m) {
    if (i.count(r)) i.at(r) += m;
    else i.insert(pair<radicand, multiple>(r, m));
}


/* simplify the expression:
    - simplify the radicand
    - remove the 0 multiple
*/
void standardize(int &rational, map <radicand, multiple> &irrational) {
    for (auto &p : irrational) {
        int tmp = simplify(p.first);
        if (tmp == 0) {
            rational += sqrt(p.first) * p.second;
            p.second = 0;
        } else if (tmp > 1) {
            map_add(irrational, p.first / (tmp * tmp), tmp * p.second);
            p.second = 0;
        }
    }

    for (auto it = irrational.begin(); it != irrational.end();)
        if (it->second == 0) it = irrational.erase(it);
        else ++it;
}

Sqrt::Sqrt(int rational_, map <radicand, multiple> irrational_) :
        rational{rational_}, irrational{irrational_} {
    standardize(rational, irrational);
}

Sqrt::Sqrt(const Sqrt &other) :
        rational{other.rational}, irrational{other.irrational} {
    standardize(rational, irrational);
}

Sqrt::Sqrt(const Sqrt &&other) :
        rational{move(other.rational)}, irrational{move(other.irrational)} {
    standardize(rational, irrational);
}

Sqrt &Sqrt::operator=(Sqrt other) {
    swap(rational, other.rational);
    swap(irrational, other.irrational);
    standardize(rational, irrational);
    return *this;
}

string Sqrt::pretty_print() {
    if (rational == 0 && irrational.size() == 0) return "(0)";
    string rat = (rational ? to_string(rational) : "");
    string irr = "";
    for (const auto &p : irrational) {
        string radi = "√(" + to_string(p.first) + ")";
        if (p.second > 0) {
            irr += "+" + (p.second == 1 ? "" : to_string(p.second)) + radi;
        } else if (p.second < 0) {
            irr += (p.second == -1 ? "-" : to_string(p.second)) + radi;
        }
    }
    return "(" + rat + irr + ")";
}

Sqrt Sqrt::operator+(const Sqrt &other) {
    map <radicand, multiple> res_i = irrational;
    for (const auto &p : other.irrational) {
        map_add(res_i, p.first, p.second);
    }
    return {rational + other.rational, res_i};
}

Sqrt Sqrt::operator-(const Sqrt &other) {
    map <radicand, multiple> res_i = irrational;
    for (const auto &p : other.irrational) {
        map_add(res_i, p.first, -p.second);
    }
    return {rational - other.rational, res_i};
}

Sqrt Sqrt::operator*(const Sqrt &other) const {
    int res_r = rational * other.rational;
    map <radicand, multiple> res_i{};
    for (const auto &p : other.irrational) {
        for (const auto &q : irrational) {
            map_add(res_i, p.first * q.first, p.second * q.second);
        }
    }
    for (const auto &p: irrational)
        map_add(res_i, p.first, p.second * other.rational);

    for (const auto &p: other.irrational)
        map_add(res_i, p.first, p.second * rational);

    return {res_r, res_i};
}

Frac Sqrt::operator/(const Sqrt &other) {
    try {
        return {*this, other};
    }
    catch (domain_error &r) {
        cerr << r.what() << endl;
        throw;
    }
    return {{1, {}},
            {1, {}}}; // should never be reached
}

bool Sqrt::operator==(const Sqrt &other) const {
    return rational == other.rational && irrational == other.irrational;
}

bool Sqrt::operator!=(const Sqrt &other) const {
    return !(*this == other);
}
