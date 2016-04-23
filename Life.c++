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

AbstractCell::AbstractCell(bool alived){
    _alived = alived;
}

bool AbstractCell::operator == (const AbstractCell& rhs) const {
    return (_alived == rhs._alived);
}

// ----------
// ConwayCell
// ----------

ConwayCell::ConwayCell() : AbstractCell(false) {}

AbstractCell* ConwayCell::clone () const{
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

int ConwayCell::count_neighbor(int possible_nb[]) const{
    return possible_nb[0]+possible_nb[1]+ possible_nb[2]+possible_nb[3]+ possible_nb[4]+possible_nb[5]+ possible_nb[6]+possible_nb[7];
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

bool ConwayCell::operator== (const ConwayCell& rhs) const {
    if (const ConwayCell* const p = dynamic_cast<const ConwayCell*>(&rhs))
        return AbstractCell::operator==(*p);
    return false;
}

// -----------
// FredkinCell
// -----------

FredkinCell::FredkinCell() : AbstractCell(false) {
    _age = 0;
}

AbstractCell* FredkinCell::clone () const{
    return new FredkinCell(*this);
}

void FredkinCell::update_state(string c) {
    if (c == "-") {
        _alived = false;
        _age = 0;
    } else if (c == "0"){
        _alived = true;
        _age = 0;
    }
}

int FredkinCell::count_neighbor(int possible_nb[]) const{
    return possible_nb[0]+possible_nb[1]+ possible_nb[2]+possible_nb[3];
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
    if (!_alived && (num_neighbors == 1 || num_neighbors == 3))
        _alived = true;
    else if (_alived && (num_neighbors == 0 || num_neighbors == 2 || num_neighbors == 4))
        _alived = false;
    else if (_alived && (num_neighbors == 1 || num_neighbors == 3 || num_neighbors == 5))
        ++_age;
}

int FredkinCell::cnt() {
    if (_alived)
        return 1;
    else
        return 0;
}

bool FredkinCell::operator== (const FredkinCell& rhs) const {
    if (const FredkinCell* const p = dynamic_cast<const FredkinCell*>(&rhs))
        return AbstractCell::operator==(*p) && _age==rhs._age;
    return false;
}

// ----
// Cell
// ----

Cell::Cell() {
    FredkinCell fk;
    _p = fk.clone();
}

Cell::Cell (const Cell& rhs) {
    if (!rhs._p)
        _p = 0;
    else
        _p = rhs._p->clone();
}

Cell::~Cell () {
    delete _p;
}

void Cell::update_state(string c) {
    if ((c == "-") || (c == "0")){
        if (FredkinCell* const fk = dynamic_cast<FredkinCell*>(_p))
            fk->update_state(c);
    } else if ((c == "*") || (c == ".")){
        if (ConwayCell* cw = dynamic_cast<ConwayCell*>(_p)) {
            cw->update_state(c);
        } else {
            delete _p;
            ConwayCell conway;
            _p = conway.clone();
            _p->update_state(c);
        }       
    }
}

int Cell::count_neighbor(int possible_nb[]) const{
    if (FredkinCell* const fk = dynamic_cast<FredkinCell*>(_p)){
        return fk->count_neighbor(possible_nb);
    } else if (ConwayCell* const cw = dynamic_cast<ConwayCell*>(_p)){
        return cw->count_neighbor(possible_nb);
    }
    return 0;
}

string Cell::print(){
    if (FredkinCell* const fk = dynamic_cast<FredkinCell*>(_p)){
        return fk->print();
    } else if (ConwayCell* const cw = dynamic_cast<ConwayCell*>(_p)){
        return cw->print();
    }
    return "";
}

int Cell::cnt() {
    if (FredkinCell* const fk = dynamic_cast<FredkinCell*>(_p)){
        return fk->cnt();
    } else if (ConwayCell* const cw = dynamic_cast<ConwayCell*>(_p)){
        return cw->cnt();
    }
    return 0;
}

void Cell::evolve(int num_neighbors) {
    if (FredkinCell* const fk = dynamic_cast<FredkinCell*>(_p)) {
        fk->evolve(num_neighbors);
        if(fk->print() == "2") {
            delete _p;
            ConwayCell conway;
            _p = conway.clone();
            _p->update_state("*");
        }
    } else if (ConwayCell* const cw = dynamic_cast<ConwayCell*>(_p))
        cw->evolve(num_neighbors);
}

bool Cell::operator== (const Cell& rhs) const {
    if (!_p && !rhs._p)
        return true;
    if (!_p || !rhs._p)
        return false;
    return (*_p == *(rhs._p));
}

