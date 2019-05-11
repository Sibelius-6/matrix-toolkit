#include <iostream>
#include <string>
#include <stdexcept>
#include "matrix.h"
#include "complex.h"
#include <complex>
#include <cmath>
#include <map>
#include <time.h>

using namespace std;


string getInput(bool integer = false) {
    if (integer) {
        int i = 5;
        while (!(cin >> i)) {
            cerr << "\033[1;31mError\033[0m: Your input is not valid." << endl;
            if (cin.eof()) {
                i = 5;
                break;
            }
            cin.clear();
            cin.ignore();
        }
        return to_string(i);
    } else {
        string input = "uninitialized" + to_string(time(NULL));
        cin >> input;
        return input;
    }

}


void matrixRead(map <string, Matrix> &m, bool quickmode = false) {
    string name;
    cout << "\033[1;34mPlease enter the name for this matrix\033[0m" << endl;
    name = getInput();
    while (m.find(name) != m.end()) {
        cerr << "\033[1;31mError\033[0m: This name \033[4m" << name << "\033[0m was taken previously." << endl;
        name = getInput();
    }

    cout << "\033[1;34mPlease enter the row and column for this matrix [1, 10].\033[0m" << endl << endl;
    cout << "\033[1;34m> Row: \033[0m" << endl;
    int r, c;

    r = stoi(getInput(true));
    while (r <= 0 || r > 10) {
        cerr << "\033[1;31mError\033[0m: Out of range." << endl;
        r = stoi(getInput(true));
    }

    cout << "\033[1;34m> Col: \033[0m" << endl;
    c = stoi(getInput(true));
    while (c <= 0 || c > 10) {
        cerr << "\033[1;31mError\033[0m: Out of range." << endl;
        c = stoi(getInput(true));
    }

    Matrix matrix{r, c};
    cout << "\033[1;2mSuccess\033[0m: The dimension is set. Row " << r << ", Col " << c << endl;
    if (!quickmode) {
        cout << "~~Now please set your entries~~ (integers only)" << endl << endl;
        for (int i = 0; i < r; ++i) {
            cout << "\033[1;34m> Input your " << i + 1 << "(th) row. \033[0m Press Enter after finishing one entry."
                 << endl;
            for (int j = 0; j < c; ++j) {
                int tmp = stoi(getInput(true));
                matrix.set_ij(i, j, Complex{tmp});
            }
        }
    }
    string confirm;
    do {
        cout << "\033[1;34m> Now your matrix is \033[0m" << endl << matrix;
        cout << endl << "\033[1;34m> Confirm? (y or n) \033[0m" << endl;
        cin >> confirm;
        if (confirm == "n") {
            cout << "\033[1;34m> Select the entry you want to modify.\033[0m" << endl;
            cout << "\033[1;34m> Row: \033[0m" << endl;
            int i, j;
            i = stoi(getInput(true)) - 1;
            while (i < 0 || i >= r) {
                cerr << "\033[1;31mError\033[0m: Out of range." << endl;
                i = stoi(getInput(true)) - 1;
            }

            cout << "\033[1;34m> Col: \033[0m" << endl;
            j = stoi(getInput(true)) - 1;
            while (j < 0 || j >= c) {
                cerr << "\033[1;31mError\033[0m: Out of range." << endl;
                j = stoi(getInput(true)) - 1;
            }

            cout << "\033[1;34m> New entry \033[0m" << endl;
            int tmp = stoi(getInput(true));
            matrix.set_ij(i, j, Complex{tmp});
        }
    } while (confirm != "y");
    m.insert(pair<string, Matrix>(name, matrix));
    cout << "\033[1;34m> Matrix " << name << "is successfully read in!\033[0m" << endl;
}

int main() {
    map <string, Matrix> matrices;

    cout << endl << endl;
    cout <<
         "███████╗██╗██████╗ ███████╗██╗     ██╗██╗   ██╗███████╗        ██████╗ ███████╗███╗   ██╗ ██████╗" << endl <<
         "██╔════╝██║██╔══██╗██╔════╝██║     ██║██║   ██║██╔════╝        ██╔══██╗██╔════╝████╗  ██║██╔════╝" << endl <<
         "███████╗██║██████╔╝█████╗  ██║     ██║██║   ██║███████╗        ██████╔╝█████╗  ██╔██╗ ██║██║  ███╗" << endl <<
         "╚════██║██║██╔══██╗██╔══╝  ██║     ██║██║   ██║╚════██║        ██╔═══╝ ██╔══╝  ██║╚██╗██║██║   ██║" << endl <<
         "███████║██║██████╔╝███████╗███████╗██║╚██████╔╝███████║        ██║     ███████╗██║ ╚████║╚██████╔╝" << endl <<
         "╚══════╝╚═╝╚═════╝ ╚══════╝╚══════╝╚═╝ ╚═════╝ ╚══════╝        ╚═╝     ╚══════╝╚═╝  ╚═══╝ ╚═════╝" << endl;
    cout << endl << "\033[1;35m> Welcome to Sibelius' matrix toolkit <\033[0m" << endl;

    string cmd;
    while (!cin.eof() && cmd != "quit" && cmd != "q") {
        cout << endl << "\033[1;35m- Now you can type your command ('help' for help manual)\033[0m" << endl;
        cin >> cmd;
        if (cmd == "clear") {
            cout << "\033[2J\033[1;1H"; // clear the screen
        } else if (cmd == "help") {
            cout << endl << "\033[1;7m> Short Help Page <\033[0m" << endl;
            cout << "\033[1;1mhelp\033[0m:          help page" << endl;
            cout << "\033[1;1mclear\033[0m:         clear the page" << endl;
            cout << "\033[1;1mq / quit\033[0m:      quit" << endl;
            cout << "\033[1;1mread-matrix\033[0m:   input a matrix" << endl;
            cout << "\033[1;1mquick-read\033[0m:    quickly input a matrix (other fields will be filled by zero)" << endl;
            cout << "\033[1;1mls\033[0m:            list all current matrices that were inputted" << endl;
            cout << "\033[1;7m> End of Help Page <\033[0m" << endl << endl; // the end of help page
        } else if (cmd == "ls") {
            cout << endl << "****** Displaying matrices ******" << endl;
            if (matrices.size() == 0) {
                cout << "Nothing can be displayed. Please 'read-matrix' to read in a matrix." << endl;
            } else {
                cout << "Currently, " << matrices.size() << " matrices have been read in." << endl;
                for (auto it = matrices.begin(); it != matrices.end(); ++it) {
                    cout << "\033[1;2mname: \033[0m" << it->first << endl << it->second << endl;
                }
                cout << endl;
            }
        } else if (cmd == "read-matrix") {
            matrixRead(matrices);
        } else if (cmd == "quick-read") {
            matrixRead(matrices, true);
        } else {
            cerr << "\033[1;2mUnrecognized command: \033[0m" << cmd << "\033[1;2m. See 'help'. \033[0m" << endl;
        }
        // cout << "\033[1;2mYour command is \033[0m" << cmd << endl;
    }
}


