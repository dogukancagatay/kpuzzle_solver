//============================================================================
// Name        : se420_hw2_2.cpp
// Author      : Dogukan Cagatay IEU 20070602012
// Version     : v1.4
// Description : Uniform Cost Search Solution for The 8-Puzzle
//============================================================================

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
KPuzzle* goal_state;
/* start KPuzzle class method implementations */
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

int find_misplaced_tiles(KPuzzle *kp,KPuzzle *goal_state){
	int misplaced_counter = 0;

	for (unsigned int i = 0; i < kp->get_puzzle().size(); ++i) {
		for (unsigned int j = 0; j < kp->get_puzzle()[i].size(); ++j) {
			if(kp->get_puzzle()[i][j] != goal_state->get_puzzle()[i][j]){
				misplaced_counter++;
			}
		}
	}
	return misplaced_counter;
}

int find_manhattan_distance(KPuzzle *kp,KPuzzle *goal_state){
	int distance = 0;
	vector<std::pair<int,int> > rac(kp->get_k() * kp->get_k()); // holds each tiles position
	int i_dist,j_dist;

	for (unsigned int i = 0; i < kp->get_puzzle().size(); ++i) {
		for (unsigned int j = 0; j < kp->get_puzzle()[i].size(); ++j) {
			rac[goal_state->get_puzzle()[i][j]].first = (int)i;
			rac[goal_state->get_puzzle()[i][j]].second = (int)j;
		}
	}

	for (unsigned int i = 0; i < kp->get_puzzle().size(); ++i) {
		for (unsigned int j = 0; j < kp->get_puzzle()[i].size(); ++j) {
			if(kp->get_puzzle()[i][j] != goal_state->get_puzzle()[i][j]){
				if(kp->get_puzzle()[i][j] != 0){
					i_dist = i - rac[kp->get_puzzle()[i][j]].first ;
					i_dist = i_dist < 0 ? i_dist*(-1) : i_dist;
					j_dist = j - rac[kp->get_puzzle()[i][j]].second;
					j_dist = j_dist < 0 ? j_dist*(-1) : j_dist;

					distance += i_dist;
					distance += j_dist;
					i_dist = 0;
					j_dist = 0;
				}
			}
		}
	}
	return distance;
}

struct _BFS_KPuzzle {
	bool operator()(KPuzzle* lhs, KPuzzle* rhs) {
		if (lhs->get_path_cost() < rhs->get_path_cost())
			return true;
		else
			return false;
	}
} BFS_KPuzzle;

struct _DFS_KPuzzle {
	bool operator()(KPuzzle* lhs, KPuzzle* rhs) {
		if (lhs->get_path_cost() > rhs->get_path_cost())
			return true;
		else
			return false;
	}
} DFS_KPuzzle;

struct _GREEDY_KPuzzle {
	bool operator()(KPuzzle* lhs, KPuzzle* rhs) {
		if (find_misplaced_tiles(lhs,goal_state) < find_misplaced_tiles(rhs,goal_state))
			return true;
		else
			return false;
	}
} GREEDY_KPuzzle;

struct _ASTAR_KPuzzle {
	bool operator()(KPuzzle* lhs, KPuzzle* rhs) {
		if (lhs->get_path_cost() + find_misplaced_tiles(lhs, goal_state) < rhs->get_path_cost() + find_misplaced_tiles(rhs, goal_state))
			return true;
		else
			return false;
	}
} ASTAR_KPuzzle;

struct _ASTARV2_KPuzzle {
	bool operator()(KPuzzle* lhs, KPuzzle* rhs) {
		if (lhs->get_path_cost() + find_manhattan_distance(lhs, goal_state) < rhs->get_path_cost() + find_manhattan_distance(rhs, goal_state))
			return true;
		else
			return false;
	}
} ASTARV2_KPuzzle;

KPuzzle* uniform_cost_search_with_stl(KPuzzle* initial_state, KPuzzle* goal_state) {
	KPuzzle *temp = NULL, *node = NULL;
	vector<KPuzzle*> open;
	vector<KPuzzle*> closed;
	vector<KPuzzle*>::iterator closed_it, open_it;
	vector<KPuzzle*> children;

	//inser the initial state to the open queue
	open.push_back(initial_state);
	do {
		if (open.empty()) {
			cout << "Failure" << endl;
			return NULL;
		}
		node = open.front();

		if (*node == *goal_state) {
			cout << "Found the goal" << endl;
			//return node;
			break;
		}
		/*If the current state can move up, add the moved up state
		 * to the tree and queue to be processed afterwards
		 */
		if ((temp = node->move_up()) != NULL) {
			children.push_back(temp);
		}
		/* If the current state can move up, add the moved down state
		 * to the tree and queue to be processed afterwards
		 */
		if ((temp = node->move_down()) != NULL) {
			children.push_back(temp);
		}
		/* If the current state can move up, add the moved left state
		 * to the tree and queue to be processed afterwards
		 */
		if ((temp = node->move_left()) != NULL) {
			children.push_back(temp);
		}
		/* If the current state can move up, add the moved left state
		 * to the tree and queue to be processed afterwards
		 */
		if ((temp = node->move_right()) != NULL) {
			children.push_back(temp);
		}
		open.erase(open.begin()); // pop the open queue
		for (unsigned int i = 0; i < children.size(); ++i) {
			if (find(open.begin(),open.end(),children[i]) == open.end() && find(closed.begin(), closed.end(),children[i]) == closed.end()) {
				open.push_back(children[i]);
			} else if ((open_it = find(open.begin(),open.end(),children[i])) != open.end()) {
				if ((*open_it)->get_path_cost() >= children[i]->get_path_cost()) {
					open.erase(open_it);
					open.push_back(children[i]);
				}
			} else if ((closed_it = find(closed.begin(),closed.end(),children[i])) != closed.end()) {
				if ((*closed_it)->get_path_cost()
						>= children[i]->get_path_cost()) {
					closed.erase(closed_it);
					open.push_back(children[i]);
				}
			}
		}
		closed.push_back(node);
//		sort(open.begin(), open.end(), BFS_KPuzzle);
//		sort(open.begin(), open.end(), GREEDY_KPuzzle);
//		sort(open.begin(), open.end(), ASTAR_KPuzzle);
		sort(open.begin(), open.end(), ASTARV2_KPuzzle);
		children.clear();

	} while (true);

	return node;
}

int main() {
	vector<vector<int> > is;
	vector<int> is1;
	vector<int> is2;
	vector<int> is3;

	KPuzzle* initial_state;

	/* create initial state */

	// homework question
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
