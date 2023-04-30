/*
 * ExistingNode.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include <ExistingBoardNode.h>

namespace view {

ExistingBoardNode::ExistingBoardNode(int x, int y, int width, int height, BoardNode *node) :
		Fl_Output(x, y, width, height) {
	this->node = node;

	try {
		string nodeNumber = toString(this->node->getNumber(),
				"Node does not contain a number.");
		this->value(nodeNumber.c_str());
	} catch (const char *message) {
		fl_message("%s", message);
	}
}

ExistingBoardNode::~ExistingBoardNode() {
}

} /* namespace view */
