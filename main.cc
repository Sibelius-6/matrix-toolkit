#include <string>
#include <iostream>
#include "complex.h"
using namespace std;

int main() {

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
  

}
