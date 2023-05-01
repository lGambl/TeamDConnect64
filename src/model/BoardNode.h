/*
 * Node.h
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#ifndef MODEL_BOARDNODE_H_
#define MODEL_BOARDNODE_H_

namespace model {

/**
 * A node class that represents a node of a board
 */
class BoardNode {
private:
	int number;
	bool preset;

	BoardNode *north;
	BoardNode *south;
	BoardNode *east;
	BoardNode *west;

	bool checkConnectedNode(BoardNode *nextNode);

public:
	/**
	 * Initializes a node.
	 *
	 * @precondition none
	 * @postcondition this->number = number
	 *
	 * @param number The number the node stores.
	 * @param preset The node should be changeable or not.
	 */
	BoardNode(int number, bool preset);

	/**
	 * Deconstructor for the node.
	 */
	virtual ~BoardNode();

	/**
	 * Getter for the number stored in the node.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The number stored in the node.
	 */
	int getNumber() {
		return this->number;
	}

	/**
	 * Setter for the number stored in the node.
	 *
	 * @precondition none
	 * @postcondition this->number == number
	 *
	 * @param number The new number to store in the node.
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
	 * @return The preset stored in the node.
	 */
	bool getPreset() {
		return this->preset;
	}

	/**
	 * Setter for the preset stored in the node.
	 *
	 * @precondition none
	 * @postcondition this->preset == preset
	 *
	 * @param preset The new preset to store in the node.
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
	 * @return The pointer to the node to the east.
	 */
	BoardNode*& getEast() {
		return this->east;
	}

	/**
	 * Setter for the east node pointer.
	 *
	 * @precondition none
	 * @postcondition this->east == east
	 *
	 * @param east The new east node pointer.
	 */
	void setEast(BoardNode *&east) {
		this->east = east;
	}

	/**
	 * Getter for the north node pointer.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The pointer to the node to the north.
	 */
	BoardNode*& getNorth() {
		return this->north;
	}

	/**
	 * Setter for the north node pointer.
	 *
	 * @precondition none
	 * @postcondition this->north == north
	 *
	 * @param north The new north node pointer.
	 */
	void setNorth(BoardNode *&north) {
		this->north = north;
	}

	/**
	 * Getter for the south node pointer.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The pointer to the node to the south.
	 */
	BoardNode*& getSouth() {
		return this->south;
	}

	/**
	 * Setter for the south node pointer.
	 *
	 * @precondition none
	 * @postcondition this->south == south
	 *
	 * @param south The new south node pointer.
	 */
	void setSouth(BoardNode *&south) {
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
	BoardNode*& getWest() {
		return this->west;
	}

	/**
	 * Setter for the west node pointer.
	 *
	 * @precondition none
	 * @postcondition this->west == west
	 *
	 * @param west The new west node pointer
	 */
	void setWest(BoardNode *&west) {
		this->west = west;
	}

	/**
	 * Checks if the node is connect to other nodes correctly
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return True if connect correctly, False otherwise
	 */
	bool isConnected();

	/**
	 * Gets the node that next if the node is connected properly
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The connected node if exists, nullptr otherwise.
	 */
	BoardNode* getConnectedUpperNode();
};

} /* namespace model */

#endif /* MODEL_BOARDNODE_H_ */
