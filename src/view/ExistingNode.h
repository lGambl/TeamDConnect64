/*
 * ExistingNode.h
 *
 *  Created on: Apr 11, 2023
 *      Author: steven
 */

#ifndef VIEW_EXISTINGNODE_H_
#define VIEW_EXISTINGNODE_H_

#include <FL/Fl_Text_Display.H>
#include <FL/fl_ask.H>

#include "Node.h"
using namespace model;

#include "Utils.h"

namespace view {

class ExistingNode : Fl_Text_Display {
private:
	Node* node;
public:
	ExistingNode(int x,int y,int width, int height,Node* node);
	virtual ~ExistingNode();
};

} /* namespace view */

#endif /* VIEW_EXISTINGNODE_H_ */
