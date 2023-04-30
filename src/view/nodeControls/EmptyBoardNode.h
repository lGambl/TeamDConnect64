/*
 * EmptyNode.h
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#ifndef VIEW_EMPTYBOARDNODE_H_
#define VIEW_EMPTYBOARDNODE_H_

#include <FL/Fl_Int_Input.H>
#include <FL/fl_ask.H>

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include <BoardNode.h>
using namespace model;

#include "Utils.h"

#include "GameWindow.h"

namespace view {

class EmptyBoardNode: public Fl_Int_Input {
private:
	BoardNode *node;
	int maxNumber;

	void valueOutOfBounds();
public:
	/**
	 * Initializes an existing node control.
	 *
	 * @precondition none
	 * @postcondition this->node = node
	 *
	 * @param x The x position of the window.
	 * @param y The y position of the window.
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param tag The tag for the input box.
	 * @param node The node the control refers to.
	 */
	EmptyBoardNode(int x, int y, int width, int height, const char *tag, int maxNumber, BoardNode *node);

	/**
	 * Deconstructor for the existing node control.
	 */
	virtual ~EmptyBoardNode();

	/**
	 * Handles events fired from input box.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param e Integer representing the event fired.
	 */
	int handle(int e);

	/**
	 * Rests the node.
	 *
	 * @precondition none
	 * @postcondition this->node->getNumber() = -1
	 */
	void reset();
};

} /* namespace view */

#endif /* VIEW_EMPTYNODE_H_ */
