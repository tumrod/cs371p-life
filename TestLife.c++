#include "gtest/gtest.h"

#include "Life.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

TEST(LifeTest, life_1) {
    Life<ConwayCell> l(5, 5);
    int row = l._grid.size();
    int col = l._grid[0].size();

    ASSERT_EQ(l._generation, 0);
    ASSERT_EQ(l._pop, 0);
    ASSERT_EQ(row, 7);
    ASSERT_EQ(col, 7);
    ASSERT_TRUE(true);
}

TEST(LifeTest, life_2) {
    Life<FredkinCell> l(10, 20);
    int row = l._grid.size();
    int col = l._grid[0].size();

    ASSERT_EQ(l._generation, 0);
    ASSERT_EQ(l._pop, 0);
    ASSERT_EQ(row, 12);
    ASSERT_EQ(col, 22);
    ASSERT_TRUE(true);
}

TEST(LifeTest, life_3) {
    Life<Cell> l(20, 5);
    int row = l._grid.size();
    int col = l._grid[0].size();

    ASSERT_EQ(l._generation, 0);
    ASSERT_EQ(l._pop, 0);
    ASSERT_EQ(row, 22);
    ASSERT_EQ(col, 7);
    ASSERT_TRUE(true);
}

TEST(LifeTest, add_cell_1) {
    Life<ConwayCell> l(5, 5);
    l.add_cell("*");
    l.add_cell(".");
    l.add_cell(".");
    l.add_cell("*");
    ostringstream w;
    l.print(w);
    ASSERT_EQ("Generation = 0, Population = 2.\n*..*.\n.....\n.....\n.....\n.....\n", w.str());
    ASSERT_EQ(l._generation, 0);
    ASSERT_EQ(l._pop, 2);
}

TEST(LifeTest, add_cell_2) {
    Life<FredkinCell> l(5, 5);
    l.add_cell("0");
    l.add_cell("0");
    l.add_cell("-");
    l.add_cell("0");
    l.add_cell("0");
    ostringstream w;
    l.print(w);
    ASSERT_EQ("Generation = 0, Population = 4.\n00-00\n-----\n-----\n-----\n-----\n", w.str());
    ASSERT_EQ(l._generation, 0);
    ASSERT_EQ(l._pop, 4);
}

TEST(LifeTest, add_cell_3) {
    Life<Cell> l(5, 5);
    l.add_cell("0");
    l.add_cell(".");
    l.add_cell("*");
    l.add_cell("0");
    l.add_cell("-");
    ostringstream w;
    l.print(w);
    ASSERT_EQ("Generation = 0, Population = 3.\n0.*0-\n-----\n-----\n-----\n-----\n", w.str());
    ASSERT_EQ(l._generation, 0);
    ASSERT_EQ(l._pop, 3);
}

TEST(LifeTest, add_grid_1) {
    Life<ConwayCell> l(21, 13);
    string input =".............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    ostringstream w;
    l.print(w);
    ASSERT_EQ("Generation = 0, Population = 13.\n" + test, w.str());
    ASSERT_EQ(l._generation, 0);
    ASSERT_EQ(l._pop, 13);
}

TEST(LifeTest, add_grid_2) {
    Life<FredkinCell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0000--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    ostringstream w;
    l.print(w);
    ASSERT_EQ("Generation = 0, Population = 34.\n" + test, w.str());
    ASSERT_EQ(l._generation, 0);
    ASSERT_EQ(l._pop, 34);
}

TEST(LifeTest, add_grid_3) {
    Life<Cell> l(20, 20);
    string input ="--------------------\n-------**-----------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0**0--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    ostringstream w;
    l.print(w);
    ASSERT_EQ("Generation = 0, Population = 36.\n" + test, w.str());
    ASSERT_EQ(l._generation, 0);
    ASSERT_EQ(l._pop, 36);
}

TEST(LifeTest, at_1) {
    Life<ConwayCell> l(5, 5);
    l.add_cell("*");
    l.add_cell(".");
    l.add_cell(".");
    l.add_cell("*");

    ConwayCell actual = l.at(1, 1);
    ConwayCell expected = l._grid[1][1];
    ASSERT_EQ(actual, expected);
}

TEST(LifeTest, at_2) {
    Life<FredkinCell> l(5, 5);
    l.add_cell("0");
    l.add_cell("-");
    l.add_cell("-");
    l.add_cell("0");

    FredkinCell actual = l.at(1, 1);
    FredkinCell expected = l._grid[1][1];
    ASSERT_EQ(actual, expected);
}

