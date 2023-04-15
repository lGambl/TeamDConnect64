/*
 * Node.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include "Node.h"

namespace model {

Node::Node(int number, int xpos, int ypos) {
	this->number = number;
	this->xpos = xpos;
	this->ypos = ypos;

	this->north = nullptr;
	this->east = nullptr;
	this->south = nullptr;
	this->west = nullptr;
}

Node::~Node() {
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

bool Node::isConnected() {
	int north = this->getNorth()->number;
	int south = this->getSouth()->number;
	int west = this->getWest()->number;
	int east = this->getEast()->number;

	bool hasLowerNode = false;
	bool hasUpperNode = false;

	if (north == this->number + 1) {
		if (!hasUpperNode) {
			hasUpperNode = true;
		} else {
			return false;
		}
	} else if (north == this->number - 1) {
		if (!hasLowerNode) {
			hasLowerNode = true;
		}
	}
	if (south == this->number + 1) {
		if (!hasUpperNode) {
			hasUpperNode = true;
		} else {
			return false;
		}
	} else if (south == this->number - 1) {
		if (!hasLowerNode) {
			hasLowerNode = true;
		} else {
			return false;
		}
	}
	if (east == this->number + 1) {
		if (!hasUpperNode) {
			hasUpperNode = true;
		} else {
			return false;
		}
	} else if (east == this->number - 1) {
		if (!hasLowerNode) {
			hasLowerNode = true;
		} else {
			return false;
		}
	}
	if (west == this->number + 1) {
		if (!hasUpperNode) {
			hasUpperNode = true;
		} else {
			return false;
		}
	} else if (west == this->number - 1) {
		if (!hasLowerNode) {
			hasLowerNode = true;
		} else {
			return false;
		}
	}

	return hasLowerNode && hasUpperNode;

}

Node* Node::getConnectedUpperNode() {
	if (this->isConnected()) {
		if (this->north->getNumber() == this->number + 1) {
			return this->north;
		}
		if (this->south->getNumber() == this->number + 1) {
			return this->south;
		}
		if (this->east->getNumber() == this->number + 1) {
			return this->east;
		}
		if (this->west->getNumber() == this->number + 1) {
			return this->west;
		}
	}
	return nullptr;
}

} /* namespace model */
