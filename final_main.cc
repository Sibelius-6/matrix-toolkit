#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Matrix {
    int row, col;
public:
    void setRow(int r) { row = r; }

    void setCol(int c) { col = c; }
};


void matrixRead(int lang, Matrix &m) {
    int r, c;
    cout << " -- " << (lang ? "please enter row -> col in order" : "请按照行列的数序输入") << endl;
    cout << " -- " << (lang ? "range is " : "范围是") << "[1, 10]" << endl;
    cin >> r >> c;
    if (!(1 <= r && r <= 10 && 1 <= c && c <= 10)) throw out_of_range("row, column > 10 or < 1");
    m.setRow(r);
    m.setCol(c);
}

int main() {
    cout << " -- " << "Choose your preferred language. 请选择偏好语言" << endl;
    cout << " -- " << "zh or en? (case sensitive)" << endl;
    // 1 stands for english, 0 stands for Chinese
    int lang = -1;
    string s;
    cin >> s;
    if (s == "en") lang = 1;
    else if (s == "zh") lang = 0;
    else {
        cout << " -- " << "unrecognized input, exit..." << endl;
        return 0;
    }

    Matrix m;
    try { matrixRead(lang, m); }
    catch (const out_of_range &oor) {
        cerr << "Out of Range error: " << oor.what() << endl;
        throw;
    }
}

