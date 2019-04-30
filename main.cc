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

    cout << "- and the spectral radius " << m.spectral_radius() << endl;
}
