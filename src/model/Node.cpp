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
	// TODO: Delete all nodes when done.
}

} /* namespace model */
