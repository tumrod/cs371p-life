#ifndef Life_h
#define Life_h

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "gtest/gtest.h"

using namespace std;

template <class T>
class Life{
	friend class LifeTest;

  	public:
		typedef T                 value_type;

		typedef value_type*       pointer;
		typedef const value_type* const_pointer;

		typedef value_type&       reference;
		typedef const value_type& const_reference;

	private:
		vector< vector<value_type> > _grid;
		vector< vector<int> > _neigh_cnt;
		int _generation;
		int _r;
		int _c;
		int _pop;


		void update_neighbor(){
			_pop = 0;
			vector< vector<int> > temp_neighbor = _neigh_cnt;
			for(int row = 1; row < (int)_grid.size()-1; ++row) {
				for(int col = 1; col < _grid[0].size()-1; ++col) {
					int possible_nb[] = {_grid[row][col-1].cnt(), _grid[row][col+1].cnt(), \
						_grid[row+1][col].cnt(), _grid[row-1][col].cnt(),\
						_grid[row+1][col-1].cnt(), _grid[row+1][col+1].cnt(), \
						_grid[row-1][col-1].cnt() ,_grid[row-1][col+1].cnt()};

					_neigh_cnt[row][col] = _grid[row][col].count_neighbor(possible_nb);
					_pop += _grid[row][col].cnt();         
				}
			}
		}

	public:

		// -----------
		// Constructor
		// -----------

		/**
		 * @param		string input
		 */
		Life<value_type> (int row, int col) {
			_grid.resize(row+2, vector<value_type> (col+2, value_type()));
			_neigh_cnt.resize(row+2, vector<int> (col+2, 0));
			_r = 1;
			_c = 1;
			_pop = 0;
			_generation = 0;
		}

		// --------
		// add_cell
		// --------

		/**
		 * @param		string input
		 */
		void add_cell(string s){
			int col = (int)_grid[0].size();
			if(_c == col-1){
				++_r;
				_c = 1;
			}
			_grid[_r][_c].update_state(s);
			_neigh_cnt[_r][_c] = _grid[_r][_c].cnt();
			_pop += (*this).at(_r, _c).cnt();
			++_c;
		}

		// --------
		// add_grid
		// --------

		/**
		 * @param		string input
		 */
		void add_grid(string input) {
			for (int i = 0; i < input.length(); ++i){
				stringstream ss;
				string s;
				char c = input[i];
				ss << c;
				ss >> s;
				add_cell(s);
			}

		}

		// --
		// at
		// --

		/**
		 * @param		int row, int column
		 * @return      object at the position row, col
		 */
		value_type& at(int r, int c){
			return _grid[r][c]; 
		}

		// -----
		// begin
		// -----

		/**
		 * @return       vector<vector<value_type>>::iterator
		 */
		typename vector<vector<value_type>>::iterator begin() {
			return _grid.begin();
		}

		// ---
		// end
		// ---

		/**
		 * @return       vector<vector<value_type>>::iterator
		 */
		typename vector<vector<value_type>>::iterator end() {
			return _grid.end();
		}

		// -----
		// print
		// -----

		/**
		 * @param       ostream& outputstream
		 */
		void print(ostream& w) {
			typename vector<vector<value_type>>::iterator row;
			typename vector<value_type>::iterator col;
			w << "Generation = " << _generation << ", Population = " << _pop << "." << endl;
			int r = 0;
			for(row = (*this).begin()+1; row != (*this).end()-1; ++row) {
				for(col = (*row).begin()+1; col != (*row).end()-1; ++col) {
					w <<(*col).print();
				}
				w << endl; 
				++r;
			}
		}

		// --------
		// simulate
		// --------

		/**
		 * @param       int evol : number of evolution
		 *				ostream& w : outputstream
		 *				int gen=0 : generation (for specific print)
		 *				bool original = true: include original board (generation 0)
		 *				int step = 1 : step size
		 *				int start=0 : starting point of printing
		 *				int end=0 : ending point of printing
		 */
		void simulate(int evol, ostream& w, int gen=0, bool original = true, int step = 1, int start=0, int end=0) {
			if(original) {
				w << endl;
				print(w);
			}

			for(int i = 1; i <= evol; ++i){
				++_generation;
				update_neighbor();
				_pop = 0;
				for(int row = 1; row < (int)_grid.size()-1; ++row) {
					for(int col = 1; col < _grid[0].size()-1; ++col) {
						int num_neigh = _neigh_cnt[row][col];
						_grid[row][col].evolve(num_neigh);
						_pop += _grid[row][col].cnt();
					}
				}
				if(gen && _generation == gen) {
					if (start != 0 && end != 0)
						w << endl;
					print(w);
				} else if(start < end && _generation == start) {	
					w << endl;
					print(w);
					++start;
				} else if(step > 1 && i%step == 0) {
					w << endl;
					print(w);
				} else if(step == 1 && gen == 0 && start == 0 && end == 0){
					w << endl;
					print(w);
				}
				if(i == evol)
					w << endl;
			}
		}

