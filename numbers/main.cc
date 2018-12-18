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
  Frac zero = {{0, {{}}}, {1, {}}};
  Frac one = {{3, {}}, {2, {{}}}};
  Frac oone {{50, {{}}}, {50, {{}}}};
  Frac ttwo {{-46, {{}}}, {-27, {{}}}};
  Frac two = {{2, {{}}}, {1, {{}}}};
  Frac _two = {{-2, {{}}}, {1, {{}}}};
  Frac _one = {{-1, {{}}}, {1, {{}}}};
 //  cout << endl << "Now complex operation..." << endl << endl;

  Complex e {one, zero};
  Complex f {oone, ttwo};
  

  Complex zzero {zero, zero}; 
  cout << "e: " << e.pretty_print() << " f: " 
                << f.pretty_print() << endl << endl;
  
//  cout << "e == f: " << (e == f) << endl;
//  cout << "e+f is " << (e+f).pretty_print() << endl;
//  cout << "e-f is " << (e-f).pretty_print() << endl;
//  cout << "e*f is " << (e*f).pretty_print() << endl;
  cout << "sqrt e is " << (sqrt(e)).pretty_print() << endl;
//  cout << "e^1 is " << (pow(e, 1)).pretty_print() << endl;
//  cout << "e^2 is " << (pow(e, 2)).pretty_print() << endl;
//  cout << "e^3 is " << (pow(e, 3)).pretty_print() << endl;
}
