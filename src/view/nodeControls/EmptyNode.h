/*
 * EmptyNode.h
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#ifndef VIEW_EMPTYNODE_H_
#define VIEW_EMPTYNODE_H_

#include <FL/Fl_Int_Input.H>
#include <FL/fl_ask.H>

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "Node.h"
using namespace model;

#include "Utils.h"

#include "GameWindow.h"

namespace view {

class EmptyNode: public Fl_Int_Input {
private:
	Node *node;
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
	EmptyNode(int x, int y, int width, int height, const char *tag, int maxNumber, Node *node);

	/**
	 * Deconstructor for the existing node control.
	 */
	virtual ~EmptyNode();

	/**
	 * Handles events fired from input box.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param e Integer representing the event fired.
	 */
	int handle(int e);
};

} /* namespace view */

#endif /* VIEW_EMPTYNODE_H_ */
