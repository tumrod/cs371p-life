#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "gtest/gtest.h"
#include "Life.h"

using namespace std;

// ------------
// AbstractCell
// ------------
// AbstractCell::AbstractCell(){
//     _alived = false;
// }

AbstractCell::AbstractCell(bool alived){
    _alived = alived;
}


//AbstractCell::AbstractCell(const AbstractCell& rhs);
//AbstractCell::~AbstractCell();
//AbstractCell* AbstractCell::clone () const = 0;
//void AbstractCell::evolve();


// ----------
// ConwayCell
// ----------

ConwayCell::ConwayCell() : AbstractCell(false) {}

AbstractCell* ConwayCell::clone () {
    return new ConwayCell(*this);
}

void ConwayCell::update_state(string c) {
    _alived = (c == "*");
}

string ConwayCell::print(){
    if (_alived){
        return "*";
    }
    return ".";
}

int ConwayCell::count_neighbor(vector< vector<ConwayCell>> _grid, int row, int col) {
    int total = _grid[row][col-1].cnt() + _grid[row][col+1].cnt() \
                + _grid[row+1][col].cnt() + _grid[row-1][col].cnt() \
                + _grid[row+1][col-1].cnt() + _grid[row+1][col+1].cnt() \
                + _grid[row-1][col-1].cnt() + _grid[row-1][col+1].cnt();
    return total;
}

void ConwayCell::evolve(int num_neighbors) {
    if (!_alived && num_neighbors == 3)
        _alived = true;
    else if (_alived && (num_neighbors < 2 || num_neighbors > 3))
        _alived = false;
}

int ConwayCell::cnt() {
    if (_alived)
        return 1;
    else
        return 0;
}

// -----------
// FredkinCell
// -----------

FredkinCell::FredkinCell() : AbstractCell(false) {
    _age = -1;
}

AbstractCell* FredkinCell::clone () {
    return new FredkinCell(*this);
}

void FredkinCell::update_state(string c) {
    if (c == "-") {
        _alived = false;
        _age = -1;
    } else if (c == "0"){
        _alived = true;
        _age = 0;
    }
}
int FredkinCell::count_neighbor(vector< vector<FredkinCell>> _grid, int row, int col) {
    int total = _grid[row][col-1].cnt() + _grid[row][col+1].cnt() \
                + _grid[row+1][col].cnt() + _grid[row-1][col].cnt();
    return total;
}

string FredkinCell::print(){
    if (_alived){
        if (_age < 10)
            return std::to_string(_age);
        else
            return "+";
    }
    return "-";
}

void FredkinCell::evolve(int num_neighbors) {
    if (!_alived && (num_neighbors == 1 || num_neighbors == 3)) {
        _alived = true;
        _age = 0;
    }
    else if (_alived && (num_neighbors == 0 || num_neighbors == 2 || num_neighbors == 4)) {
        _alived = false;
        _age = -1;
    } else if (_alived && (num_neighbors == 1 || num_neighbors == 3 || num_neighbors == 5)) {
        ++_age;
    }  
}

int FredkinCell::cnt() {
    if (_alived)
        return 1;
    else
        return 0;
}

// ----
// Cell
// ----
// Cell::Cell();
// Cell::Cell(const Cell& rhs);
// Cell::~Cell();



// ----
// Life
// ----

