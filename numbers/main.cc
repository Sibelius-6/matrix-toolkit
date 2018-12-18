#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <cmath>
#include "fraction.h"
#include "sqrt.h"
#include "complex.h"
using namespace std;

int main() {
  Frac one = {{1, {{}}}, {1, {{}}}};
  Frac two = {{2, {{}}}, {1, {{}}}};
  Frac _two = {{-2, {{}}}, {1, {{}}}};
  Frac _one = {{-1, {{}}}, {1, {{}}}};
  cout << endl << "Now complex operation..." << endl << endl;

  Complex e = {_one, _two};
  Complex f = {_one, _two};
  
  cout << "e: " << e.pretty_print() << " f: " 
                << f.pretty_print() << endl << endl;
  
//  cout << "e+f is " << (e+f).pretty_print() << endl;
//  cout << "e-f is " << (e-f).pretty_print() << endl;
//  cout << "e*f is " << (e*f).pretty_print() << endl;
  cout << "e^0 is " << (power(e, 0)).pretty_print() << endl;
  cout << "e^1 is " << (power(e, 1)).pretty_print() << endl;
  cout << "e^2 is " << (power(e, 2)).pretty_print() << endl;
  cout << "e^3 is " << (power(e, 3)).pretty_print() << endl;
}
