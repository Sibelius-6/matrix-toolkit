#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <cmath>
//#include "fraction.h"
//#include "sqrt.h"
#include "complex.h"
using namespace std;

int main() {
  Frac zero = {{0, {{}}}, {1, {}}};
  Frac one = {{-3, {}}, {2, {{}}}};
//  Frac oone {{50, {{}}}, {50, {{}}}};
//  Frac ttwo {{-46, {{}}}, {-27, {{}}}};
//  Frac two = {{2, {{}}}, {1, {{}}}};
//  Frac _two = {{-2, {{}}}, {1, {{}}}};
//  Frac _one = {{-1, {{}}}, {1, {{}}}};
//  Frac ttt = { {0, {{6, -2}}}, {-4 , {}} };
 //  cout << endl << "Now complex operation..." << endl << endl;

  Complex e {1};

  Complex f {2};
  Complex g {0};
  Complex h {-1};
  Complex i {1000};
  Complex all[] = {e, f, g, h, i};
  int ii = 0;

  for (auto cc : all) { 
    cout << 'e' + ii << ": " << cc.pretty_print() << " which hold place : " << cc.placeHolder() << endl;
    ++ii;
  } 
  

//  Complex zzero {zero, zero}; 
//  cout << "ttt: " << ttt.pretty_print() << endl; /* " f: " */ 
//                << f.pretty_print() << endl << endl;
  
//  cout << "e == f: " << (e == f) << endl;
//  cout << "e+f is " << (e+f).pretty_print() << endl;
//  cout << "e-f is " << (e-f).pretty_print() << endl;
//  cout << "e*f is " << (e*f).pretty_print() << endl;
//  cout << "sqrt e is " << (sqrt(e)).pretty_print() << endl;
//  cout << "e^1 is " << (pow(e, 1)).pretty_print() << endl;
//  cout << "e^2 is " << (pow(e, 2)).pretty_print() << endl;
//  cout << "e^3 is " << (pow(e, 3)).pretty_print() << endl;
}
