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
		}

		void add_cell(string s){
		  if(_c == _col-1){
		        ++_r;
		        _c = 1;
		    }
		  	_grid[_r][_c].update_state(s);
		    _neigh_cnt[_r][_c] = (*this).at(_r, _c).cnt();
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
		    for(int row = 1; row < (int)_grid.size()-1; ++row) {
		        for(int col = 1; col < _grid[0].size()-1; ++col) {
		        		_neigh_cnt[row][col] = _grid[row][col].count_neighbor(_grid, row, col);
		            _pop += _grid[row][col].cnt();            
		        }
		    }
		}

		typename std::vector<vector<value_type>>::iterator begin() {
		    return _grid.begin();
		}

		typename vector<vector<value_type>>::iterator end() {
		    return _grid.end();
		}

		void print() {
		   	typename vector<vector<value_type>>::iterator row;
		    typename vector<value_type>::iterator col;
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

		void simulate(int evol, int step = 1) {
			cout << endl;
		    cout << "Generation = " << 0 << ", Population = " << _pop << "." << endl;
		    print();

		    for(int i = 1; i <= evol; ++i){
		        update_neighbor();
		        int pop = 0;
		        for(int row = 1; row < (int)_grid.size()-1; ++row) {
		            for(int col = 1; col < _grid[0].size()-1; ++col) {
		                int num_neigh = _neigh_cnt[row][col];
		                _grid[row][col].evolve(num_neigh);
		                pop += _grid[row][col].cnt();
		            }
		        }
		        if (i%step == 0) {
			        cout << "Generation = " << i << ", Population = " << pop << "." << endl;;
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
		// AbstractCell();
		AbstractCell(bool alived);
		
		// virtual AbstractCell* clone () const = 0;
		virtual AbstractCell* clone() = 0;
		// virtual char changed(char status) const = 0;
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
			
			// ConwayCell(string c);
			ConwayCell();
      ConwayCell(const ConwayCell&) = default;
      void update_state(string c);
      int count_neighbor(vector< vector<ConwayCell>> _grid, int row, int col);
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
      int count_neighbor(vector< vector<FredkinCell>> _grid, int row, int col);
			AbstractCell* clone ();
			string print();
			void evolve(int num_neighbors);
			int cnt();
      ~FredkinCell() = default;
};

// class Cell {
// 		friend class CellTest;
// 		private:
// 			AbstractCell* _p;
				
// 		public:
// 				// -----------
// 				// Constructor
// 				// -----------

// 				/**
// 				 * @param       String name and default 
// 				 */

// 				 Cell();
// 				 Cell(const Cell& rhs);
// 				 ~Cell();


// };

// class Cell {
// 	private:
// 		AbstractCell* _p;
// 	public:
// 		Cell(bool alived);

// };


#endif // Life_h