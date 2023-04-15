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

}

Board::~Board() {
	delete this->firstNode;
}

bool Board::loadBoard(vector<Node*> nodes) {
	for (Node *node : nodes) {

		for (Node *secondaryNode : nodes) {
			if (node == secondaryNode) {
				continue;
			}
			if (node->getXpos() == secondaryNode->getXpos() - 1) {
				node->setWest(secondaryNode);
			}
			if (node->getXpos() == secondaryNode->getXpos() + 1) {
				node->setEast(secondaryNode);
			}
			if (node->getYpos() == secondaryNode->getYpos() + 1) {
				node->setNorth(secondaryNode);
			}
			if (node->getYpos() == secondaryNode->getYpos() - 1) {
				node->setSouth(secondaryNode);
			}
		}
	}
	return this->firstNode == nullptr;
}

bool Board::isSolved() {
	if (this->firstNode == nullptr) {
		return false;
	}
	return checkIfNodeSolved(this->firstNode);
}

bool Board::checkIfNodeSolved(Node *node) {
	if (node->getNumber() == this->MAX_VALUE) {
		return true;
	}
	Node *connectedNode = node->getConnectedUpperNode();
	if (connectedNode == nullptr) {
		return false;
	}
	return checkIfNodeSolved(connectedNode);
}

} /* namespace model */
