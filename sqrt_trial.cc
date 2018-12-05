#include <string>
#include <iostream>
#include <map>
using namespace std;

typedef size_t radicand;
typedef int multiple;

class Sqrt {
  int rational;
  map<radicand, multiple> irrational;
  // = rational + multiple * √radicand
public:
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
};

int main() {
  map<radicand, multiple> i {
    {2, 3}, {10, 1}, {8, -1}, {3, 102}, {23, 0}, {29, -102}
  };
  Sqrt six {-10, i};
  cout << six.pretty_print() << endl;
}

