#include <vector>
#include <string>
#include <memory>
#include "complex.h"
#include "matrix.h"

using namespace std;

// By default, all the entries are filled with 0
Matrix::Matrix(int row, int col): row{row}, col{col} {
  vector<unique_ptr<Complex>> row_of_zeros (col, make_unique<Complex>());
  vector<vector<unique_ptr<Complex>>> all_zero (row, row_of_zeros);
  data = move(all_zero);
}


