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
		int _row;
		int _col;
		int _pop;

	public:
		Life<value_type> (int row, int col) {
			_grid.resize(row+2, vector<value_type> (col+2, value_type()));
			_neigh_cnt.resize(row+2, vector<int> (col+2, 0));
			_r = 1;
			_c = 1;
			_row = row+2;
			_col = col+2;
			_pop = 0;
			_generation = 0;
		}

		void add_cell(string s){
		  if(_c == _col-1){
				++_r;
				_c = 1;
			}
			_grid[_r][_c].update_state(s);
			_neigh_cnt[_r][_c] = _grid[_r][_c].cnt();
			_pop += (*this).at(_r, _c).cnt();
			++_c;
		}

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

		value_type& at(int r, int c){
			return _grid[r][c]; 
		}

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

		typename vector<vector<value_type>>::iterator begin() {
			return _grid.begin();
		}

		typename vector<vector<value_type>>::iterator end() {
			return _grid.end();
		}

		void print() {
			typename vector<vector<value_type>>::iterator row;
			typename vector<value_type>::iterator col;
			cout << "Generation = " << _generation << ", Population = " << _pop << "." << endl;
			int r = 0;
			for(row = (*this).begin()+1; row != (*this).end()-1; ++row) {
				for(col = (*row).begin()+1; col != (*row).end()-1; ++col) {
					cout <<(*col).print();
				}
				cout << endl; 
				++r;
			}
			cout << endl;
		}

		void simulate(int evol, int gen=0, bool original = true, int step = 1, int start=0, int end=0) {

			if(original) {
				cout << endl;
				print();
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
				if(gen && _generation == gen)
					print();
				else if(start < end && _generation == start) {
					print();
					++start;
				} else if(step > 1 && i%step == 0) {
					print();
				} else if(step == 1 && gen == 0 && start == 0 && end == 0){
					print();
				}
					
			}
		}
};

class AbstractCell {
	// friend class AbstractCellTest;
	protected:
		bool _alived;
		char _cell;
		
	public:
		AbstractCell(bool alived);
		virtual AbstractCell* clone() = 0;
		virtual void update_state(string c) = 0;
		virtual string print() = 0;
		virtual void evolve(int num_neighbors) = 0;
		virtual int cnt() = 0;

};

class ConwayCell : public AbstractCell {
	// friend class ConwayCellTest;
	public:
		// -----------
		// Constructor
		// -----------

		/**
		 * @param       String name and default 
		 */

		ConwayCell();
		ConwayCell(const ConwayCell&) = default;
		void update_state(string c);
		int count_neighbor(int possible_nb[]);
		AbstractCell* clone ();
		string print();
		void evolve(int num_neighbors);
		int cnt();
		~ConwayCell() = default;
};

class FredkinCell : public AbstractCell {
	// friend class FredkinCellTest;
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
		void update_state(string c);
		int count_neighbor(int possible_nb[]);
		AbstractCell* clone ();
		string print();
		void evolve(int num_neighbors);
		int cnt();
		~FredkinCell() = default;
};

class Cell {
	// friend class CellTest;
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
		Cell (const Cell& rhs);
		~Cell ();
		void update_state(string c);
		string print();
		int count_neighbor(int possible_nb[]);
		void evolve(int num_neighbors);
		// Cell& operator = (Cell rhs);
		// void swap (Cell& rhs);
		int cnt();
};


#endif // Life_h