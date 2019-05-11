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
    cout << "\033[1;34m> Matrix " << name << " is successfully read in!\033[0m" << endl;
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
            cout << "\033[1;1mquick-read\033[0m:    quickly input a matrix (other entries will be filled by zero)"
                 << endl;
            cout << "\033[1;1mls\033[0m:            list all current matrices that were inputted" << endl;
            cout << "\033[1;1moperate\033[0m:       Matrices operation mode" << endl;
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
        } else if (cmd == "quit" || cmd == "q") {
            break;
        } else if (cmd == "operate") {
            cout << endl << "\033[1;7m> Matrices Operation Mode <\033[0m" << endl;
            if (matrices.size() == 0) {
                cout << "\033[1;4m> No matrices are available for operation."
                     << "Please 'read-matrix' to read in a matrix.\033[0m" << endl;
                continue;
            }
            cout << "\033[1;4m> Currently, " << matrices.size() << " matrices have been read in. They are:\033[0m"
                 << endl;
            for (auto it = matrices.begin(); it != matrices.end(); ++it) {
                cout << it->first << " ";
            }
            cout << endl;

            cout << "\033[1;4m> Select your operation arity. unary or binary?\033[0m" << endl;
            string type;
            cin >> type;
            while (type != "binary" && type != "unary") {
                cerr << "\033[1;31mError: \033[0m Unrecognized arity." << endl;
                cin >> type;
            }

            if (type == "binary") {
                cout << "\033[1;4m> Choose from:\033[0m" << endl;
                cout << "+      -       *" << endl;
                cout << "\033[1;4m> Select first argument:\033[0m" << endl;
                string first, second, op;
                cin >> first;
                while (matrices.find(first) == matrices.end()) {
                    cerr << "\033[1;31mError\033[0m: This name \033[4m" << first << "\033[0m doesn't exist."
                         << endl;
                    cin >> first;
                }
                cout << "\033[1;4m> Select the operation:\033[0m" << endl;
                cin >> op;
                while (op != "+" && op != "*" && op != "*") {
                    cerr << "\033[1;31mError\033[0m: operation is not valid." << endl;
                    cin >> op;
                }
                cout << "\033[1;4m> Select second argument:\033[0m" << endl;
                cin >> second;
                while (matrices.find(second) == matrices.end()) {
                    cerr << "\033[1;31mError\033[0m: This name \033[4m" << second << "\033[0m doesn't exist."
                         << endl;
                    cin >> second;
                }
                try {
                    if (op == "+") {
                        Matrix res = matrices[first] + matrices[second];
                    } else if (op == "-") {
                        Matrix res = matrices[first] - matrices[second];
                    } else {
                        Matrix res = matrices[first] * matrices[second];
                    }

                    cout << endl << first << " " << op << " " << second << " is " << endl << res;
                    cout << endl << "\033[1;4m>Want to store your result? (y or n)\033[0m" << endl;
                    string store;
                    cin >> store;
                    while (store != "y" && store != "n") {
                        cin >> store;
                    }
                    if (store == "y") {
                        cout << endl << "\033[1;4m>Give a name to the result\033[0m" << endl;
                        string res_name;
                        cin >> res_name;
                        while (matrices.find(res_name) != matrices.end()) {
                            cerr << "\033[1;31mError\033[0m: This name \033[4m" << res_name << "\033[0m was taken."
                                 << endl;
                            cin >> res_name;
                        }
                    }
                } catch (const exception &e) {
                    cerr << "Sorry, " << op << "cannot be done, because " << e.what() << endl;
                    cerr << "Please restart your operation." << endl;
                }

            } else {
                cout << "\033[1;4m> Unary operations (or invariants of matrix), namely:\033[0m" << endl;
                cout << "det:   determinant     rank:    rank     trace:    trace" << endl;
                cout << "index: index (for nilpotent matrices)" << endl;
                cout << "ev:    eigenvalues (with multiplicity)   sv:      singular values" << endl;
                cout << "RREF:  RREF        inv:     inverse     left_inv / rt_inv: left/right inverse" << endl;
                cout << "tr:    transpose   conj:    conjugate   radius:   spectral radius" << endl << endl;
                cout << "square, symmetric, normal, Hermitian, unitary, diagonal, diagonalizable" << endl;
                cout << "upper_tri, lower_tri, orthogonal, invertible, nilpotent" << endl;

                string matrix_name;
                cout << "\033[1;4m> Select the matrix:\033[0m" << endl;
                cin >> matrix_name;
                while (matrices.find(matrix_name) == matrices.end()) {
                    cerr << "\033[1;31mError\033[0m: This name \033[4m" << matrix_name
                         << "\033[0m doesn't exist."
                         << endl;
                    cin >> matrix_name;
                }
                while (1) {
                    Matrix copy = matrices[matrix_name];
                    string op;
                    cout << "\033[1;4m> Type your operation(s)\033[0m"
                         << ", or 'quit' to quit, or 'help' to see whole options" << endl;
                    cin >> op;
                    try {
                        if (op == "det") {
                            cout << ">determinant is " << copy.determinant();
                        } else if (op == "rank") {
                            cout << ">rank is " << copy.rank();
                        } else if (op == "trace") {
                            cout << ">trace is " << copy.trace();
                        } else if (op == "ev") {
                            copy.geometric_multiplicity();
                            copy.algebraic_multiplicity();
                        } else if (op == "sv") {
                            copy.singular_values();
                        } else if (op == "RREF") {
                            cout << ">RREF is" << endl;
                            copy.RREF();
                            cout << copy;
                        } else if (op == "inv") {
                            cout << ">inverse is" << endl;
                            cout << copy.inverse();
                        } else if (op == "left_inv") {
                            cout << ">left inverse is" << endl;
                            cout << copy.left_inverse();
                        } else if (op == "rt_inv") {
                            cout << ">right inverse is" << endl;
                            cout << copy.right_inverse();
                        } else if (op == "tr") {
                            cout << ">transpose is" << endl;
                            cout << copy.transpose();
                        } else if (op == "conj") {
                            cout << ">conjugate is" << endl;
                            cout << copy.conjugate();
                        } else if (op == "radius") {
                            cout << ">spectral radius is" << copy.spectral_radius();
                        } else if (op == "index") {
                            cout << ">index (nilpotent matrix) is " << copy.index();
                        } else if (op == "square") {
                            cout << matrix_name << " is ";
                            if (!copy.square()) cout << "not";
                            cout << " a square matrix.";
                        } else if (op == "symmetric") {
                            cout << matrix_name << " is ";
                            if (!copy.symmetric()) cout << "not";
                            cout << " symmetric.";
                        } else if (op == "normal") {
                            cout << matrix_name << " is ";
                            if (!copy.normal()) cout << "not";
                            cout << " normal.";
                        } else if (op == "Hermitian") {
                            cout << matrix_name << " is ";
                            if (!copy.Hermitian()) cout << "not";
                            cout << " Hermitian.";
                        } else if (op == "unitary") {
                            cout << matrix_name << " is ";
                            if (!copy.unitary()) cout << "not";
                            cout << " unitary.";
                        } else if (op == "diagonal") {
                            cout << matrix_name << " is ";
                            if (!copy.diagonal())cout << "not";
                            cout << " diagonal.";
                        } else if (op == "diagonalizable") {
                            cout << matrix_name << " is ";
                            if (!copy.diagonalizable()) cout << "not";
                            cout << " diagonalizable.";
                        } else if (op == "upper_tri") {
                            cout << matrix_name << " is ";
                            if (!copy.upper_triangular()) cout << "not";
                            cout << " upper triangular.";
                        } else if (op == "lower_tri") {
                            cout << matrix_name << " is ";
                            if (!copy.lower_triangular()) cout << "not";
                            cout << " lower triangular.";
                        } else if (op == "orthogonal") {
                            cout << matrix_name << " is ";
                            if (!copy.orthogonal()) cout << "not";
                            cout << " orthogonal.";
                        } else if (op == "invertible") {
                            cout << matrix_name << " is ";
                            if (!copy.invertible()) cout << "not";
                            cout << " invertible.";
                        } else if (op == "nilpotent") {
                            cout << matrix_name << " is ";
                            if (!copy.nilpotent()) cout << "not";
                            cout << " nilpotent.";
                        } else if (op == "help") {
                            cout << endl
                                 << "\033[1;4m> Unary operations (or invariants of matrix) to choose, namely:\033[0m"
                                 << endl << "det:   determinant     rank:    rank     trace:    trace" << endl
                                 << "index: index (for nilpotent matrices)" << endl
                                 << "ev:    eigenvalues (with multiplicity)   sv:      singular values" << endl
                                 << "RREF:  RREF        inv:     inverse     left_inv / rt_inv: left/right inverse"
                                 << endl
                                 << "tr:    transpose   conj:    conjugate   radius:   spectral radius" << endl
                                 << endl
                                 << "square, symmetric, normal, Hermitian, unitary, diagonal, diagonalizable"
                                 << endl
                                 << "upper_tri, lower_tri, orthogonal, invertible, nilpotent" << endl;
                        } else if (op == "quit") {
                            break;
                        } else {
                            cerr << "\033[1;31mUnrecognized operation: \033[0m" << op << endl;
                        }
                        cout << endl;
                    } catch (const exception &e) {
                        cerr << "Sorry, " << op << "cannot done, because " << e.what() << endl;
                        cerr << "Please try other operations." << endl;
                    }
                }

            }


        } else {
            cerr << "\033[1;2mUnrecognized command: \033[0m" << cmd << "\033[1;2m. See 'help'. \033[0m" << endl;
        }
        // cout << "\033[1;2mYour command is \033[0m" << cmd << endl;
    }
}


