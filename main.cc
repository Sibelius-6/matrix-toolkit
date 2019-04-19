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
            m.set_ij(i, j, one);
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            n.set_ij(i, j, two);
        }
    }
    Matrix res = m * n;
    res.display();
}
