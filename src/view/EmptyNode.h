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

#include "Node.h"
using namespace model;

#include "Utils.h"

namespace view {

class EmptyNode: public Fl_Int_Input {
private:
	Node* node;
public:
	EmptyNode(int x,int y,int width,int height,const char* title,Node* node);
	virtual ~EmptyNode();

	int handle(int e);
};

} /* namespace view */

#endif /* VIEW_EMPTYNODE_H_ */
