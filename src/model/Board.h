/*
 * Borad.h
 *
 *  Created on: Apr 13, 2023
 *      Author: larry
 */

#ifndef MODEL_BOARD_H_
#define MODEL_BOARD_H_

#include <Node.h>

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

namespace model {

class Board {
private:
	Node *firstNode;
	bool checkIfNodeSolved(Node *node);
public:
	const int MAX_VALUE = 64;
	const int MIN_VALUE = 1;

	/**
	 * Initializes a Board
	 *
	 * @pre none
	 * @post this->firstNode == nullptr
	 *
	 */
	Board();

	/**
	 * Deconstructor for the node.
	 */
	virtual ~Board();

	/**
	 * Loads a board given a vector of nodes
	 *
	 * @pre none
	 * @post this-> firstNode != nullptr
	 *
	 * @param nodes the nodes for the board
	 *
	 * @return true if the board was loaded correctly and false if not
	 */
	bool loadBoard(vector<Node*> nodes);

	/**
	 * Checks if the board is solved
	 *
	 * @return true if not and false if so
	 */
	bool isSolved();

};

} /* namespace model */

#endif /* MODEL_BOARD_H_ */