		FRIEND_TEST(LifeTest, life_1);
		FRIEND_TEST(LifeTest, life_2);
		FRIEND_TEST(LifeTest, life_3);
		FRIEND_TEST(LifeTest, add_cell_1);
		FRIEND_TEST(LifeTest, add_cell_2);
		FRIEND_TEST(LifeTest, add_cell_3);
		FRIEND_TEST(LifeTest, add_grid_1);
		FRIEND_TEST(LifeTest, add_grid_2);
		FRIEND_TEST(LifeTest, add_grid_3);
		FRIEND_TEST(LifeTest, at_1);
		FRIEND_TEST(LifeTest, at_2);
		FRIEND_TEST(LifeTest, at_3);
		FRIEND_TEST(LifeTest, update_neighbor_1);
		FRIEND_TEST(LifeTest, update_neighbor_2);
		FRIEND_TEST(LifeTest, update_neighbor_3);
		FRIEND_TEST(LifeTest, begin_1);
		FRIEND_TEST(LifeTest, begin_2);
		FRIEND_TEST(LifeTest, begin_3);
		FRIEND_TEST(LifeTest, end_1);
		FRIEND_TEST(LifeTest, end_2);
		FRIEND_TEST(LifeTest, end_3);
		FRIEND_TEST(LifeTest, print_1);
		FRIEND_TEST(LifeTest, print_2);
		FRIEND_TEST(LifeTest, print_3);
		FRIEND_TEST(LifeTest, simulate_1);
		FRIEND_TEST(LifeTest, simulate_2);
		FRIEND_TEST(LifeTest, simulate_3);
};

class AbstractCell {
	friend class AbstractCellTest;
	protected:
		bool _alived;
		AbstractCell& operator = (const AbstractCell&)  = default;
        AbstractCell& operator = (      AbstractCell&&) = default;
		
	public:
		AbstractCell(bool alived);
		AbstractCell (const AbstractCell&)  = default;
        AbstractCell (      AbstractCell&&) = default;
		virtual ~AbstractCell() = default;

		virtual AbstractCell* clone() const = 0;

		// ------------
		// update_state
		// ------------

		/**
		 * @param       String character 
		 */
		virtual void update_state(string c) = 0;

		// --------------
		// count_neighbor
		// --------------

		/**
		 * @param       int[] of possible neighbors upto 8 neighbors 
		 * @return		int   number of neighbor
		 */
		virtual int count_neighbor(int possible_nb[]) const = 0;

		// -----
		// print
		// -----

		/**
		 * @param       
		 * @return		string character of the cell state
		 */
		virtual string print() = 0;

		// ------
		// evolve
		// ------

		/**
		 * @param       int number of neighbors
		 */
		virtual void evolve(int num_neighbors) = 0;

		// ---
		// cnt
		// ---

		/**
		 * @return		count 1 for alived, count 0 for dead
		 */
		virtual int cnt() = 0;

		// ----------
		// operator==
		// ----------

		/**
		 * @param		other AbstractCell
		 * @return		true for equal, otherwise false
		 */
		virtual bool operator == (const AbstractCell& rhs) const;

    	FRIEND_TEST(AbstractCellTest, AbstractCell_1);
    	FRIEND_TEST(AbstractCellTest, AbstractCell_2);
    	FRIEND_TEST(AbstractCellTest, AbstractCell_3);
    	FRIEND_TEST(AbstractCellTest, operator_equal_equal_1);
    	FRIEND_TEST(AbstractCellTest, operator_equal_equal_2);
    	FRIEND_TEST(AbstractCellTest, operator_equal_equal_3);

};

class ConwayCell : public AbstractCell {
	friend class ConwayCellTest;
	public:
		// -----------
		// Constructor
		// -----------

