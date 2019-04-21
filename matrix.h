#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include "complex.h"

class Matrix {
    int row, col; // this should be consistent with the data
    std::vector <std::vector<Complex>> data;

    void swap_rows(int i, int k);

    void divide_row(int i, const Complex &v);

    void add_multiple_row(int i, int k, const Complex &v);

public:
    Matrix(int row, int col);

    void set_ij(int i, int j, const Complex &value);

    const Complex &get_ij(int i, int j) const;

    int getR() const { return row; }

    int getC() const { return col; }

    Matrix operator+(const Matrix &other);

    Matrix operator-(const Matrix &other);

    Matrix operator*(const Matrix &other) const;

    Matrix operator*(const Complex &scalar) const;

    bool operator==(const Matrix &other) const;

    bool operator!=(const Matrix &other) const;

    void display() const;

    // methods below are invariants of matrix
    Complex determinant() const;

    size_t rank() const;

    Complex trace() const;

    size_t index() const; // nilpotent matrix

    size_t geometric_multiplicity() const;

    size_t algebraic_multiplicity() const;

    Complex *singular_values() const;

    Complex *eigenvalues() const;

    Complex spectral_radius() const;

    // methods below will return a matrix or a vector
    void RREF();

    Matrix inverse() const;

    Matrix left_inverse() const;

    Matrix right_inverse() const;

    Matrix adjoint() const;

    Matrix transpose() const;

    Matrix kernal() const;

    Matrix diagonalize() const;

    Matrix orthogonal_diagonalize() const;

    // methods below are to determine whether this matrix meets or not
    bool square() const;

    bool symmetric() const;

    bool diagonal() const;

    bool diagonalizable() const;

    bool triangular() const; // either upper or lower

    bool orthogonal() const;

    bool nilpotent() const;

    bool Hermitian() const;

    bool normal() const;

    // decomposition


    // methods below are static, it can return a specific type of matrix
    static Matrix identity_matrix(size_t n);

    static Matrix zero_matrix(size_t r, size_t c);

    // public helpers (I'm bit lazy)
    bool all_zero_row(int i) const;



    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);
};

Matrix operator*(const Complex &scalar, const Matrix &m);




#endif
