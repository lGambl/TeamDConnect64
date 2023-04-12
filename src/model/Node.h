/*
 * Node.h
 *
 *  Created on: Apr 11, 2023
 *      Author: steven
 */

#ifndef MODEL_NODE_H_
#define MODEL_NODE_H_

namespace model {

class Node {
private:
	int number;

	Node* north;
	Node* south;
	Node* east;
	Node* west;

public:
	Node(int number);
	virtual ~Node();

	Node*& getEast() {
		return this->east;
	}

	void setEast(Node *&east) {
		this->east = east;
	}

	Node*& getNorth() {
		return this->north;
	}

	void setNorth(Node *&north) {
		this->north = north;
	}

	int getNumber() {
		return this->number;
	}

	void setNumber(int number) {
		this->number = number;
	}

	Node*& getSouth() {
		return this->south;
	}

	void setSouth(Node *&south) {
		this->south = south;
	}

	Node*& getWest() {
		return this->west;
	}

	void setWest(Node *&west) {
		this->west = west;
	}
};

} /* namespace model */

#endif /* MODEL_NODE_H_ */
