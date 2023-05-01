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
	static const int NUMBER_COLUMNS = 8;
	static const int NUMBER_ROWS = 8;
	const int MIN_VALUE = 1;

	BoardNode *firstNode;
	vector<BoardNode*> nodes;

	uint numberColumns;
	uint numberRows;
	int nodeCount;
	int timer;

	void setUpNodes();

	bool checkIfNodeSolved(BoardNode *node);

	void setEastNode(vector<BoardNode*>::size_type i, BoardNode *current);
	void setWestNode(vector<BoardNode*>::size_type i, BoardNode *current);
	void setNorthNode(vector<BoardNode*>::size_type i, BoardNode *current);
	void setSouthNode(vector<BoardNode*>::size_type i, BoardNode *current);

public:

	/**
	 * Initializes a Board.
	 *
	 * @precondition none
	 * @postcondition this->firstNode == nullptr
	 */
	Board();

	/**
	 * Deconstructor for the node.
	 */
	virtual ~Board();

	/**
	 * Loads a board given a vector of nodes.
	 *
	 * @precondition none
	 * @postcondition this-> firstNode != nullptr
	 *
	 * @param difficulty The difficulty to load.
	 *
	 * @return True if the board was loaded correctly and False if not.
	 */
	bool loadBoard(int difficulty);

	/**
	 * Checks if the board is solved.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return True if solved and false otherwise.
	 */
	bool isSolved();

	/**
	 * Getter for the number of columns on the board.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The number of columns on the board.
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
	 * @return The number of rows on the board.
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
	 * @return The nodes on the board.
	 */
	const vector<BoardNode*>& getNodes() const {
		return this->nodes;
	}

	/**
	 * Getter for the timer of the board.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return timer The timer for the board.
	 */
	int getTimer() const {
		return this->timer;
	}

	/**
	 * Sets the timer.
	 *
	 * @precondition none
	 * @postcondition this->timer == timer
	 *
	 * @param timer The new timer value.
	 */
	void setTimer(int timer) {
		this->timer = timer;
	}

	/**
	 * Setter for the list of nodes.
	 *
	 * @precondition none
	 * @postcondition this.firstNode == nodes[i]
	 *
	 * @param nodes The new nodes for the board.
	 */
	void setNodes(vector<BoardNode*> nodes);
};

} /* namespace model */

#endif /* MODEL_BOARD_H_ */
