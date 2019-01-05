#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>

class Complex;

class Matrix {
  int row, col; // this should be consistent with the data
  std::vector<std::vector<unique_ptr<Complex>>> data;

public:
  void setR(int r) { row = r; }
  void setC(int c) { col = c; }

  void setData(std::vector<std::vector<int>>);

  int getR() const { return row; }
  int getC() const { return col; }
  



};













#endif
