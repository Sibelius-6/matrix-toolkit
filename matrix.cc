#include <vector>
#include <string>
#include "complex.h"
#include "matrix.h"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <stdexcept>

// Eigen library
#include <Eigen/Eigenvalues>

using Eigen::EigenSolver;
using Eigen::MatrixXd;

using namespace std;


// here i, j are indexes
void Matrix::swap_rows(int i, int k) {
    if (i >= row || i < 0 || k >= row || k < 0) throw logic_error("out of range");
    swap(data[i], data[k]);
}

void Matrix::divide_row(int i, const Complex &v) {
    if (i >= row || i < 0) throw logic_error("Out of range");
    for (auto &d : data[i]) d = d / v;
}

// row_i += v * row_k
void Matrix::add_multiple_row(int i, int k, const Complex &v) {
    if (i >= row || i < 0 || k >= row || k < 0) throw logic_error("out of range");
    for (int c = 0; c < col; ++c) data[i][c] = data[i][c] + v * data[k][c];
}

bool Matrix::all_zero_row(int i) const {
    Complex zero{0};
    for (int j = 0; j < col; ++j) {
        if (data[i][j] != zero) return false;
    }
    return true;
}


// By default, all the entries are filled with 0
Matrix::Matrix(int row, int col) : row{row}, col{col} {
    vector <Complex> row_of_zeros(col, Complex());
    vector <vector<Complex>> all_zero(row, row_of_zeros);
    data = move(all_zero);
}


// requires: 0 <= i <= row-1	0 <= j <= col-1
void Matrix::set_ij(int i, int j, const Complex &value) {
    assert(0 <= i && i <= row - 1 && 0 <= j && j <= col - 1 && "i,j is out_of_range");
    data[i][j] = value;
}

const Complex &Matrix::get_ij(int i, int j) const {
    assert(0 <= i && i <= row - 1 && 0 <= j && j <= col - 1 && "i,j is out_of_range");
    return data[i][j];
}

Matrix Matrix::operator+(const Matrix &other) const {
    if (row != other.getR() || col != other.getC()) throw logic_error("Dimension doesn't match");
    Matrix res{row, col};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            res.set_ij(i, j, data[i][j] + other.get_ij(i, j));
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix &other) const {
    if (row != other.getR() || col != other.getC()) throw logic_error("Dimension doesn't match");
    Matrix res{row, col};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            res.set_ij(i, j, data[i][j] - other.get_ij(i, j));
        }
    }
    return res;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (col != other.getR()) throw logic_error("Dimension doesn't match");
    Matrix res{row, other.getC()};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < other.getC(); ++j) {
            Complex sum{0};
            for (int k = 0; k < col; ++k) {
                sum = sum + get_ij(i, k) * other.get_ij(k, j);
            }
            res.set_ij(i, j, sum);
        }
    }
    return res;
}