		/**
		 * @param       String name and default 
		 */

		ConwayCell();
		ConwayCell(const ConwayCell&) = default;
		ConwayCell (     ConwayCell&&) = default;
		ConwayCell& operator = (const ConwayCell&) = default;
        ConwayCell& operator = (      ConwayCell&&) = default;
		~ConwayCell() = default;

		AbstractCell* clone () const;

		// ------------
		// update_state
		// ------------

		/**
		 * @param       String character 
		 */
		void update_state(string c);

		// --------------
		// count_neighbor
		// --------------

		/**
		 * @param       int[] of possible neighbors upto 8 neighbors 
		 * @return		int   number of neighbor
		 */
		int count_neighbor(int possible_nb[]) const;

		// -----
		// print
		// -----

		/**
		 * @param       
		 * @return		string character of the cell state
		 */
		string print();

		// ------
		// evolve
		// ------

		/**
		 * @param       int number of neighbors
		 */
		void evolve(int num_neighbors);

		// ---
		// cnt
		// ---

		/**
		 * @return		count 1 for alived, count 0 for dead
		 */
		int cnt();

		// ----------
		// operator==
		// ----------

		/**
		 * @param		other ConwayCell
		 * @return		true for equal, otherwise false
		 */
		bool operator == (const ConwayCell& rhs) const;

        FRIEND_TEST(ConwayCellTest, ConwayCell_1);
        FRIEND_TEST(ConwayCellTest, ConwayCell_2);
        FRIEND_TEST(ConwayCellTest, ConwayCell_3);
		FRIEND_TEST(ConwayCellTest, clone_1);
		FRIEND_TEST(ConwayCellTest, clone_2);
		FRIEND_TEST(ConwayCellTest, clone_3);
		FRIEND_TEST(ConwayCellTest, update_state_1);
		FRIEND_TEST(ConwayCellTest, update_state_2);
		FRIEND_TEST(ConwayCellTest, update_state_3);
		FRIEND_TEST(ConwayCellTest, count_neighbor_1);
		FRIEND_TEST(ConwayCellTest, count_neighbor_2);
		FRIEND_TEST(ConwayCellTest, count_neighbor_3);
		FRIEND_TEST(ConwayCellTest, print_1);
		FRIEND_TEST(ConwayCellTest, print_2);
		FRIEND_TEST(ConwayCellTest, print_3);
		FRIEND_TEST(ConwayCellTest, evolve_1);
		FRIEND_TEST(ConwayCellTest, evolve_2);
		FRIEND_TEST(ConwayCellTest, evolve_3);
		FRIEND_TEST(ConwayCellTest, cnt_1);
		FRIEND_TEST(ConwayCellTest, cnt_2);
		FRIEND_TEST(ConwayCellTest, cnt_3);
		FRIEND_TEST(ConwayCellTest, operator_equal_equal_1);
		FRIEND_TEST(ConwayCellTest, operator_equal_equal_2);
		FRIEND_TEST(ConwayCellTest, operator_equal_equal_3);

};

class FredkinCell : public AbstractCell {
	friend class FredkinCellTest;
	private:
		int _age;
	public:
		// -----------
		// Constructor
		// -----------

		/**
		 * @param       String name and default 
		 */
		FredkinCell();
		FredkinCell(const FredkinCell&) = default;
		FredkinCell (      FredkinCell&&) = default;
		FredkinCell& operator = (const FredkinCell&)  = default;
        FredkinCell& operator = (      FredkinCell&&) = default;
		~FredkinCell() = default;

		AbstractCell* clone () const;

		// ------------
		// update_state
		// ------------

		/**
		 * @param       String character 
		 */
		void update_state(string c);

		// --------------
		// count_neighbor
		// --------------

		/**
		 * @param       int[] of possible neighbors upto 8 neighbors 
		 * @return		int   number of neighbor
		 */
		int count_neighbor(int possible_nb[]) const;

		// -----
		// print
		// -----

		/**
		 * @param       
		 * @return		string character of the cell state
		 */
		string print();

		// ------
		// evolve
		// ------

		/**
		 * @param       int number of neighbors
		 */
		void evolve(int num_neighbors);

		// ---
		// cnt
		// ---

		/**
		 * @return		count 1 for alived, count 0 for dead
		 */
		int cnt();

		// ----------
		// operator==
		// ----------

