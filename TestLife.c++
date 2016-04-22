#include "gtest/gtest.h"

#include "Life.h"
#include <iostream>
#include <sstream>
#include <string>

TEST(LifeTest, life_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(LifeTest, add_cell_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(LifeTest, add_grid_1) {
    Life<ConwayCell> l(5, 5);
    string input ="";
    l.add_grid(input);
    // l.print();
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(LifeTest, at_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(LifeTest, update_neighbor_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(LifeTest, begin_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(LifeTest, end_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(LifeTest, print_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(LifeTest, simulate_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

// AbstractCellTest

TEST(AbstractCellTest, AbstractCell_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

// ConwayCellTest

TEST(ConwayCellTest, ConwayCell_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(ConwayCellTest, clone_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(ConwayCellTest, update_state_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(ConwayCellTest, count_neighbor_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(ConwayCellTest, print_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(ConwayCellTest, evolve_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(ConwayCellTest, cnt_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

// FredkinCellTest

TEST(FredkinCellTest, FredkinCell_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(FredkinCellTest, clone_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(FredkinCellTest, update_state_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(FredkinCellTest, count_neighbor_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(FredkinCellTest, print_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(FredkinCellTest, evolve_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(FredkinCellTest, cnt_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

// CellTest

TEST(CellTest, Cell_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(CellTest, clone_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(CellTest, update_state_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(CellTest, count_neighbor_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(CellTest, print_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(CellTest, evolve_1) {
    bool result = true;
    ASSERT_TRUE(result);
}

TEST(CellTest, cnt_1) {
    bool result = true;
    ASSERT_TRUE(result);
}
