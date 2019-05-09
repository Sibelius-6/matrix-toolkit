#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

struct Matrix {
    int row, col;

    void setRow(int r) { row = r; }

    void setCol(int c) { col = c; }
};

string getInput(bool integer = false) {
    if (integer) {
        int i = 0;
        while (!(cin >> i)) {
            if (cin.eof()) {
                i = 0;
                break;
            }
            cin.clear();
            cin.ignore();
        }
        return to_string(i);
    } else {
        string input = "uninitialized";
        do {
            cin >> input;
        } while (input == "");

        return input;
    }

}


void matrixRead(map <string, Matrix> &m) {
    string name;
    cout << "\033[1;34mPlease enter the name for this matrix\033[0m" << endl;
    do {
        name = getInput();
    } while (m.find(name) != m.end());

    cout << "\033[1;34mPlease enter the row and column for this matrix [1, 10].\033[0m" << endl;
    cout << "\033[1;34m>Row: \033[0m" << endl;
    int r, c;
    do {
        r = stoi(getInput(true));
    } while (r < 0 || r > 10);

    cout << "\033[1;34m>Col: \033[0m" << endl;
    do {
        c = stoi(getInput(true));
    } while (c < 0 || c > 10);

    Matrix mm{r, c};
    m.insert(pair<string, Matrix>(name, mm));
}

int main() {
    map <string, Matrix> mymap;
    matrixRead(mymap);
    matrixRead(mymap);
    for (auto it = mymap.begin(); it != mymap.end(); ++it) {
        cout << "name: " << it->first << " r/c: "
             << (it->second).row << "/" << (it->second).col << endl;
    }
}

