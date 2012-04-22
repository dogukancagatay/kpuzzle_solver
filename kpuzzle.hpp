//============================================================================
// Name        : kpuzzle.hpp
// Author      : Dogukan Cagatay
// E-mail	   : dcagatay@gmail.com
// Version     : v1.4
// Description : kpuzzle class definition and implementation.
//============================================================================

#ifndef KPUZZLE_HPP
#define KPUZZLE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

/* Class definition of KPuzzle */
class KPuzzle {
public:
	KPuzzle(unsigned int k, int depth, vector<vector<int> >& initial_state);
	KPuzzle(KPuzzle *kp);
	unsigned int get_k() const;
	int get_depth();
	int get_path_cost() const;
	vector<vector<int> >& get_puzzle();
	KPuzzle* get_parent();
	KPuzzle* move_up();
	KPuzzle* move_down();
	KPuzzle* move_left();
	KPuzzle* move_right();
	void set_empty(pair<unsigned int, unsigned int>* new_empty);
	void set_depth(int depth);
	void set_parent(KPuzzle* parent);
	void add_path_cost(int cost);
	void print_puzzle() const;
	bool operator==(KPuzzle& other);
	bool operator==(KPuzzle* other);
    enum algoEnum{ BFS, DFS, GREEDY, AStar};
private:
    typedef pair<unsigned int,unsigned int> position;
    position *empty;
    vector<vector<int> > puzzle;
    unsigned int K;
    int depth;
    int path_cost;
    KPuzzle *parent;
    algoEnum algorithm;
    void find_empty();
    int cost_function();
};

//* start KPuzzle class method implementations */
KPuzzle::KPuzzle(unsigned int k, int depth,
		vector<vector<int> >& initial_state) {
	K = k;
	puzzle = initial_state;
	this->depth = depth;
	find_empty();
	set_parent(NULL);
	path_cost = 0;
}
KPuzzle::KPuzzle(KPuzzle *kp) {
	K = kp->get_k();
	puzzle = kp->get_puzzle();
	depth = kp->get_depth() + 1;
	find_empty();
	set_parent(kp);
	path_cost = 0;
}

int KPuzzle::get_path_cost() const {
	return path_cost;
}
unsigned int KPuzzle::get_k() const {
	return K;
}
void KPuzzle::add_path_cost(int cost) {
	path_cost += cost;
}
vector<vector<int> > & KPuzzle::get_puzzle() {
	return puzzle;
}
KPuzzle* KPuzzle::get_parent() {
	return parent;
}

void KPuzzle::print_puzzle() const {
	for (unsigned int i = 0; i < puzzle.size(); ++i) {
		for (unsigned int j = 0; j < puzzle[i].size(); ++j) {
			if (puzzle[i][j] == 0) {
				cout << ' ' << ' ';
			} else {
				cout << ' ' << puzzle[i][j];
			}
		}
		cout << endl;
	}
}

KPuzzle *KPuzzle::move_left() {
	KPuzzle * new_puzzle;
	if (empty->second == 0) { //if it is in the leftist column
		new_puzzle = NULL;
	} else {

		//new_puzzle = new KPuzzle(puzzle.size(), get_depth() + 1, puzzle);
		new_puzzle = new KPuzzle(this);
		new_puzzle->get_puzzle()[empty->first][empty->second] =
				new_puzzle->get_puzzle()[empty->first][empty->second - 1];
		new_puzzle->get_puzzle()[empty->first][empty->second - 1] = 0;
		new_puzzle->set_empty(new position(empty->first, empty->second - 1));
		new_puzzle->add_path_cost(get_path_cost() + 1);
	}
	return new_puzzle;
}

KPuzzle *KPuzzle::move_right() {
	KPuzzle * new_puzzle;
	if (empty->second == K - 1) { //if it is in the rightest column
		new_puzzle = NULL;
	} else {
		//new_puzzle = new KPuzzle(puzzle.size(), get_depth() + 1, puzzle);
		new_puzzle = new KPuzzle(this);
		new_puzzle->get_puzzle()[empty->first][empty->second] =
				new_puzzle->get_puzzle()[empty->first][empty->second + 1];
		new_puzzle->get_puzzle()[empty->first][empty->second + 1] = 0;
		new_puzzle->set_empty(new position(empty->first, empty->second + 1));
		new_puzzle->add_path_cost(get_path_cost() + 1);
	}
	return new_puzzle;
}

KPuzzle *KPuzzle::move_up() {
	KPuzzle * new_puzzle;
	if (empty->first == 0) { //if it is in the top row
		new_puzzle = NULL;
	} else {
//		new_puzzle = new KPuzzle(puzzle.size(), get_depth() + 1, puzzle);
		new_puzzle = new KPuzzle(this);
		new_puzzle->get_puzzle()[empty->first][empty->second] =
				new_puzzle->get_puzzle()[empty->first - 1][empty->second];
		new_puzzle->get_puzzle()[empty->first - 1][empty->second] = 0;
		new_puzzle->set_empty(new position(empty->first - 1, empty->second));
		new_puzzle->add_path_cost(get_path_cost() + 1);
	}
	return new_puzzle;
}

KPuzzle *KPuzzle::move_down() {
	KPuzzle * new_puzzle;
	if (empty->first == K - 1) { //if it is in the bottom row
		new_puzzle = NULL;
	} else {
//		new_puzzle = new KPuzzle(puzzle.size(), get_depth() + 1, puzzle);
		new_puzzle = new KPuzzle(this);
		new_puzzle->get_puzzle()[empty->first][empty->second] =
				new_puzzle->get_puzzle()[empty->first + 1][empty->second];
		new_puzzle->get_puzzle()[empty->first + 1][empty->second] = 0;
		new_puzzle->set_empty(new position(empty->first + 1, empty->second));
		new_puzzle->add_path_cost(get_path_cost() + 1);
	}
	return new_puzzle;
}

void KPuzzle::set_empty(pair<unsigned int, unsigned int> *new_empty) {
	delete (empty);
	empty = new_empty;
}

int KPuzzle::get_depth() {
	return depth;
}
void KPuzzle::set_depth(int depth) {
	this->depth = depth;
}

inline void KPuzzle::set_parent(KPuzzle *parent) {
	this->parent = parent;
}

void KPuzzle::find_empty() {
	for (unsigned int i = 0; i < puzzle.size(); ++i) {
		for (unsigned int j = 0; j < puzzle[i].size(); ++j) {
			if (puzzle[i][j] == 0) {
				empty = new pair<unsigned int, unsigned int>(i, j);
			}
		}
	}
}

bool KPuzzle::operator==(KPuzzle &other) {
	if (get_puzzle() == other.get_puzzle())
		return true;
	else
		return false;
}

bool KPuzzle::operator==(KPuzzle *other) {
	if (this->get_puzzle() == other->get_puzzle())
		return true;
	else
		return false;
}

#endif