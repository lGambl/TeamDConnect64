/*
 * Node.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include <BoardNode.h>

namespace model {

BoardNode::BoardNode(int number, bool preset) {
	this->number = number;
	this->preset = preset;

	this->north = nullptr;
	this->east = nullptr;
	this->south = nullptr;
	this->west = nullptr;
}

BoardNode::~BoardNode() {
	this->number = 0;
	if (this->north != nullptr) {
		delete this->north;
	}
	if (this->south != nullptr) {
		delete this->south;
	}
	if (this->east != nullptr) {
		delete this->east;
	}
	if (this->west != nullptr) {
		delete this->west;
	}
}

bool BoardNode::checkConnectedNode(BoardNode *nextNode) {

	bool hasUpperNode = false;
	bool hasLowerNode = false;

	if (nextNode != nullptr && nextNode->getNumber() == this->number + 1) {
		hasUpperNode = true;
	} else if (nextNode != nullptr
			&& nextNode->getNumber() == this->number - 1) {
		hasLowerNode = true;
	}

	return hasUpperNode && hasLowerNode;
}

bool BoardNode::isConnected() {

	bool isNorth = this->checkConnectedNode(this->north);
	bool isSouth = this->checkConnectedNode(this->south);
	bool isEast = this->checkConnectedNode(this->east);
	bool isWest = this->checkConnectedNode(this->west);

	return isNorth && isSouth && isEast && isWest;

}

BoardNode* BoardNode::getConnectedUpperNode() {
	if (this->north != nullptr
			&& this->north->getNumber() == this->number + 1) {
		return this->north;
	}
	if (this->south != nullptr
			&& this->south->getNumber() == this->number + 1) {
		return this->south;
	}
	if (this->east != nullptr && this->east->getNumber() == this->number + 1) {
		return this->east;
	}
	if (this->west != nullptr && this->west->getNumber() == this->number + 1) {
		return this->west;
	} else {
		return nullptr;
	}
}

} /* namespace model */
