#include <vector>
#include <string>
#include "complex.h"
#include "matrix.h"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <stdexcept>
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

Matrix Matrix::operator-(const Matrix &other) {
    Matrix res {row, col};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            res.set_ij(i, j, data[i][j] - other.get_ij(i, j));
        }
    }
    return res;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (col != other.getR()) throw logic_error("Can't do matrix multiplication");
    Matrix res {row, other.getC()};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < other.getC(); ++j) {
            Complex sum {0};
            for (int k = 0; k < col; ++k) {
                sum = sum + get_ij(i, k) * other.get_ij(k, j);
            }
            res.set_ij(i, j, sum);
        }
    }
    return res;
}

Matrix Matrix::operator*(const Complex &scalar) const {
    Matrix res {row, col};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            res.set_ij(i, j, get_ij(i, j) * scalar);
        }
    }
    return res;
}

bool Matrix::operator==(const Matrix &other) const {
    if (row != other.getR()) return false;
    if (col != other.getC()) return false;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (get_ij(i, j) != other.get_ij(i, j)) return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other) const {
    return !(*this == other);
}

void Matrix::display() const {
    if (row == 0) {
        cout << "[ empty ]" << endl;
        return;
    }
    vector <int> place_holders(col, 0);
    for (auto r: data) {
        for (int c = 0; c < col; ++c) {
            place_holders[c] = max(place_holders[c], r.at(c).placeHolder());
        }
    }

    string empty_line = "[";
    for (auto ph : place_holders) empty_line += " " + string(ph, ' ') + " ";
    empty_line += "]";

    for (int i = 0; i < row; ++i) {
        if (i != 0) cout << empty_line << endl;
        auto this_row = data[i];
        cout << "[";
        for (int j = 0; j < col; ++j) cout << " " << this_row[j].reformat(place_holders[j]) << " ";
        cout << "]" << endl;
    }
}

Complex Matrix::determinant() const {
    return Complex {1};
}

size_t Matrix::rank() const {
    return 1;
}

Complex Matrix::trace() const {
    if (!square()) throw logic_error("Can't calculate trace for rectangular matrix");
    Complex res {0};
    for (int i = 0; i < row; ++i) res = res + get_ij(i, i);
    return res;
}

// for full definition, please search for wikipedia on nilpotent matrix
size_t Matrix::index() const {
    if (!nilpotent()) throw logic_error("Matrix is not nilpotent");
    if (!square()) throw logic_error("Matrix is not square");

    Matrix zero = zero_matrix(row, col);
    Matrix res = *this;
    size_t k = 1;
    while (res != zero) {
        res = res * (*this);
        ++k;
    }
    return k;
}

bool Matrix::square() const {
    return col == row;
}

bool Matrix::nilpotent() const {
    // using all eigenvalues = 0 to get this result
    return true;
}

Matrix Matrix::identity_matrix(size_t n) {
    Matrix res {n, n};
    for (int i = 0; i < n; ++i) res.set_ij(i, i, 1);
    return res;
}


Matrix Matrix::zero_matrix(size_t r, size_t c) {
    return Matrix {r, c};
}

Matrix operator*(const Complex &scalar, const Matrix &m) {
    return m * scalar;
}