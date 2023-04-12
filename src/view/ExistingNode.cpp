/*
 * ExistingNode.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include <ExistingNode.h>

namespace view {

ExistingNode::ExistingNode(int x, int y, int width, int height, Node *node) :
		Fl_Text_Display(x, y, width, height) {
	this->node = node;

	this->boxTextBuffer = new Fl_Text_Buffer();
	this->buffer(this->boxTextBuffer);

	try {
		string nodeNumber = toString(this->node->getNumber(),
				"Node does not contain a number.");
		boxTextBuffer->text(nodeNumber.c_str());
	} catch (const char *message) {
		fl_message("%s", message);
	}
}

ExistingNode::~ExistingNode() {
	delete this->boxTextBuffer;
}

} /* namespace view */
