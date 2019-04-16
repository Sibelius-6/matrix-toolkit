#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include "complex.h"

class Matrix {
    int row, col; // this should be consistent with the data
    std::vector <std::vector<Complex>> data;

public:
    Matrix(int row, int col);
//  ~Matrix();

    void set_ij(int i, int j, const Complex &value);

    const Complex &get_ij(int i, int j) const;

    int getR() const { return row; }

    int getC() const { return col; }

    Matrix operator+(const Matrix &other);

    Matrix operator-(const Matrix &other);

    Matrix operator*(const Matrix &other) const;


};


#endif
