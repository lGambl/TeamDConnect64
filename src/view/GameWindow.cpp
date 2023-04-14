/*
 * GameWindow.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include <GameWindow.h>

namespace view {

GameWindow::GameWindow(int width, int height, const char *title) :
		Fl_Window(width, height, title) {
	if (width < MINIMUM_SIZE) {
		throw std::invalid_argument(
				"Width must be greater than or equal to " + MINIMUM_SIZE);
	}

	if (height < MINIMUM_SIZE) {
		throw std::invalid_argument(
				"Height must be greater than or equal to " + MINIMUM_SIZE);
	}

	this->numberRows = 8;
	this->numberColumns = 8;
	int maxNumber = this->numberColumns * this->numberRows;

	Fl_Fontsize inputBoxFontSize = calculateSizes(width, height);

	this->begin();

	this->buildNodeSquares(maxNumber, inputBoxFontSize);

	this->timer = new Fl_Output(this->middleX, this->timerY,
			this->otherObjectsWidth, this->otherObjectsHeight, "");

	this->closeButton = new Fl_Button(this->middleX, this->closeButtonY,
			this->otherObjectsWidth, this->otherObjectsHeight, "Close");
	this->closeButton->callback(cb_close, this);

	this->end();
	this->size_range(MINIMUM_SIZE, MINIMUM_SIZE);
	this->resizable(this);
}

Fl_Fontsize GameWindow::calculateSizes(int width, int height) { // FIXME: Doesn't center when different number of columns
	this->inputBoxWidth = (width / 4 * 3) / this->numberColumns;
	this->inputBoxHeight = (height / 4 * 3) / this->numberRows;

	Fl_Fontsize inputBoxFontSize = 12; // FIXME: Calculate font size

	this->otherObjectsWidth = 70;
	this->otherObjectsHeight = 30;

	this->widthCenteringFactor = ((inputBoxWidth + 1) * (numberColumns / 2));
	this->widthCentering = (width / 2) - widthCenteringFactor;

	this->heightCenteringFactor = ((inputBoxHeight + 1) * (numberColumns / 2));
	this->heightCentering = (height / 2) - heightCenteringFactor;

	this->middleX = width / 2 - (otherObjectsWidth / 2);

	this->closeButtonY = height - heightCentering
			- (otherObjectsHeight / (this->numberColumns / 2)) + 5;

	this->timerY = heightCentering
			- (otherObjectsHeight / (this->numberColumns / 2)) - 25;

	return inputBoxFontSize;
}

void GameWindow::buildNodeSquares(int maxNumber, Fl_Fontsize inputBoxFontSize) {

	for (int i = 0; i < numberRows; i++) {
		for (int j = 0; j < numberColumns; j++) {

			int inputX = i * this->inputBoxWidth + this->widthCentering;
			int inputY = j * this->inputBoxHeight + this->heightCentering;

			Node *newNode = new Node(-1); // FIXME: Replace this with retrieval of next node to display (<1 gives input box and >1 gives display box)

			void *newControl;
			if (newNode->getNumber() < 1) {
				newControl = new EmptyNode(inputX, inputY, this->inputBoxWidth,
						this->inputBoxHeight, "", maxNumber, newNode);

			} else {
				newControl = new ExistingNode(inputX, inputY,
						this->inputBoxWidth, this->inputBoxHeight, newNode);

			}

			this->gameBoard.push_back(newControl); // FIXME: Fix font size
		}
	}
}

GameWindow::~GameWindow() {
}

void GameWindow::cb_close(Fl_Widget*, void *data) {
	((GameWindow*) data)->hide();
}

} /* namespace view */
