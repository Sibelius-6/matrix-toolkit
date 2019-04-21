#include <iostream>
#include <string>
#include <stdexcept>
#include "matrix.h"
#include "complex.h"

using namespace std;


int main() {
    Matrix m {3, 4};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << "\033[1;31m> Matrix M: row:" << i << " col:" << j << "\033[0m" << endl;
            int mm;
            cin >> mm;
            Complex mmm {mm};
            m.set_ij(i, j, mmm);
        }
    }
    cout << "rank: " << m.rank() << endl;
    m.display();
    m.RREF();
    cout << "-------" << endl;
    m.display();
}
