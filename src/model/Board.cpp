/*
 * Borad.cpp
 *
 *  Created on: Apr 13, 2023
 *      Author: larry
 */

#include <Board.h>

namespace model {

Board::Board() {
	this->firstNode = nullptr;

	this->numberColumns = NUMBER_COLUMNS;
	this->numberRows = NUMBER_ROWS;
	this->timer = 0;

	this->nodeCount = this->numberColumns * this->numberRows;
}

Board::~Board() {
	delete this->firstNode;
}

bool Board::loadBoard(int difficulty) {
	BoardReader handler;
	this->nodes = handler.readNodeFile(difficulty);

	this->setUpNodes();

	return this->firstNode == nullptr;
}

bool Board::isSolved() {
	if (this->firstNode == nullptr) {
		return false;
	}

	if (this->firstNode->getNumber() != this->MIN_VALUE) {
		for (BoardNode *current : this->nodes) {
			if (current->getNumber() == this->MIN_VALUE) {
				this->firstNode = current;
			}
		}

		if (this->firstNode->getNumber() == this->MIN_VALUE) {
			return false;
		}
	}

	return checkIfNodeSolved(this->firstNode);
}

bool Board::checkIfNodeSolved(BoardNode *node) {
	if (node->getNumber() == this->nodeCount) {
		return true;
	}
	BoardNode *connectedNode = node->getConnectedUpperNode();
	if (connectedNode == nullptr) {
		return false;
	}
	return checkIfNodeSolved(connectedNode);
}

void Board::setNodes(vector<BoardNode*> nodes) {
	this->nodes = nodes;
	this->setUpNodes();
}

void Board::setEastNode(vector<BoardNode*>::size_type i, BoardNode *current) {
	// If node is not in last column
	if (i % this->numberColumns != this->numberColumns - 1) {
		current->setEast(this->nodes[i + 1]);
	}
}

void Board::setWestNode(vector<BoardNode*>::size_type i, BoardNode *current) {
	// If node is not in first column
	if (i % this->numberColumns != 0) {
		current->setWest(this->nodes[i - 1]);
	}
}

void Board::setNorthNode(vector<BoardNode*>::size_type i, BoardNode *current) {
	// If node is not in first row
	if (i > this->numberRows) {
		current->setNorth(this->nodes[i - this->numberColumns]);
	}
}

void Board::setSouthNode(vector<BoardNode*>::size_type i, BoardNode *current) {
	// If node is not in last row
	if (i < this->nodeCount - this->numberRows) {
		current->setSouth(this->nodes[i + this->numberColumns]);
	}
}

void Board::setUpNodes() {
	for (vector<BoardNode*>::size_type i = 0; i < this->nodes.size(); i++) {
		BoardNode *current = this->nodes[i];

		this->setEastNode(i, current);
		this->setWestNode(i, current);
		this->setNorthNode(i, current);
		this->setSouthNode(i, current);

		if (this->firstNode == nullptr
				|| current->getNumber() < this->firstNode->getNumber()) {
			this->firstNode = current;
		}
	}
}

} /* namespace model */
