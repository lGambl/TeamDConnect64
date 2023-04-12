/*
 * EmptyNode.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include <EmptyNode.h>

namespace view {

EmptyNode::EmptyNode(int x, int y, int width, int height, const char *tag,
		Node *node) :
		Fl_Int_Input(x, y, width, height, tag) {
	this->node = node;
}

EmptyNode::~EmptyNode() {
}

int EmptyNode::handle(int e) {
	int ret = Fl_Input::handle(e); // pass events to subclass first
	switch (e) {
	case FL_KEYBOARD:
		try {
			string valueString = this->value();
			if (valueString.compare("") == 0) {
				break;
			}

			int value = toInt(valueString, "Please enter a number.");
			this->node->setNumber(value);
			ret = 1;
			break;
		} catch (const char *message) {
			fl_message("%s", message);
		}
	}
	return ret; // pass back subclass's handle return code
}

} /* namespace view */
