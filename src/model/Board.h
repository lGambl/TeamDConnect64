/*
 * Borad.h
 *
 *  Created on: Apr 13, 2023
 *      Author: larry
 */

#ifndef MODEL_BOARD_H_
#define MODEL_BOARD_H_

#include <BoardNode.h>

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include <BoardReader.h>
using namespace datatier;

namespace model {

/**
 * A board class that represents a board of the game
 */
class Board {
private:
	BoardNode *firstNode;
	vector<BoardNode*> nodes;

	uint numberColumns;
	uint numberRows;
	int nodeCount;
	int timer;

	void setUpNodes();

	bool checkIfNodeSolved(BoardNode *node);
public:
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
	bool loadBoard(int difficulty);

	/**
	 * Checks if the board is solved
	 *
	 * @return true if not and false if so
	 */
	bool isSolved();

	/**
	 * Getter for the number of columns on the board.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The number of columns on the board
	 */
	int getNumberColumns() const {
		return this->numberColumns;
	}

	/**
	 * Getter for the number of rows on the board.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The number of rows on the board
	 */
	int getNumberRows() const {
		return this->numberRows;
	}

	/**
	 * Getter for the nodes on the board.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The nodes on the board
	 */
	const vector<BoardNode*>& getNodes() const {
		return this->nodes;
	}

	/**
	 * Gets the timer
	 *
	 * @return timer
	 */
	int getTimer() const {
		return this->timer;
	}

	/**
	 * Sets the timer
	 *
	 *@pre none
	 *@post this->timer == timer
	 *
	 * @return
	 */
	void setTimer(int timer) {
		this->timer = timer;
	}

	void setNodes(vector<BoardNode*> nodes);
};


} /* namespace model */

#endif /* MODEL_BOARD_H_ */
