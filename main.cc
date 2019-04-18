#include <iostream>
#include <string>
#include <stdexcept>
#include "matrix.h"
#include "complex.h"

using namespace std;


int main() {
    Complex one {1};
    Complex two {2};
    Matrix m {2, 3};
    Matrix m2 {2, 3};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            m.set_ij(i, j, one);
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            m2.set_ij(i, j, two);
        }
    }
    Matrix res = m + m2;
    Complex half = one / two;
    res = res * half;
    res.set_ij(0, 1, one);
    res.set_ij(1, 2, two);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "row: " << i << "col: " << j << "value : " << res.get_ij(i, j).pretty_print() << endl;
        }
    }
    res.display();
}
