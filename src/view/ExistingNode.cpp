/*
 * ExistingNode.cpp
 *
 *  Created on: Apr 11, 2023
 *      Author: steven
 */

#include <ExistingNode.h>

namespace view {

ExistingNode::ExistingNode(int x,int y,int width, int height) : Fl_Text_Display(x,y,width,height) {
	Fl_Text_Buffer* boxTextBuffer = new Fl_Text_Buffer();
	this->buffer(boxTextBuffer);
	boxTextBuffer->text("-10");

//	try {
//		string nodeNumber = toString(this->node->getNumber(), "Node does not contain a number.");
//		boxTextBuffer->text(nodeNumber.c_str());
//	}
//	catch (const char* message)
//	{
//		fl_message("%s", message);
//	}
}

ExistingNode::~ExistingNode() {
	// TODO Auto-generated destructor stub
}

} /* namespace view */
