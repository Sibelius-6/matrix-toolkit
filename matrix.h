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
    Matrix(int row = 1, int col = 1);

    void set_ij(int i, int j, const Complex &value);

    const Complex &get_ij(int i, int j) const;

    inline int getR() const { return row; }

    inline int getC() const { return col; }

    Matrix operator+(const Matrix &other) const;

    Matrix operator-(const Matrix &other) const;

    Matrix operator*(const Matrix &other) const;

    Matrix operator*(const Complex &scalar) const;

    bool operator==(const Matrix &other) const;

    bool operator!=(const Matrix &other) const;

    void display() const;

    // methods below are invariants of matrix
    Complex determinant_helper(int n) const;

    Complex determinant() const;

    size_t rank() const;

    Complex trace() const;

    size_t index() const; // nilpotent matrix


    void eigenvalues(std::vector <Complex> &v) const;

    void singular_values() const;

    Complex spectral_radius() const;

    // these two methods will print the multiplicity
    void geometric_multiplicity() const;

    void algebraic_multiplicity() const;

    // methods below will return a matrix or a vector
    void RREF();

    Matrix inverse() const;

    Matrix left_inverse() const;

    Matrix right_inverse() const;

    Matrix transpose() const;

    Matrix conjugate() const;

    // methods below are to determine whether this matrix meets or not
    inline bool square() const { return col == row; }

    bool symmetric() const;

    bool normal() const;

    bool Hermitian() const;

    bool unitary() const;

    bool diagonal() const;

    bool diagonalizable() const;

    bool upper_triangular() const;

    bool lower_triangular() const;

    bool orthogonal() const;

    bool invertible() const;

    bool nilpotent() const;



    // decomposition: will print the result
    // rank_decomposition singular_value_decomposition
    /*void diagonalization() const;

    void orthogonal_diagonalization() const;

    void rank_decomposition() const;

    void singular_value_decomposition() const;*/

    // methods below are static, it can return a specific type of matrix
    static Matrix identity_matrix(size_t n);

    static Matrix zero_matrix(size_t r, size_t c);

    // public helpers (I'm bit lazy)
    bool all_zero_row(int i) const;


    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);
};

Matrix operator*(const Complex &scalar, const Matrix &m);


#endif
