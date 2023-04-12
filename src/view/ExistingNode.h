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

namespace view {

class ExistingNode : Fl_Text_Display {
public:
	ExistingNode(int x,int y,int width, int height);
	virtual ~ExistingNode();
};

} /* namespace view */

#endif /* VIEW_EXISTINGNODE_H_ */