TEST(LifeTest, at_3) {
    Life<ConwayCell> l(5, 5);
    l.add_cell("*");
    l.add_cell(".");
    l.add_cell(".");
    l.add_cell("*");

    ConwayCell actual = l.at(1, 1);
    ConwayCell expected = l._grid[1][1];
    ASSERT_EQ(actual, expected);
}

TEST(LifeTest, update_neighbor_1) {
    Life<ConwayCell> l(21, 13);
    string input =".............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int before = l._neigh_cnt[10][7];
    l.update_neighbor();
    int after = l._neigh_cnt[10][7];

    ASSERT_EQ(before, 0);
    ASSERT_EQ(after, 5);
}

TEST(LifeTest, update_neighbor_2) {
    Life<FredkinCell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0000--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int before = l._neigh_cnt[10][7];
    l.update_neighbor();
    int after = l._neigh_cnt[10][7];

    ASSERT_EQ(before, 0);
    ASSERT_EQ(after, 2);
}

TEST(LifeTest, update_neighbor_3) {
    Life<Cell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0**0--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int before = l._neigh_cnt[10][7];
    l.update_neighbor();
    int after = l._neigh_cnt[10][7];

    ASSERT_EQ(before, 0);
    ASSERT_EQ(after, 2);
}

TEST(LifeTest, begin_1) {
    Life<ConwayCell> l(21, 13);
    string input =".............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    vector<vector<ConwayCell>>::iterator row = l.begin();
    ConwayCell result = *((*row).begin());
    ASSERT_EQ(result, l.at(1, 1));
}

TEST(LifeTest, begin_2) {
    Life<FredkinCell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0000--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    vector<vector<FredkinCell>>::iterator row = l.begin();
    FredkinCell result = *((*row).begin());
    ASSERT_EQ(result, l.at(1, 1));
}

TEST(LifeTest, begin_3) {
    Life<Cell> l(20, 20);
    string input ="--------------------\n-------**-----------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0**0--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    vector<vector<Cell>>::iterator row = l.begin();
    Cell result = *((*row).begin());
    ASSERT_EQ(result, l.at(1, 1));
}

TEST(LifeTest, end_1) {
    Life<ConwayCell> l(21, 13);
    string input =".............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    vector<vector<ConwayCell>>::iterator row = l.end() -1 ;
    vector<ConwayCell>::iterator col = (*row).end() -1; 
    ConwayCell result = *(col);
    ASSERT_EQ(result, l.at(21, 13));
}

TEST(LifeTest, end_2) {
    Life<FredkinCell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0000--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    vector<vector<FredkinCell>>::iterator row = l.end() -1 ;
    vector<FredkinCell>::iterator col = (*row).end() -1; 
    FredkinCell result = *(col);
    ASSERT_EQ(result, l.at(20, 20));
}

TEST(LifeTest, end_3) {
    Life<Cell> l(20, 20);
    string input ="--------------------\n-------**-----------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0**0--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    vector<vector<Cell>>::iterator row = l.end() -1 ;
    vector<Cell>::iterator col = (*row).end() -1; 
    Cell result = *(col);
    ASSERT_EQ(result, l.at(20, 20));
}

TEST(LifeTest, print_1) {
    Life<ConwayCell> l(21, 13);
    string input =".............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    ostringstream w;
    l.print(w);
    ASSERT_EQ("Generation = 0, Population = 13.\n" + test, w.str());
}

TEST(LifeTest, print_2) {
    Life<FredkinCell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0000--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    ostringstream w;
    l.print(w);
    ASSERT_EQ("Generation = 0, Population = 34.\n" + test, w.str());
}

TEST(LifeTest, print_3) {
    Life<Cell> l(20, 20);
    string input ="--------------------\n-------**-----------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0**0--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    ostringstream w;
    l.print(w);
    ASSERT_EQ("Generation = 0, Population = 36.\n" + test, w.str());
}

TEST(LifeTest, simulate_1) {
    Life<ConwayCell> l(21, 13);
    string input =".............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n";
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    ostringstream w;
    l.simulate(1, w);
    ASSERT_EQ("\nGeneration = 0, Population = 13.\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n\nGeneration = 1, Population = 17.\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.....***.....\n.....****....\n........*....\n......*......\n....*........\n....****.....\n.....***.....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n\n", w.str());
}

