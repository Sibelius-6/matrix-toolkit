#include <iostream>
#include <string>
#include <stdexcept>
#include "matrix.h"
#include "complex.h"
#include <complex>
#include <vector>
#include <cmath>
using namespace std;


int main() {
    cout << "\033[1;31mEnter Your Dimension\033[0m" << endl;
    int dim;
    cin >> dim;
    Matrix m {dim, dim};
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            cout << "\033[1;31m> Matrix M: row:" << i << " col:" << j << "\033[0m" << endl;
            int mm;
            cin >> mm;
            Complex mmm {mm};
            m.set_ij(i, j, mmm);
        }
    }
    m.display();
    vector <Complex> v;
    m.eigenvalues(v);
    cout << endl << "Now eigenvalues!!" << endl;
    for (auto ev : v) {
        cout << ev << endl;
    }

    m.algebraic_multiplicity();

    m.geometric_multiplicity();

    if (m.diagonalizable()) cout << "diagonalizable" << endl;
    else cout << "not diagonalizable" << endl;
}
