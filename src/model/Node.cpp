/*
 * Node.cpp
 *
 *  Created on: Apr 11, 2023
 *      Author: steven
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
	// TODO Auto-generated destructor stub
}

} /* namespace model */
