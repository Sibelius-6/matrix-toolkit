#include <iostream>
#include <string>
#include <stdexcept>
#include "matrix.h"
#include "complex.h"

using namespace std;


int main() {
    Complex one {1};
    Complex two {2};
    Matrix m {4, 2};
    Matrix n {2, 3};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << ">Matrix M: row:" << i << " col:" << j << endl;
            int mm;
            cin >> mm;
            Complex mmm {mm};
            m.set_ij(i, j, mmm);
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << ">Matrix N: row:" << i << " col:" << j << endl;
            int nn;
            cin >> nn;
            Complex nnn {nn};
            n.set_ij(i, j, nnn);
        }
    }
    cout << ">M is" << endl;
    m.display();
    cout << ">N is" << endl;
    n.display();
    Matrix res = m * n;
    cout << ">M * N is" << endl;
    res.display();
}
