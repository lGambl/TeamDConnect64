/*
 * EmptyNode.h
 *
 *  Created on: Apr 11, 2023
 *      Author: steven
 */

#ifndef VIEW_EMPTYNODE_H_
#define VIEW_EMPTYNODE_H_

#include <FL/Fl_Int_Input.H>
#include <FL/fl_ask.H>

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

namespace view {

class EmptyNode: public Fl_Int_Input {
public:
	EmptyNode(int x,int y,int width,int height,const char* title);
	virtual ~EmptyNode();

	int handle(int e);
};

} /* namespace view */

#endif /* VIEW_EMPTYNODE_H_ */
