#include <vector>
#include <string>
#include <memory>
#include "complex.h"
#include "matrix.h"
#include <cassert>
using namespace std;

// By default, all the entries are filled with 0
Matrix::Matrix(int row, int col): row{row}, col{col} {
  unique_ptr<Complex> zero (new Complex());
  vector<unique_ptr<Complex>> row_of_zeros;
  for (int i = 0; i < col; ++i) row_of_zeros.push_back(move(zero));
  
  vector<vector<unique_ptr<Complex>>> all_zero;
  for (int i = 0; i < row; ++i) all_zero.push_back(move(row_of_zeros));
  data = move(all_zero);
}


// requires: 0 <= i <= row-1	0 <= j <= col-1
void Matrix::set_ij(int i, int j, int value) {
  assert(0 <= i && i <= row - 1 && 0 <= j && j <= col - 1 && "i,j is out_of_range");
  *(data[i][j]) = Complex{value};
}

unique_ptr<Complex> Matrix::get_ij(int i, int j) {
  assert(0 <= i && i <= row - 1 && 0 <= j && j <= col - 1 && "i,j is out_of_range");
  return make_unique<Complex>(*(data[i][j]));
}