Matrix Matrix::operator*(const Complex &scalar) const {
    Matrix res{row, col};
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
    vector<int> place_holders(col, 0);
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

// source: https://www.tutorialspoint.com/cplusplus-program-to-compute-determinant-of-a-matrix
Complex Matrix::determinant_helper(int n) const {
    if (!square()) throw logic_error("Can't determine determinant for non-square matrix");
    Complex det{0};
    Matrix submatrix{row, col};
    if (n == 0) return det;
    if (n == 1) return get_ij(0, 0);
    if (n == 2) return ((get_ij(0, 0) * get_ij(1, 1)) - (get_ij(1, 0) * get_ij(0, 1)));
    else {
        for (int x = 0; x < n; ++x) {
            int subi = 0;
            for (int i = 1; i < n; ++i) {
                int subj = 0;
                for (int j = 0; j < n; ++j) {
                    if (j == x) continue;
                    submatrix.set_ij(subi, subj, get_ij(i, j));
                    subj++;
                }
                subi++;
            }
            Complex minus_one{-1};
            det = det + (pow(minus_one, x) * get_ij(0, x) * submatrix.determinant_helper(n - 1));
        }
    }
    return det;
}

Complex Matrix::determinant() const {
    if (!square()) throw logic_error("Can't determine determinant for non-square matrix");
    return determinant_helper(row);
}


size_t Matrix::rank() const {
    Matrix copy = *this;
    copy.RREF();
    size_t rank = 0;

    for (int i = 0; i < row; ++i) {
        if (copy.all_zero_row(i)) return rank;
        else ++rank;
    }

    return rank;
}

Complex Matrix::trace() const {
    if (!square()) throw logic_error("Can't calculate trace for rectangular matrix");
    Complex res{0};
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

void Matrix::eigenvalues(vector <Complex> &v) const {
    if (!square()) throw logic_error("Can't calculate eigenvalues for non-square matrix");
    MatrixXd m(row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (!get_ij(i, j).Real()) throw logic_error("Sorry, EigenSolver library doesn't support Complex Matrices");
            m(i, j) = get_ij(i, j).doublelize().real();
        }
    }
    EigenSolver <MatrixXd> es(m);
    for (size_t x = 0; x < row; ++x) {
        v.emplace_back(complex_double_to_Complex(es.eigenvalues()[x]));
    }
}

void Matrix::singular_values() const {
    Matrix AT_times_A = transpose() * (*this);
    vector <Complex> v;
    AT_times_A.eigenvalues(v);
    for (auto ev : v) {
        try {
            cout << sqrt(ev) << endl;
        }
        catch (const exception &e) {
            cout << ">Have some trouble calculating sqrt, since " << e.what() << endl;
            cout << ">So the square of this singular value is " << ev;
        }
    }
}

Complex Matrix::spectral_radius() const {
    vector <Complex> v;
    eigenvalues(v);
    Complex res{0};
    for (Complex ev : v) {
        Complex tmp = sqrt(ev.sqr_norm());
        if (tmp > res) res = tmp;
    }
    return res;
}

void Matrix::algebraic_multiplicity() const {
    cout << endl << "\033[1;31m***** Algebraic Multiplicity *****\033[0m" << endl;
    vector <Complex> evs;
    eigenvalues(evs);
    int adjust = 0;
    for (Complex ev : evs) adjust = max(adjust, ev.placeHolder());
    for (Complex ev : evs) {
        cout << ev.reformat(adjust) << " :  " << count(evs.begin(), evs.end(), ev) << endl;
    }
    cout << endl;
}

static size_t geometric_multiplicity_helper(const Complex &c, const Matrix &A) {
    if (!A.square()) throw logic_error("Can't find geometric multiplicity");
    Matrix A_lambda_I = A - c * A.identity_matrix(A.getR());
    // rank-nullity theorem
    return A_lambda_I.getC() - A_lambda_I.rank();
}

void Matrix::geometric_multiplicity() const {
    cout << endl << "\033[1;31m***** Geometric Multiplicity *****\033[0m" << endl;
    vector <Complex> evs;
    eigenvalues(evs);
    int adjust = 0;
    for (Complex ev : evs) adjust = max(adjust, ev.placeHolder());
    for (Complex ev : evs) {
        cout << ev.reformat(adjust) << " :  " << geometric_multiplicity_helper(ev, *this)<< endl;
    }
    cout << endl;
}

// source http://rosettacode.org/wiki/Reduced_row_echelon_form#C.2B.2B
void Matrix::RREF() {
    Complex zero{0};
    int lead = 0;
    for (int r = 0; r <= row - 1; ++r) {
        if (lead > col - 1) return;
        int i = r;
        while (data[i][lead] == zero) {
            ++i;
            if (i > row - 1) {
                i = r;
                ++lead;
                if (lead > col - 1) return;
            }
        }
        swap_rows(i, r);
        const Complex lead_num = data[r][lead];
        divide_row(r, lead_num);
        for (int i = 0; i <= row - 1; ++i) {
            if (i != r) add_multiple_row(i, r, zero - data[i][lead]);
        }
    }
}

Matrix Matrix::inverse() const {
    if (!invertible()) throw logic_error("matrix is not invertible");
    Matrix temp{row, col * 2};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            temp.set_ij(i, j, get_ij(i, j));
        }
    }
    Complex one{1};
    for (int d = 0; d < col; ++d) temp.set_ij(d, col + d, one);
    temp.RREF();
    Matrix res{row, col};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            res.set_ij(i, j, temp.get_ij(i, col + j));
        }
    }
    return res;
}

Matrix Matrix::right_inverse() const {
    try {
        return transpose() * (*this * transpose()).inverse();
    }
    catch (...) {
        throw logic_error("this matrix doesn't have right inverse");
    }
}