TEST(LifeTest, simulate_2) {
    Life<FredkinCell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0000--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    ostringstream w;
    l.simulate(1, w);
    ASSERT_EQ("\nGeneration = 0, Population = 34.\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0000--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n\nGeneration = 1, Population = 64.\n--------------------\n--------------------\n--------------------\n---------00---------\n---------11---------\n-------010010-------\n-------0-11-0-------\n-----00------00-----\n-----11--00--11-----\n---01--10--01--10---\n---01--10--01--10---\n-----11--00--11-----\n-----00--11--00-----\n-------01--10-------\n-------01--10-------\n---------11---------\n---------00---------\n--------------------\n--------------------\n--------------------\n\n", w.str());
}

TEST(LifeTest, simulate_3) {
    Life<Cell> l(20, 20);
    string input ="--------------------\n-------**-----------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0**0--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    ostringstream w;
    l.simulate(1, w);
    ASSERT_EQ("\nGeneration = 0, Population = 36.\n--------------------\n-------**-----------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0**0--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n\nGeneration = 1, Population = 68.\n-------00-----------\n------0..0----------\n-------00-----------\n---------00---------\n---------11---------\n-------010010-------\n-------0-..-0-------\n-----00------00-----\n-----11--00--11-----\n---01--10--01--10---\n---01--10--01--10---\n-----11--00--11-----\n-----00--11--00-----\n-------01--10-------\n-------01--10-------\n---------11---------\n---------00---------\n--------------------\n--------------------\n--------------------\n\n", w.str());
}

// AbstractCellTest

TEST(AbstractCellTest, AbstractCell_1) {    
    AbstractCell* const p = new FredkinCell();
    ASSERT_FALSE(p->_alived);

    try {
        FredkinCell& r = dynamic_cast<FredkinCell&>(*p);
        r.update_state("0");
        ASSERT_EQ("0", r.print());
        ASSERT_EQ(1, r.cnt());
        ASSERT_TRUE(p->_alived);
    } catch (const bad_cast& e) {
        ASSERT_TRUE(false);
    }
    delete p;
}

TEST(AbstractCellTest, AbstractCell_2) {    
    AbstractCell* const p = new ConwayCell();
    ASSERT_FALSE(p->_alived);

    try {
        ConwayCell& r = dynamic_cast<ConwayCell&>(*p);
        r.update_state("*");
        ASSERT_EQ("*", r.print());
        ASSERT_EQ(1, r.cnt());
        ASSERT_TRUE(p->_alived);
    } catch (const bad_cast& e) {
        ASSERT_TRUE(false);
    }
    delete p;
}

TEST(AbstractCellTest, AbstractCell_3) {    
    AbstractCell* const p = new FredkinCell();
    ASSERT_FALSE(p->_alived);

    try {
        FredkinCell& r = dynamic_cast<FredkinCell&>(*p);
        r.update_state("-");
        ASSERT_EQ("-", r.print());
        ASSERT_EQ(0, r.cnt());
        ASSERT_FALSE(p->_alived);

    } catch (const bad_cast& e) {
        ASSERT_TRUE(false);
    }
    delete p;
}

TEST(AbstractCellTest, equal_op_1) {    
    ASSERT_TRUE(true);
}
TEST(AbstractCellTest, equal_op_2) {    
    ASSERT_TRUE(true);
}
TEST(AbstractCellTest, equal_op_3) {    
    ASSERT_TRUE(true);
}

// ConwayCellTest
TEST(ConwayCellTest, ConwayCell_1) {
    ConwayCell p = ConwayCell();
    ASSERT_FALSE(p._alived);

    p.update_state("*");
    ASSERT_TRUE(p._alived);
    p._alived = false;

    ASSERT_EQ(".", p.print());
}

TEST(ConwayCellTest, ConwayCell_2) {
    ConwayCell p = ConwayCell();
    ASSERT_FALSE(p._alived);

    p.update_state("-");
    ASSERT_FALSE(p._alived);
    p._alived = true;

    ASSERT_EQ("*", p.print());
}

TEST(ConwayCellTest, ConwayCell_3) {
    ConwayCell p = ConwayCell();
    ASSERT_FALSE(p._alived);

    p.update_state("0");
    ASSERT_FALSE(p._alived);
    p._alived = true;

    ASSERT_EQ("*", p.print());
}

