/*
 * Node.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include "Node.h"

namespace model {

Node::Node(int number) {
	this->number = number;

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
	bool hasLowerNode = false;
	bool hasUpperNode = false;

	if (this->north != nullptr && this->north->getNumber() == this->number + 1) {
		if (!hasUpperNode) {
			hasUpperNode = true;
		} else {
			return false;
		}
	} else if (this->north != nullptr && this->north->getNumber() == this->number - 1) {
		if (!hasLowerNode) {
			hasLowerNode = true;
		}
	}
	if (this->south != nullptr && this->south->getNumber() == this->number + 1) {
		if (!hasUpperNode) {
			hasUpperNode = true;
		} else {
			return false;
		}
	} else if (this->south != nullptr && this->south->getNumber() == this->number - 1) {
		if (!hasLowerNode) {
			hasLowerNode = true;
		} else {
			return false;
		}
	}
	if (this->east != nullptr && this->east->getNumber() == this->number + 1) {
		if (!hasUpperNode) {
			hasUpperNode = true;
		} else {
			return false;
		}
	} else if (this->east != nullptr && this->east->getNumber() == this->number - 1) {
		if (!hasLowerNode) {
			hasLowerNode = true;
		} else {
			return false;
		}
	}
	if (this->west != nullptr && this->west->getNumber() == this->number + 1) {
		if (!hasUpperNode) {
			hasUpperNode = true;
		} else {
			return false;
		}
	} else if (this->west != nullptr && this->west->getNumber() == this->number - 1) {
		if (!hasLowerNode) {
			hasLowerNode = true;
		} else {
			return false;
		}
	}

	return hasLowerNode && hasUpperNode;

}

Node* Node::getConnectedUpperNode() {
//	if (this->isConnected()) {
		if (this->north != nullptr && this->north->getNumber() == this->number + 1) {
			return this->north;
		}
		if (this->south != nullptr && this->south->getNumber() == this->number + 1) {
			return this->south;
		}
		if (this->east != nullptr && this->east->getNumber() == this->number + 1) {
			return this->east;
		}
		if (this->west != nullptr && this->west->getNumber() == this->number + 1) {
			return this->west;
		}
		else {
			return nullptr;
		}
//	}
//	return nullptr;
}

} /* namespace model */
