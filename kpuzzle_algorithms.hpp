//============================================================================
// Name        : kpuzzle_algorithms.cpp
// Author      : Dogukan Cagatay
// E-mail	   : dcagatay@gmail.com
// Version     : v1.4
// Description : kpuzzle solving algorithm implementations.
//============================================================================

#ifndef KPUZZLE_ALGORITHMS_CPP
#define KPUZZLE_ALGORITHMS_CPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "kpuzzle.hpp"

using namespace std;

KPuzzle* goal_state;

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

	//insert the initial state to the open queue
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

#endif