#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <cmath>
using namespace std;

typedef size_t radicand;
typedef int multiple;


class Sqrt;

class Frac {
public:
  Sqrt numer, denom;
  Frac(Sqrt n, Sqrt d) : numer{n}, denom{d} {
    rationalize(numer, denom);
  }

  string pretty_print() {
    return "(" + numer.pretty_print() + "/"
                + denom.pretty_print() + ")";
  }
};



// √12 ->2√3, √7 => 3, 1
// √9 => 0
int simplify(int p) {
  int n = sqrt(p);
//  cout << "n is " << n << endl;
  if (n * n == p) return 0;
  for (int i = n; i > 0; --i) {
    if (p % (i * i) == 0) return i;
  }
  return -1; // should never be reached
}

void map_add(map<radicand, multiple> &i, size_t r, int m) {
  if (i.count(r)) i.at(r) += m;
  else i.insert(pair<radicand, multiple>(r, m));
}

void standardize(int &rational, map<radicand, multiple> &irrational) {
  for (auto &p : irrational) {
    int tmp = simplify(p.first);
    if (tmp == 0) {
      rational += sqrt(p.first) * p.second;
      p.second = 0;
    } else if (tmp > 1) {
      map_add(irrational, p.first/(tmp*tmp), tmp*p.second);
      p.second = 0;
    }
  }

  for (auto it = irrational.begin(); it != irrational.end(); )
     if(it->second == 0) it = irrational.erase(it);
     else ++it;
}


class Sqrt {
public:
  int rational;
  map<radicand, multiple> irrational;
  // = rational + multiple * √radicand

  Sqrt(int rational_, map<radicand, multiple> irrational_):
    rational{rational_}, irrational{irrational_} {
      standardize(rational, irrational);
      // remove the zero multiple
      // √18 ->3√3
    }
// simplify the expression in the ctor

  Sqrt(const Sqrt &other) {
    rational = other.rational;
    irrational = other.irrational;
    standardize(rational, irrational);
  }

  Sqrt &operator=(Sqrt other) {
    swap(rational, other.rational);
    swap(irrational, other.irrational);
    standardize(rational, irrational);
    return *this;
  }

  
  
  string pretty_print() {
    string rat = (rational? to_string(rational) : "");
    string irr = "";
    for (const auto &p : irrational) {
      string radi = "√(" + to_string(p.first) + ")";
      if (p.second > 0) {
        irr += "+" + (p.second == 1? "" : to_string(p.second)) + radi;
      } else if (p.second < 0) {
        irr += (p.second == -1? "-" : to_string(p.second)) + radi;
      }
    }
    return "(" + rat + irr + ")";
  } // √ = options + v

  Sqrt operator+(const Sqrt &other) {
    map<radicand, multiple> res_i = irrational;
    for (const auto &p : other.irrational) {
      map_add(res_i, p.first, p.second);
    }
    return { rational + other.rational, res_i };
  }

  Sqrt operator-(const Sqrt &other) {
    map<radicand, multiple> res_i = irrational;
    for (const auto &p : other.irrational) {
      map_add(res_i, p.first, -p.second);
    }
    return { rational - other.rational, res_i };
  }

  Sqrt operator*(const Sqrt &other) {
    int res_r = rational * other.rational;
    map<radicand, multiple> res_i {};
    for (const auto &p : other.irrational) {
      for (const auto &q : irrational) {
        map_add(res_i, p.first*q.first,  p.second*q.second);
      }
    }
    for (const auto &p: irrational)
      map_add(res_i, p.first, p.second*other.rational);

    for (const auto &p: other.irrational)
      map_add(res_i, p.first, p.second*rational);

    return { res_r, res_i };
  }
  
  Frac operator/(const Sqrt &other) { return {*this, other}; }
};



void rationalize(Sqrt &n, Sqrt &d) {
  if (d.irrational.size() == 0) return;
  Sqrt tmp = d;
  (tmp.irrational.begin())->second *= -1;
  n = n * tmp;
  d = d * tmp;
  rationalize(n, d);
}

/*
class Frac {
public:
  Sqrt numer, denom;
  Frac(Sqrt n, Sqrt d) : numer{n}, denom{d} {
    rationalize(numer, denom);
  }

  string pretty_print() {
    return "(" + numer.pretty_print() + "/" 
                + denom.pretty_print() + ")";
  }
};
*/

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
  cout << "a/b is " << endl;
}