		/**
		 * @param		other FredkinCell
		 * @return		true for equal, otherwise false
		 */
		bool operator== (const FredkinCell& rhs) const;

        FRIEND_TEST(FredkinCellTest, FredkinCell_1);
        FRIEND_TEST(FredkinCellTest, FredkinCell_2);
        FRIEND_TEST(FredkinCellTest, FredkinCell_3);
		FRIEND_TEST(FredkinCellTest, clone_1);
		FRIEND_TEST(FredkinCellTest, clone_2);
		FRIEND_TEST(FredkinCellTest, clone_3);
		FRIEND_TEST(FredkinCellTest, update_state_1);
		FRIEND_TEST(FredkinCellTest, update_state_2);
		FRIEND_TEST(FredkinCellTest, update_state_3);
		FRIEND_TEST(FredkinCellTest, count_neighbor_1);
		FRIEND_TEST(FredkinCellTest, count_neighbor_2);
		FRIEND_TEST(FredkinCellTest, count_neighbor_3);
		FRIEND_TEST(FredkinCellTest, print_1);
		FRIEND_TEST(FredkinCellTest, print_2);
		FRIEND_TEST(FredkinCellTest, print_3);
		FRIEND_TEST(FredkinCellTest, evolve_1);
		FRIEND_TEST(FredkinCellTest, evolve_2);
		FRIEND_TEST(FredkinCellTest, evolve_3);
		FRIEND_TEST(FredkinCellTest, cnt_1);
		FRIEND_TEST(FredkinCellTest, cnt_2);
		FRIEND_TEST(FredkinCellTest, cnt_3);
		FRIEND_TEST(FredkinCellTest, operator_equal_equal_1);
		FRIEND_TEST(FredkinCellTest, operator_equal_equal_2);
		FRIEND_TEST(FredkinCellTest, operator_equal_equal_3);
};

class Cell {
	friend class CellTest;
	private:
		AbstractCell* _p;
			
	public:
		// -----------
		// Constructor
		// -----------

		/**
		 * @param       String name and default 
		 */
		Cell();
		Cell(const Cell&);
		Cell(     Cell&&) = default;
		Cell& operator = (const Cell&)  = default;
        Cell& operator = (      Cell&&) = default;

		// -----------
		// Destructor
		// -----------

		/**
		 * @param       String name and default 
		 */        
		~Cell();

		// ------------
		// update_state
		// ------------

		/**
		 * @param       String character 
		 */
		void update_state(string c);

		// --------------
		// count_neighbor
		// --------------

		/**
		 * @param       int[] of possible neighbors upto 8 neighbors 
		 * @return		int   number of neighbor
		 */
		int count_neighbor(int possible_nb[]) const;

		// -----
		// print
		// -----

		/**
		 * @param       
		 * @return		string character of the cell state
		 */
		string print();

		// ------
		// evolve
		// ------

		/**
		 * @param       int number of neighbors
		 */
		void evolve(int num_neighbors);

		// ---
		// cnt
		// ---

		/**
		 * @return		count 1 for alived, count 0 for dead
		 */
		int cnt();
		bool operator== (const Cell& rhs) const;

        FRIEND_TEST(CellTest, Cell_1);
        FRIEND_TEST(CellTest, Cell_2);
        FRIEND_TEST(CellTest, Cell_3);
		FRIEND_TEST(CellTest, clone_1);
		FRIEND_TEST(CellTest, clone_2);
		FRIEND_TEST(CellTest, clone_3);
		FRIEND_TEST(CellTest, update_state_1);
		FRIEND_TEST(CellTest, update_state_2);
		FRIEND_TEST(CellTest, update_state_3);
		FRIEND_TEST(CellTest, count_neighbor_1);
		FRIEND_TEST(CellTest, count_neighbor_2);
		FRIEND_TEST(CellTest, count_neighbor_3);
		FRIEND_TEST(CellTest, print_1);
		FRIEND_TEST(CellTest, print_2);
		FRIEND_TEST(CellTest, print_3);
		FRIEND_TEST(CellTest, evolve_1);
		FRIEND_TEST(CellTest, evolve_2);
		FRIEND_TEST(CellTest, evolve_3);
		FRIEND_TEST(CellTest, cnt_1);
		FRIEND_TEST(CellTest, cnt_2);
		FRIEND_TEST(CellTest, cnt_3);
};


#endif // Life_h