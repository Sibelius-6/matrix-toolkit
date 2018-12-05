#include <string>
#include <iostream>
#include <map>
using namespace std;

typedef size_t radicand;
typedef int multiple;

class Sqrt {
public:
  int rational;
  map<radicand, multiple> irrational;
  // = rational + multiple * √radicand

  Sqrt(int rational, map<radicand, multiple> irrational):
    rational{rational}, irrational{irrational} {}
// simplify the expression in the ctor
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
    return rat + irr;
  } // √ = options + v

  Sqrt operator+(const Sqrt &other) {
    map<radicand, multiple> res_i = irrational;
    for (const auto &p : other.irrational) {
      if (res_i.count(p.first)) res_i.at(p.first) += p.second;
      else res_i.insert(pair<radicand, multiple>(p.first, p.second));
    }
    return { rational + other.rational, res_i };
  }
};

int main() {
  map<radicand, multiple> i {
    {2, 3}, {10, 1}, {8, -1}, {3, 102}, {23, 0}, {29, -102}
  };
  map<radicand, multiple> j {
    {2, 3}, {10, -1}, {8, -10}, {7, 102}, {23, 0}, {22, -102}
  };
  Sqrt a {-10, i};
  cout << "a is " << a.pretty_print() << endl;
  Sqrt b {0, j};
  cout << "b is " << b.pretty_print() << endl;
  Sqrt c = a + b;
  cout << "c is " << c.pretty_print() << endl;
}

