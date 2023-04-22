/*
 * Node.h
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#ifndef MODEL_NODE_H_
#define MODEL_NODE_H_

namespace model {

class Node {
private:
	int number;
	bool preset;

	Node *north;
	Node *south;
	Node *east;
	Node *west;

public:
	/**
	 * Initializes a node.
	 *
	 * @precondition none
	 * @postcondition this->number = number
	 *
	 * @param number The number the node stores
	 */
	Node(int number, bool preset);

	/**
	 * Deconstructor for the node.
	 */
	virtual ~Node();

	/**
	 * Getter for the number stored in the node.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The number stored in the node
	 */
	int getNumber() {
		return this->number;
	}

	/**
	 * Setter for the number stored in the node.
	 *
	 * @precondition none
	 * @postcondition this->number = number
	 *
	 * @param number The new number to store in the node
	 */
	void setNumber(int number) {
		this->number = number;
	}

	/**
	 * Getter for the preset stored in the node.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The preset stored in the node
	 */
	bool getPreset() {
		return this->preset;
	}

	/**
	 * Setter for the preset stored in the node.
	 *
	 * @precondition none
	 * @postcondition this->preset = preset
	 *
	 * @param preset The new preset to store in the node
	 */
	void setPreset(bool preset) {
		this->preset = preset;
	}

	/**
	 * Getter for the east node pointer.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The pointer to the node to the east
	 */
	Node*& getEast() {
		return this->east;
	}

	/**
	 * Setter for the east node pointer.
	 *
	 * @precondition none
	 * @postcondition this->east = east
	 *
	 * @param west The new east node pointer
	 */
	void setEast(Node *&east) {
		this->east = east;
	}

	/**
	 * Getter for the north node pointer.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The pointer to the node to the north
	 */
	Node*& getNorth() {
		return this->north;
	}

	/**
	 * Setter for the north node pointer.
	 *
	 * @precondition none
	 * @postcondition this->north = north
	 *
	 * @param west The new north node pointer
	 */
	void setNorth(Node *&north) {
		this->north = north;
	}

	/**
	 * Getter for the south node pointer.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The pointer to the node to the south
	 */
	Node*& getSouth() {
		return this->south;
	}

	/**
	 * Setter for the south node pointer.
	 *
	 * @precondition none
	 * @postcondition this->south = south
	 *
	 * @param west The new south node pointer
	 */
	void setSouth(Node *&south) {
		this->south = south;
	}

	/**
	 * Getter for the west node pointer.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The pointer to the node to the west
	 */
	Node*& getWest() {
		return this->west;
	}

	/**
	 * Setter for the west node pointer.
	 *
	 * @precondition none
	 * @postcondition this->west = west
	 *
	 * @param west The new west node pointer
	 */
	void setWest(Node *&west) {
		this->west = west;
	}

	/**
	 * Checks if the node is connect to other nodes correctly
	 *
	 * @pre none
	 * @post none
	 *
	 * @return true if connect correctly, false if not
	 */
	bool isConnected();

	/**
	 * Gets the node that next if the node is connected properly
	 *
	 * @pre none
	 * @post none
	 *
	 * @return the connected node if there is one. If not return nullptr.
	 */
	Node* getConnectedUpperNode();
};

} /* namespace model */

#endif /* MODEL_NODE_H_ */
