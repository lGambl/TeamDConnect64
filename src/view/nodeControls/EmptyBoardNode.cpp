/*
 * EmptyNode.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include <EmptyBoardNode.h>

namespace view {

EmptyBoardNode::EmptyBoardNode(int x, int y, int width, int height, const char *tag,
		int maxNumber, BoardNode *node) :
		Fl_Int_Input(x, y, width, height, tag) {
	this->node = node;
	this->maxNumber = maxNumber;

	if (this->node->getNumber() >= 1) {
		this->value(toString(this->node->getNumber(), "Node value is not a number").c_str());
	}
}

EmptyBoardNode::~EmptyBoardNode() {
}

int EmptyBoardNode::handle(int e) {
	int ret = Fl_Input::handle(e); // pass events to subclass first
	switch (e) {
	case FL_KEYBOARD:
		try {
			string valueString = this->value();
			if (valueString.compare("") == 0) {
				break;
			}

			int value = toInt(valueString, "Please enter a positive number.");

			if (value > this->maxNumber || value < 1) {
				this->valueOutOfBounds();
			} else {
				this->node->setNumber(value);
				ret = 1;
			}

			break;
		} catch (const char *message) {
			this->value("");
			fl_message("%s", message);
		} catch (std::invalid_argument const &message) {
			fl_message("%s", message.what());
		}
	}

	return ret; // pass back subclass's handle return code
}

void EmptyBoardNode::valueOutOfBounds() {
	if (this->node->getNumber() >= 1) {
		this->value(
				toString(this->node->getNumber(), "Input must be a number.").c_str());
	} else {
		this->value("");
	}
	string max = toString(this->maxNumber, "Input must be a number.");
	string error = "Number must be between 1 and " + max + ".";
	throw std::invalid_argument(error);
}

void EmptyBoardNode::reset() {
	this->node->setNumber(-1);
	this->value("");
}

} /* namespace view */
