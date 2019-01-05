#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <memory>
class Complex;

class Matrix {
  int row, col; // this should be consistent with the data
  std::vector<std::vector<std::unique_ptr<Complex>>> data;

public:
  Matrix(int row, int col);

  void set_ij(int i, int j);
  std::unique_ptr<Complex> get_ij(int i, int j);
    
  int getR() const { return row; }
  int getC() const { return col; }
  



};













#endif
