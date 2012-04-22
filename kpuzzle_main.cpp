//============================================================================
// Name        : kpuzzle_main.cpp
// Author      : Dogukan Cagatay
// E-mail	   : dcagatay@gmail.com
// Version     : v1.4
// Description : Uniform Cost Search generic solution finder for The 8-Puzzle
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "kpuzzle.hpp"
#include "kpuzzle_algorithms.hpp"

using namespace std;

int main() {
	vector<vector<int> > is;
	vector<int> is1;
	vector<int> is2;
	vector<int> is3;

	KPuzzle* initial_state;

	/* create initial state */

	// the question
//	is1.push_back(5);
//	is1.push_back(4);
//	is1.push_back(0);
//
//	is2.push_back(6);
//	is2.push_back(1);
//	is2.push_back(8);
//
//	is3.push_back(7);
//	is3.push_back(3);
//	is3.push_back(2);

	//easy example
//	is1.push_back(1);
//	is1.push_back(3);
//	is1.push_back(4);
//
//	is2.push_back(8);
//	is2.push_back(6);
//	is2.push_back(2);
//
//	is3.push_back(7);
//	is3.push_back(0);
//	is3.push_back(5);

	//medium example
//	is1.push_back(2);
//	is1.push_back(8);
//	is1.push_back(1);
//
//	is2.push_back(0);
//	is2.push_back(4);
//	is2.push_back(3);
//
//	is3.push_back(7);
//	is3.push_back(6);
//	is3.push_back(5);

	//hard example
	is1.push_back(2);
	is1.push_back(8);
	is1.push_back(1);

	is2.push_back(4);
	is2.push_back(6);
	is2.push_back(3);

	is3.push_back(0);
	is3.push_back(7);
	is3.push_back(5);

	//worst example
//	is1.push_back(5);
//	is1.push_back(6);
//	is1.push_back(7);
//
//	is2.push_back(4);
//	is2.push_back(0);
//	is2.push_back(8);
//
//	is3.push_back(3);
//	is3.push_back(2);
//	is3.push_back(1);

	//an example
//	is1.push_back(2);
//	is1.push_back(8);
//	is1.push_back(3);
//
//	is2.push_back(1);
//	is2.push_back(6);
//	is2.push_back(4);
//
//	is3.push_back(7);
//	is3.push_back(0);
//	is3.push_back(5);

	is.push_back(is1);
	is.push_back(is2);
	is.push_back(is3);

	initial_state = new KPuzzle(is.size(), 0, is);

	/* create goal state */
	is[0][0] = 1;
	is[0][1] = 2;
	is[0][2] = 3;

	is[1][0] = 8;
	is[1][1] = 0;
	is[1][2] = 4;

	is[2][0] = 7;
	is[2][1] = 6;
	is[2][2] = 5;

	goal_state = new KPuzzle(is.size(), -1, is);

//	cout<< find_manhattan_distance(initial_state,goal_state) << endl;

	time_t start = time(NULL);
	KPuzzle *result = uniform_cost_search_with_stl(initial_state, goal_state);
	cout << "Time elapsed = " << time(NULL)-start << endl;

	if (result != NULL) {
		cout << "Path cost = " << result->get_path_cost() << endl;
	}

	for (KPuzzle* it = result; it != NULL; it = it->get_parent()) {
		it->print_puzzle();
		cout << endl;
	}

	return 0;
}