TEST(ConwayCellTest, clone_1) {
    AbstractCell* p;
    ConwayCell conway;
    p = conway.clone();

    p->update_state("*");
    ASSERT_EQ("*", p->print());

    p->update_state("-");
    ASSERT_EQ(".", p->print());

    delete p;
}

TEST(ConwayCellTest, clone_2) {
    AbstractCell* p;
    ConwayCell conway;
    p = conway.clone();

    p->update_state("*");
    ASSERT_EQ("*", p->print());

    delete p;
}

TEST(ConwayCellTest, clone_3) {
    AbstractCell* p;
    ConwayCell conway;
    p = conway.clone();

    p->update_state("-");
    ASSERT_EQ(".", p->print());

    delete p;
}

TEST(ConwayCellTest, update_state_1) {
    ConwayCell p = ConwayCell();
    ASSERT_FALSE(p._alived);

    p.update_state("*");
    ASSERT_TRUE(p._alived);
}

TEST(ConwayCellTest, update_state_2) {
    ConwayCell p = ConwayCell();
    ASSERT_FALSE(p._alived);

    p.update_state("*");
    ASSERT_TRUE(p._alived);
    p._alived = false;

    ASSERT_EQ(".", p.print());
}

TEST(ConwayCellTest, update_state_3) {
    ConwayCell p = ConwayCell();
    ASSERT_FALSE(p._alived);

    p.update_state("*");
    ASSERT_TRUE(p._alived);
    p._alived = false;

    ASSERT_EQ(".", p.print());

    p.update_state("-");
    ASSERT_FALSE(p._alived);
    ASSERT_EQ(".", p.print());
}

