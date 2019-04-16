#include <vector>
#include <string>
#include "complex.h"
#include "matrix.h"
#include <cassert>

using namespace std;

// By default, all the entries are filled with 0
Matrix::Matrix(int row, int col) : row{row}, col{col} {
    vector <Complex> row_of_zeros(col, Complex());
    vector <vector<Complex>> all_zero(row, row_of_zeros);
    data = move(all_zero);
}

/*Matrix::~Matrix() {
  for (auto row : data) {
    for (auto i : row) {
      delete i;
    }
  }
}*/

// requires: 0 <= i <= row-1	0 <= j <= col-1
void Matrix::set_ij(int i, int j, int value) {
    assert(0 <= i && i <= row - 1 && 0 <= j && j <= col - 1 && "i,j is out_of_range");
    data[i][j] = Complex{value};
}

Complex Matrix::get_ij(int i, int j) {
    assert(0 <= i && i <= row - 1 && 0 <= j && j <= col - 1 && "i,j is out_of_range");
    return data[i][j];
}