Matrix Matrix::left_inverse() const {
    try {
        return (transpose() * *this).inverse() * transpose();
    }
    catch (...) {
        throw logic_error("this matrix doesn't have left inverse");
    }
}

Matrix Matrix::transpose() const {
    Matrix res{col, row};
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            res.set_ij(i, j, get_ij(j, i));
        }
    }
    return res;
}

Matrix Matrix::conjugate() const {
    Matrix res{row, col};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            res.set_ij(i, j, get_ij(i, j).conjugate());
        }
    }
    return res;
}

bool Matrix::symmetric() const {
    return square() && (transpose() == *this);
}

bool Matrix::diagonal() const {
    if (!square()) throw logic_error("Can't determine for a non-square matrix");
    Complex zero{0};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i != j && get_ij(i, j) != zero) return false;
        }
    }
    return true;
}

bool Matrix::invertible() const {
    if (!square()) throw logic_error("no point to determine whether non-square matrix is invertible");
    if (rank() == row) return true;
    return false;
}

bool Matrix::Hermitian() const {
    return square() && (*this == transpose().conjugate());
}

bool Matrix::unitary() const {
    return invertible() && (inverse() == transpose().conjugate());
}

bool Matrix::orthogonal() const {
    return invertible() && (inverse() == transpose());
}

bool Matrix::normal() const {
    return square() && (*this * transpose().conjugate() == transpose().conjugate() * *this);
}

bool Matrix::nilpotent() const {
    // using all eigenvalues = 0 to get this result
    vector <Complex> evs;
    eigenvalues(evs);
    for (Complex ev : evs) {
        Complex zero;
        if (ev != zero) return false;
    }
    return true;
}

bool Matrix::upper_triangular() const {
    if (!square()) throw logic_error("We don't discuss triangular properties with non-square");
    Complex zero{0};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (j < i && get_ij(i, j) != zero) return false;
        }
    }
    return true;
}

bool Matrix::lower_triangular() const {
    return transpose().upper_triangular();
}

bool Matrix::diagonalizable() const {
    if (!square()) return false;
    vector <Complex> evs;
    eigenvalues(evs);
    for (Complex ev : evs) {
        size_t g = geometric_multiplicity_helper(ev, *this);
        size_t a = count(evs.begin(), evs.end(), ev);
        if (a != g) return false;
    }
    return true;
}

// here starts the decomposition
/*void Matrix::diagonalization() const {
    if (!diagonalizable()) throw logic_error("Not diagonalizable");
    vector <Complex> evs;
    eigenvalues(evs);
    sort(evs.begin(), evs.end());
    int i = 0;
    Matrix P {row, col};
    while (i < col) {
        Complex ev = evs[i];
        size_t multiplicity = count(evs.begin(), evs.end(), ev);
        Matrix A_lambda_I = *this - ev * identity_matrix(getR());
        A_lambda_I.RREF();
        i += multiplicity;
    }
}*/

Matrix Matrix::identity_matrix(size_t n) {
    Matrix res{n, n};
    for (int i = 0; i < n; ++i) res.set_ij(i, i, 1);
    return res;
}

Matrix Matrix::zero_matrix(size_t r, size_t c) {
    return Matrix{r, c};
}


Matrix operator*(const Complex &scalar, const Matrix &m) {
    return m * scalar;
}

ostream &operator<<(ostream &out, const Matrix &m) {
    int row = m.row;
    int col = m.col;
    auto data = m.data;
    if (row == 0) {
        out << "[ empty ]" << endl;
        return out;
    }
    vector<int> place_holders(col, 0);
    for (auto r: data) {
        for (int c = 0; c < col; ++c) {
            place_holders[c] = max(place_holders[c], r.at(c).placeHolder());
        }
    }

    string empty_line = "[";
    for (auto ph : place_holders) empty_line += " " + string(ph, ' ') + " ";
    empty_line += "]";

    for (int i = 0; i < row; ++i) {
        if (i != 0) out << empty_line << endl;
        auto this_row = data[i];
        out << "[";
        for (int j = 0; j < col; ++j) out << " " << this_row[j].reformat(place_holders[j]) << " ";
        out << "]" << endl;
    }
    return out;
}
