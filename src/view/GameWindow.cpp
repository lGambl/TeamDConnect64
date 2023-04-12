/*
 * NewWindow.cpp
 *
 *  Created on: Mar 15, 2023
 *      Author: dyoder
 */

#include <GameWindow.h>

namespace view {

GameWindow::GameWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
	if (width < 300) {
		throw std::invalid_argument("Width must be greater than or equal to 300");
	}

	if (height < 300) {
		throw std::invalid_argument("Height must be greater than or equal to 300");
	}

	this->numberRows = 8;
	this->numberColumns = 8;

	int inputBoxWidth = (width/4 * 3) / this->numberColumns;
	int inputBoxHeight = (height/4 * 3) / this->numberRows;
	Fl_Fontsize inputBoxFontSize = 12;

	int closeButtonWidth = 70;
	int closeButtonHeight = 30;

	int widthCenteringFactor = ((inputBoxWidth + 1) * (numberColumns / 2)); // FIXME: Doesn't center when different number of columns
	int widthCentering = (width / 2) - widthCenteringFactor;
	int heightCenteringFactor = ((inputBoxHeight + 1) * (numberColumns / 2)); // FIXME: Doesn't center when different number of rows
	int heightCentering = (height / 2) - heightCenteringFactor;

	int closeButtonX = width / 2 - (closeButtonWidth / 2);
	int closeButtonY = height - heightCentering - (closeButtonHeight / (this->numberColumns/2)) + 5; // FIXME: Doesn't align properly when altering size of grid

    this->begin();

    for (int i = 0; i < numberRows; i++) {
    	for (int j = 0; j < numberColumns; j++) {
    		int inputX = i * inputBoxWidth + widthCentering;
    		int inputY = j * inputBoxHeight + heightCentering;

    		int nodeNumber = -1;
    		if (i == 7) {
    			nodeNumber = 12;
    		}
    		Node* newNode = new Node(nodeNumber); // FIXME: Replace this with retrieval of next node to display

    		if (newNode->getNumber() < 1) {
    			EmptyNode* newEmptyBox = new EmptyNode(inputX, inputY, inputBoxWidth, inputBoxHeight, "", newNode);
    			newEmptyBox->textsize(inputBoxFontSize++); // FIXME: Fix font size
    			this->gameBoard.push_back(newEmptyBox);
    		}
    		else {
    			ExistingNode* newBox = new ExistingNode(inputX, inputY, inputBoxWidth, inputBoxHeight, newNode);
        		this->gameBoard.push_back(newBox); // FIXME: Fix font size
    		}
    	}
    }

    this->closeButton = new Fl_Button(closeButtonX, closeButtonY, closeButtonWidth, closeButtonHeight, "Close");
    this->closeButton->callback(cb_close, this);
    this->end();
    this->resizable(this);
}

GameWindow::~GameWindow()
{
}

void GameWindow::cb_close(Fl_Widget* , void* data)
{
    ((GameWindow*)data)->hide();
}

} /* namespace view */
