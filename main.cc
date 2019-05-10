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
        int i = 1;
        while (!(cin >> i)) {
            cerr << "\033[1;31mError\033[0m: Your input is not valid." << endl;
            if (cin.eof()) {
                i = 1;
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


void matrixRead(map <string, Matrix> &m) {
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

    Matrix mm{r, c};
    cout << "\033[1;2mSuccess\033[0m: The dimension is set. Row " << r << ", Col " << c << endl;
    cout << "~~Now please set your entries~~ (integers only)" << endl << endl;
    
    m.insert(pair<string, Matrix>(name, mm));
}

int main() {
    map <string, Matrix> mymap;
    /*matrixRead(mymap);
    matrixRead(mymap);
    for (auto it = mymap.begin(); it != mymap.end(); ++it) {
        cout << "name: " << it->first << " r/c: "
             << (it->second).row << "/" << (it->second).col << endl;
    }*/
    cout << endl << endl;
    cout << "███████╗██╗██████╗ ███████╗██╗     ██╗██╗   ██╗███████╗        ██████╗ ███████╗███╗   ██╗ ██████╗" << endl <<
            "██╔════╝██║██╔══██╗██╔════╝██║     ██║██║   ██║██╔════╝        ██╔══██╗██╔════╝████╗  ██║██╔════╝" << endl <<
            "███████╗██║██████╔╝█████╗  ██║     ██║██║   ██║███████╗        ██████╔╝█████╗  ██╔██╗ ██║██║  ███╗" << endl <<
            "╚════██║██║██╔══██╗██╔══╝  ██║     ██║██║   ██║╚════██║        ██╔═══╝ ██╔══╝  ██║╚██╗██║██║   ██║" << endl <<
            "███████║██║██████╔╝███████╗███████╗██║╚██████╔╝███████║        ██║     ███████╗██║ ╚████║╚██████╔╝" << endl <<
            "╚══════╝╚═╝╚═════╝ ╚══════╝╚══════╝╚═╝ ╚═════╝ ╚══════╝        ╚═╝     ╚══════╝╚═╝  ╚═══╝ ╚═════╝"  << endl;
    cout << endl << "\033[1;35m> Welcome to Sibelius' matrix toolkit <\033[0m" << endl;
    cout << endl << "\033[1;1m- Now you can type your command ('help' for help manual)\033[0m" << endl;
    string cmd;
    while (!cin.eof() && cmd != "quit" && cmd != "q") {
        cin >> cmd;
        if (cmd == "clear") {
            cout << "\033[2J\033[1;1H"; // clear the screen
        } else if (cmd == "help") {
            cout << endl << "\033[1;7m> Short Help Page <\033[0m" << endl;
            cout << "\033[1;1mhelp\033[0m: help page" << endl;
            cout << "\033[1;1mclear\033[0m: clear the page" << endl;
            cout << "\033[1;1mread-matrix\033[0m: input a matrix" << endl;
            cout << "\033[1;1mls\033[0m: list all current matrices that were inputted" << endl;
            cout << endl; // the end of help page
        }
        cout << "\033[1;2mYour command is \033[0m" << cmd << endl;
    }
}

