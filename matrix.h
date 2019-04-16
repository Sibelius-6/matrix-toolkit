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

    void set_ij(int i, int j, int value);

    Complex get_ij(int i, int j);

    int getR() const { return row; }

    int getC() const { return col; }


};


#endif
