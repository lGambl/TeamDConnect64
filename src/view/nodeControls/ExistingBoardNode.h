/*
 * ExistingNode.h
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#ifndef VIEW_EXISTINGBOARDNODE_H_
#define VIEW_EXISTINGBOARDNODE_H_

#include <BoardNode.h>
#include <FL/Fl_Output.H>
#include <FL/fl_ask.H>

using namespace model;

#include "Utils.h"

namespace view {

class ExistingBoardNode: public Fl_Output {
private:
	BoardNode *node;
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
	 * @param node The node the control refers to.
	 */
	ExistingBoardNode(int x, int y, int width, int height, BoardNode *node);

	/**
	 * Deconstructor for the existing node control.
	 */
	virtual ~ExistingBoardNode();
};

} /* namespace view */

#endif /* VIEW_EXISTINGNODE_H_ */