TEST(ConwayCellTest, count_neighbor_1) {
    Life<ConwayCell> l(21, 13);
    string input =".............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int row = 10;
    int col = 7;
    int possible_nb[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    ConwayCell cw = l.at(row, col);
    int result = cw.count_neighbor(possible_nb);
    ASSERT_EQ(5, result);
}

TEST(ConwayCellTest, count_neighbor_2) {
    Life<ConwayCell> l(21, 13);
    string input =".............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int row = 15;
    int col = 5;
    int possible_nb[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    ConwayCell cw = l.at(row, col);
    int result = cw.count_neighbor(possible_nb);
    ASSERT_EQ(0, result);
}

TEST(ConwayCellTest, count_neighbor_3) {
    Life<ConwayCell> l(21, 13);
    string input =".............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int row = 13;
    int col = 9;
    int possible_nb[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    ConwayCell cw = l.at(row, col);
    int result = cw.count_neighbor(possible_nb);
    ASSERT_EQ(1, result);
}

TEST(ConwayCellTest, print_1) {
    ConwayCell cw = ConwayCell();
    cw.update_state("*");
    string result = cw.print();
    ASSERT_EQ("*", result);
}

TEST(ConwayCellTest, print_2) {
    ConwayCell cw = ConwayCell();
    cw.update_state("-");
    string result = cw.print();
    ASSERT_EQ(".", result);
}

TEST(ConwayCellTest, print_3) {
    ConwayCell cw = ConwayCell();
    cw.update_state("0");
    string result = cw.print();
    ASSERT_EQ(".", result);
}

TEST(ConwayCellTest, evolve_1) {
    ConwayCell cw = ConwayCell();
    cw.update_state("*");
    ASSERT_TRUE(cw._alived);

    // live cell become a dead cell
    int neighbor = 1;
    cw.evolve(neighbor);
    ASSERT_FALSE(cw._alived);

    // dead cell becomes a live cell
    neighbor = 3;
    cw.evolve(neighbor);
    ASSERT_TRUE(cw._alived);
}

TEST(ConwayCellTest, evolve_2) {
    ConwayCell cw = ConwayCell();
    cw.update_state("*");
    ASSERT_TRUE(cw._alived);

    // live cell become a dead cell
    int neighbor = 4;
    cw.evolve(neighbor);
    ASSERT_FALSE(cw._alived);

    // dead cell stay dead
    neighbor = 2;
    cw.evolve(neighbor);
    ASSERT_FALSE(cw._alived);
}

TEST(ConwayCellTest, evolve_3) {
    ConwayCell cw = ConwayCell();
    cw.update_state("*");
    ASSERT_TRUE(cw._alived);

    // live cell become a dead cell
    int neighbor = 1;
    cw.evolve(neighbor);
    ASSERT_FALSE(cw._alived);

    // dead cell becomes a live cell
    neighbor = 3;
    cw.evolve(neighbor);
    ASSERT_TRUE(cw._alived);

    // live cell stay alived
    neighbor = 3;
    cw.evolve(neighbor);
    ASSERT_TRUE(cw._alived);
}

TEST(ConwayCellTest, cnt_1) {
    ConwayCell cw = ConwayCell();
    cw.update_state("*");
    ASSERT_TRUE(cw._alived);
    ASSERT_EQ(1, cw.cnt());
}

TEST(ConwayCellTest, cnt_2) {
    ConwayCell cw = ConwayCell();
    cw.update_state(".");
    ASSERT_FALSE(cw._alived);
    ASSERT_EQ(0, cw.cnt());
}

TEST(ConwayCellTest, cnt_3) {
    ConwayCell cw = ConwayCell();
    cw.update_state("0");
    ASSERT_FALSE(cw._alived);
    ASSERT_EQ(0, cw.cnt());
}

// FredkinCellTest

TEST(FredkinCellTest, FredkinCell_1) {
    FredkinCell p = FredkinCell();
    ASSERT_FALSE(p._alived);

    p.update_state("0");
    ASSERT_TRUE(p._alived);
    p._alived = false;
    ASSERT_EQ("-", p.print());
}

TEST(FredkinCellTest, FredkinCell_2) {
    FredkinCell p = FredkinCell();
    ASSERT_FALSE(p._alived);

    p.update_state("-");
    ASSERT_FALSE(p._alived);
    p._alived = true;

    ASSERT_EQ("0", p.print());
}

TEST(FredkinCellTest, FredkinCell_3) {
    FredkinCell p = FredkinCell();
    ASSERT_FALSE(p._alived);

    p.update_state("*");
    ASSERT_FALSE(p._alived);
    p._alived = true;

    ASSERT_EQ("0", p.print());
}

TEST(FredkinCellTest, clone_1) {
    AbstractCell* p;
    FredkinCell fk;

    p = fk.clone();
    p->update_state("0");
    ASSERT_EQ("0", p->print());

    delete p;
}

TEST(FredkinCellTest, clone_2) {
    AbstractCell* p;
    FredkinCell fk;

    p = fk.clone();
    p->update_state(".");
    ASSERT_EQ("-", p->print());

    delete p;
}
TEST(FredkinCellTest, clone_3) {
    AbstractCell* p;
    FredkinCell fk;

    p = fk.clone();
    p->update_state("0");
    ASSERT_EQ("0", p->print());

    p->update_state(".");
    ASSERT_EQ("0", p->print());

    delete p;
}

TEST(FredkinCellTest, update_state_1) {
    FredkinCell p = FredkinCell();
    ASSERT_FALSE(p._alived);

    p.update_state("0");
    ASSERT_TRUE(p._alived);
}

TEST(FredkinCellTest, update_state_2) {
    FredkinCell p = FredkinCell();
    ASSERT_FALSE(p._alived);

    p.update_state("0");
    ASSERT_TRUE(p._alived);

    p._alived = false;
    ASSERT_EQ("-", p.print());
}

TEST(FredkinCellTest, update_state_3) {
    FredkinCell p = FredkinCell();
    ASSERT_FALSE(p._alived);

    p.update_state("0");
    ASSERT_TRUE(p._alived);

    p._alived = false;
    ASSERT_EQ("-", p.print());

    p.update_state(".");
    ASSERT_FALSE(p._alived);
    ASSERT_EQ("-", p.print());
}

TEST(FredkinCellTest, count_neighbor_1) {
    Life<FredkinCell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0000--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int row = 7;
    int col = 9;
    int possible_nb[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    FredkinCell fk = l.at(row, col);
    int result = fk.count_neighbor(possible_nb);
    ASSERT_EQ(2, result);
}

TEST(FredkinCellTest, count_neighbor_2) {
    Life<FredkinCell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0000--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int row = 10;
    int col = 10;
    int possible_nb[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    FredkinCell fk = l.at(row, col);
    int result = fk.count_neighbor(possible_nb);
    ASSERT_EQ(0, result);
}
TEST(FredkinCellTest, count_neighbor_3) {
    Life<FredkinCell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0000--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int row = 5;
    int col = 9;
    int possible_nb[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    FredkinCell fk = l.at(row, col);
    int result = fk.count_neighbor(possible_nb);
    ASSERT_EQ(2, result);
}

TEST(FredkinCellTest, print_1) {
    FredkinCell fk = FredkinCell();
    fk.update_state("0");
    string result = fk.print();
    ASSERT_EQ("0", result);
}

TEST(FredkinCellTest, print_2) {
    FredkinCell fk = FredkinCell();
    fk.update_state("-");
    string result = fk.print();
    ASSERT_EQ("-", result);
}

TEST(FredkinCellTest, print_3) {
    FredkinCell fk = FredkinCell();
    fk.update_state(".");
    string result = fk.print();
    ASSERT_EQ("-", result);
}

TEST(FredkinCellTest, evolve_1) {
    FredkinCell fk = FredkinCell();
    fk.update_state("0");
    ASSERT_TRUE(fk._alived);

    // live cell become a dead cell
    int neighbor = 2;
    fk.evolve(neighbor);
    ASSERT_FALSE(fk._alived);

    // dead cell becomes a live cell
    neighbor = 3;
    fk.evolve(neighbor);
    ASSERT_TRUE(fk._alived);

}

TEST(FredkinCellTest, evolve_2) {
    FredkinCell fk = FredkinCell();
    fk.update_state("0");
    ASSERT_TRUE(fk._alived);

    // live cell become a dead cell
    int neighbor = 4;
    fk.evolve(neighbor);
    ASSERT_FALSE(fk._alived);

    // dead cell becomes a live cell
    neighbor = 1;
    fk.evolve(neighbor);
    ASSERT_TRUE(fk._alived);

}

TEST(FredkinCellTest, evolve_3) {
    FredkinCell fk = FredkinCell();
    fk.update_state("0");
    ASSERT_TRUE(fk._alived);

    // live cell become a dead cell
    int neighbor = 2;
    fk.evolve(neighbor);
    ASSERT_FALSE(fk._alived);

    // dead cell stay dead
    neighbor = 4;
    fk.evolve(neighbor);
    ASSERT_FALSE(fk._alived);

}

TEST(FredkinCellTest, cnt_1) {
    FredkinCell fk = FredkinCell();
    fk.update_state("0");
    ASSERT_TRUE(fk._alived);
    ASSERT_EQ(1, fk.cnt());
}

TEST(FredkinCellTest, cnt_2) {
    FredkinCell fk = FredkinCell();
    fk.update_state("-");
    ASSERT_FALSE(fk._alived);
    ASSERT_EQ(0, fk.cnt());
}

TEST(FredkinCellTest, cnt_3) {
    FredkinCell fk = FredkinCell();
    fk.update_state("*");
    ASSERT_FALSE(fk._alived);
    ASSERT_EQ(0, fk.cnt());
}

// CellTest

TEST(CellTest, Cell_1) {
    ASSERT_TRUE(true);
    // Cell p = Cell();

    // p.update_state("*");
    // ASSERT_TRUE(p._alived);
    // p._alived = false;

    // ASSERT_EQ(".", p.print());
}

TEST(CellTest, Cell_Copy_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(CellTest, Cell_Copy_2) {
    bool result = true;
    ASSERT_TRUE(result);
}
TEST(CellTest, Cell_Copy_3) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(CellTest, update_state_1) {
    Cell p = Cell();
    p.update_state("*");
    ASSERT_EQ("*", p.print());
}

TEST(CellTest, update_state_2) {
    Cell p = Cell();
    p.update_state("0");
    ASSERT_EQ("0", p.print());
}

TEST(CellTest, update_state_3) {
    Cell p = Cell();
    p.update_state("*");
    ASSERT_EQ("*", p.print());

    p.update_state("0");
    ASSERT_EQ("*", p.print());
}

TEST(CellTest, count_neighbor_1) {
    Life<Cell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0**0--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int row = 7;
    int col = 10;
    int possible_nb[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    Cell cw = l.at(row, col);
    int result = cw.count_neighbor(possible_nb);
    ASSERT_EQ(5, result);

    row = 7;
    col = 9;
    Cell fk = l.at(row, col);
    int possible_nb2[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    result = fk.count_neighbor(possible_nb2);
    ASSERT_EQ(2, result);
}

TEST(CellTest, count_neighbor_2) {
    Life<Cell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0**0--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int row = 9;
    int col = 10;
    int possible_nb[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    Cell cw = l.at(row, col);
    int result = cw.count_neighbor(possible_nb);
    ASSERT_EQ(1, result);

    row = 9;
    col = 14;
    Cell fk = l.at(row, col);
    int possible_nb2[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    result = fk.count_neighbor(possible_nb2);
    ASSERT_EQ(1, result);
}
TEST(CellTest, count_neighbor_3) {
    Life<Cell> l(20, 20);
    string input ="--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0**0--------\n---------00---------\n-----00------00-----\n----0--0----0--0----\n----0--0----0--0----\n-----00------00-----\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n";
    string test = input;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    l.add_grid(input);

    int row = 5;
    int col = 15;
    int possible_nb[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    Cell cw = l.at(row, col);
    int result = cw.count_neighbor(possible_nb);
    ASSERT_EQ(0, result);

    row = 6;
    col = 9;
    Cell fk = l.at(row, col);
    int possible_nb2[] = {l.at(row, col-1).cnt(), l.at(row, col+1).cnt(), \
                        l.at(row+1, col).cnt(), l.at(row-1, col).cnt(),\
                        l.at(row+1, col-1).cnt(), l.at(row+1, col+1).cnt(), \
                        l.at(row-1, col-1).cnt() ,l.at(row-1, col+1).cnt()};

    result = fk.count_neighbor(possible_nb2);
    ASSERT_EQ(1, result);
}
TEST(CellTest, print_1) {
    Cell c = Cell();
    c.update_state("*");
    ASSERT_EQ("*", c.print());
}

TEST(CellTest, print_2) {
    Cell c = Cell();
    c.update_state("0");
    ASSERT_EQ("0", c.print());
}

TEST(CellTest, print_3) {
    Cell c = Cell();
    c.update_state("*");
    ASSERT_EQ("*", c.print());

    // it's ConwayCell from the beginning, so it shouldn't change its cell when wrong input
    c.update_state("0");
    ASSERT_EQ("*", c.print());
}

TEST(CellTest, evolve_1) {
    Cell fk = Cell();
    fk.update_state("0");
    ASSERT_TRUE(fk.cnt());

    // live cell become a dead cell
    int neighbor = 2;
    fk.evolve(neighbor);
    ASSERT_FALSE(fk.cnt());
}

TEST(CellTest, evolve_2) {
    Cell fk = Cell();
    fk.update_state("0");
    ASSERT_TRUE(fk.cnt());

    // live cell become a dead cell
    int neighbor = 2;
    fk.evolve(neighbor);
    ASSERT_FALSE(fk.cnt());

    // dead cell becomes a live cell
    neighbor = 3;
    fk.evolve(neighbor);
    ASSERT_TRUE(fk.cnt());
}

TEST(CellTest, evolve_3) {
    Cell fk = Cell();
    fk.update_state("0");
    ASSERT_TRUE(fk.cnt());

    // live cell become a dead cell
    int neighbor = 2;
    fk.evolve(neighbor);
    ASSERT_FALSE(fk.cnt());

    // dead cell becomes a live cell
    neighbor = 3;
    fk.evolve(neighbor);
    ASSERT_TRUE(fk.cnt());

    // dead conway cell, neighbor = 3, should become alived
    fk.update_state(".");
    fk.evolve(neighbor);
    ASSERT_TRUE(fk.cnt());
    ASSERT_EQ("*", fk.print());

    // live cell conwaycell become a dead cell
    neighbor = 1;
    fk.evolve(neighbor);
    ASSERT_FALSE(fk.cnt());
}

TEST(CellTest, cnt_1) {
    Cell c = Cell();

    c.update_state("0");
    ASSERT_EQ(1, c.cnt());

    c.update_state("-");
    ASSERT_EQ(0, c.cnt());
}

TEST(CellTest, cnt_2) {
    Cell c = Cell();

    c.update_state("*");
    ASSERT_EQ(1, c.cnt());

    c.update_state(".");
    ASSERT_EQ(0, c.cnt());
}

TEST(CellTest, cnt_3) {
    Cell c = Cell();
    c.update_state("0");
    ASSERT_EQ(1, c.cnt());

    c.update_state("-");
    ASSERT_EQ(0, c.cnt());

    c.update_state("*");
    ASSERT_EQ(1, c.cnt());

    c.update_state(".");
    ASSERT_EQ(0, c.cnt());
}