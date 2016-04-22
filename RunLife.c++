// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2016
// Glenn P. Downing
// -------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include "Life.h"
#include <vector>
// ----
// main
// ----

int main () {
    using namespace std;
    string s;
    string perlife;
    vector<string> input;
    while(!cin.eof() ) {
        getline(cin, s);
        perlife += s;
        if (s == "") {
            input.push_back(perlife);
            perlife = "";
        }
    }

    // ----------------------
    // Life<ConwayCell> 21x13
    // ----------------------

    cout << "*** Life<ConwayCell> 21x13 ***" << endl;
    /*
    Simulate 12 evolutions.
    Print every grid (i.e. 0, 1, 2, 3, ... 12)
    */
    Life<ConwayCell> l(21, 13);
    l.add_grid(input[0]);
    l.simulate(12);

    // ----------------------
    // Life<ConwayCell> 20x29
    // ----------------------

    cout << "*** Life<ConwayCell> 20x29 ***" << endl;
    /*
    Simulate 28 evolutions.
    Print every 4th grid (i.e. 0, 4, 8, ... 28)
    */
    Life<ConwayCell> l2(20, 29);
    l2.add_grid(input[1]);
    l2.simulate(28, 0, true, 4, 0, 0);

    // -----------------------
    // Life<ConwayCell> 109x69
    // -----------------------

    cout << "*** Life<ConwayCell> 109x69 ***" << endl;
    /*
    Simulate 283 evolutions.
    Print the first 10 grids (i.e. 0, 1, 2, ... 9).
    Print the 283rd grid.
    Simulate 40 evolutions.
    Print the 323rd grid.
    Simulate 2177 evolutions.
    Print the 2500th grid.
    */

    Life<ConwayCell> l3(109, 69);
    // cout << input[2];
    l3.add_grid(input[2]);
    l3.simulate(283, 283, true, 1, 1, 10);
    l3.simulate(40, 323, false, 1, 0, 0);
    l3.simulate(2177, 2500, false, 1, 0, 0);

    // -----------------------
    // Life<FredkinCell> 20x20
    // -----------------------

    cout << "*** Life<FredkinCell> 20x20 ***" << endl;
    /*
    Simulate 5 evolutions.
    Print every grid (i.e. 0, 1, 2, ... 5)
    */
    Life<FredkinCell> l4(20, 20);
    l4.add_grid(input[3]);
    l4.simulate(5);

    // ----------------
    // Life<Cell> 20x20
    // ----------------

    cout << "*** Life<Cell> 20x20 ***" << endl;

    /*
    Simulate 5 evolutions.
    Print every grid (i.e. 0, 1, 2, ... 5)
    */
    Life<Cell> l5(20, 20);
    l5.add_grid(input[4]);
    l5.simulate(5);
    
    return 0;}
