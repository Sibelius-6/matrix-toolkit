#include <iostream>
#include <string>
#include <stdexcept>
#include "matrix.h"
#include "complex.h"
using namespace std;


int main() {
  Matrix m {2, 3};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      cout << "row: " << i << "col: " << j << "value : " << m.get_ij(i, j).pretty_print() << endl;
    }
  }
}
