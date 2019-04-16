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
void Matrix::set_ij(int i, int j, const Complex &value) {
    assert(0 <= i && i <= row - 1 && 0 <= j && j <= col - 1 && "i,j is out_of_range");
    data[i][j] = value;
}

const Complex &Matrix::get_ij(int i, int j) const {
    assert(0 <= i && i <= row - 1 && 0 <= j && j <= col - 1 && "i,j is out_of_range");
    return data[i][j];
}

Matrix Matrix::operator+(const Matrix &other) {
    // add exception later on for checking whether two matrices have same dimension
    Matrix res {row, col};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            res.set_ij(i, j, data[i][j] + other.get_ij(i, j));
        }
    }
    return res;
}
