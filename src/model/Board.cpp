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

	this->numberColumns = 8;
	this->numberRows = 8;

	this->nodeCount = this->numberColumns * this->numberRows;
}

Board::~Board() {
	delete this->firstNode;
}

bool Board::loadBoard(int difficulty) {
	FileHandler handler;
	this->nodes = handler.readNodeFile(
			"/home/steven/Documents/CS3202/TeamXConnect64/src/board.txt", // FIXME: Find relative path
			difficulty);

	for (vector<Node*>::size_type i = 0; i < this->nodes.size(); i++) {
		Node *current = this->nodes[i];

		if (i % this->numberColumns != 7) {
			current->setEast(this->nodes[i + 1]);
		}

		if (i % this->numberColumns != 0) {
			current->setWest(this->nodes[i - 1]);
		}

		if (i > this->numberRows) {
			current->setNorth(this->nodes[i - this->numberColumns]);
		}

		if (i < this->nodeCount - this->numberRows) {
			current->setSouth(this->nodes[i + this->numberColumns]);
		}

		if (this->firstNode == nullptr
				|| current->getNumber() < this->firstNode->getNumber()) {
			this->firstNode = current;
		}
	}

	return this->firstNode == nullptr;
}

bool Board::isSolved() {
	if (this->firstNode == nullptr) {
		return false;
	}

	if (this->firstNode->getNumber() != this->MIN_VALUE) {
		for (Node *current : this->nodes) {
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

bool Board::checkIfNodeSolved(Node *node) {
	if (node->getNumber() == this->nodeCount) {
		return true;
	}
	Node *connectedNode = node->getConnectedUpperNode();
	if (connectedNode == nullptr) {
		return false;
	}
	return checkIfNodeSolved(connectedNode);
}

} /* namespace model */
