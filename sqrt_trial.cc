#include <string>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;

typedef size_t radicand;
typedef int multiple;


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



class Sqrt {
public:
  int rational;
  map<radicand, multiple> irrational;
  // = rational + multiple * √radicand

  Sqrt(int rational_, map<radicand, multiple> irrational_):
    rational{rational_}, irrational{irrational_} {
      for (auto &p : irrational) {
        int tmp = simplify(p.first);
	if (tmp == 0) {
	  rational += sqrt(p.first) * p.second; 
          p.second = 0;
        } else if (tmp > 1) {
          int tmp_r = p.first / (tmp * tmp);
          if (irrational.count(tmp_r)) 
				irrational.at(tmp_r) += tmp*p.second;
          else irrational.insert(pair<radicand, multiple>
						(tmp_r, tmp*p.second));
	  p.second = 0;
        }
      }

      for (auto it = irrational.begin(); it != irrational.end(); )
         if(it->second == 0) it = irrational.erase(it);
         else ++it;
      // remove the zero multiple
      // √18 ->3√3
    }
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

  Sqrt operator-(const Sqrt &other) {
    map<radicand, multiple> res_i = irrational;
    for (const auto &p : other.irrational) {
      if (res_i.count(p.first)) res_i.at(p.first) -= p.second;
      else res_i.insert(pair<radicand, multiple>(p.first, -p.second));
    }
    return { rational - other.rational, res_i };
  }

  Sqrt operator*(const Sqrt &other) {
    int res_r = rational * other.rational;
    map<radicand, multiple> res_i {};
    for (const auto &p : other.irrational) {
      for (const auto &q : irrational) {
        int radi_temp = p.first * q.first;
        if (res_i.count(radi_temp)) {
          res_i.at(radi_temp) += p.second * q.second;
        } else {
          res_i.insert(pair<radicand, multiple>(radi_temp, p.second*q.second));
        }
      }
    }
    for (const auto &p: irrational) {
      if (res_i.count(p.first)) { 
	res_i.at(p.first) += p.second*other.rational;
      } else {
	res_i.insert(pair<radicand, multiple>
			(p.first, p.second*other.rational));
      }
    }
    for (const auto &p: other.irrational) {
      if (res_i.count(p.first)) {
        res_i.at(p.first) += p.second*rational;
      } else {
        res_i.insert(pair<radicand, multiple>
                        (p.first, p.second*rational));
      }
    }
    return { res_r, res_i };
  }
};

int main() {
  map<radicand, multiple> p {
    {20, 3}
  };
  map<radicand, multiple> i {
    {2, 3}, {5, 1}, {9, 1}
  };
  map<radicand, multiple> j {
    {2, 4}, {10, -1}
  };
  Sqrt a {-10, i};
  cout << "a is " << a.pretty_print() << endl;
  Sqrt b {3, j};
  cout << "b is " << b.pretty_print() << endl;
  Sqrt c = a - b;
  cout << "a-b is " << c.pretty_print() << endl;
  Sqrt d = a * b;
  cout << "a*b is " << d.pretty_print() << endl;
}

