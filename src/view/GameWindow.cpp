/*
 * GameWindow.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include <GameWindow.h>

namespace view {

GameWindow::GameWindow(int width, int height, const char *title, int difficulty) :
		Fl_Window(width, height, title) {
	if (width < MINIMUM_SIZE) {
		throw std::invalid_argument(
				"Width must be greater than or equal to " + MINIMUM_SIZE);
	}

	if (height < MINIMUM_SIZE) {
		throw std::invalid_argument(
				"Height must be greater than or equal to " + MINIMUM_SIZE);
	}

	this->board = new Board();
	this->board->loadBoard(difficulty);

	this->nodes = this->board->getNodes();

	this->numberRows = this->board->getNumberRows();
	this->numberColumns = this->board->getNumberColumns();
	int maxNumber = this->numberColumns * this->numberRows;

	Fl_Fontsize inputBoxFontSize = calculateSizes(width, height);

	this->begin();

	this->buildNodeSquares(maxNumber, inputBoxFontSize);

	this->puzzleTitle = "Puzzle "
			+ toString(difficulty + 1, "Invalid difficulty value");
	this->timer = new Fl_Output(this->middleX, this->timerY,
			this->otherObjectsWidth, this->otherObjectsHeight, "");
	this->timer->value(this->puzzleTitle.c_str());
	this->timer->align(FL_ALIGN_CENTER);

	this->closeButton = new Fl_Button(
			this->middleX - this->otherObjectsWidth - 5, this->closeButtonY,
			this->otherObjectsWidth, this->otherObjectsHeight, "Close");
	this->closeButton->callback(cb_close, this);

	this->checkButton = new Fl_Button(this->middleX, this->closeButtonY,
			this->otherObjectsWidth, this->otherObjectsHeight, "Check");
	this->checkButton->callback(cb_check, this);

	this->checkButton = new Fl_Button(
			this->middleX + this->otherObjectsWidth + 5, this->closeButtonY,
			this->otherObjectsWidth, this->otherObjectsHeight, "Reset");
	this->checkButton->callback(cb_reset, this);

	this->end();
	this->size_range(MINIMUM_SIZE, MINIMUM_SIZE);
	this->resizable(this);
}

GameWindow::GameWindow(int width, int height, const char *title, string& save) :
		Fl_Window(width, height, title) {
	if (width < MINIMUM_SIZE) {
		throw std::invalid_argument(
				"Width must be greater than or equal to " + MINIMUM_SIZE);
	}

	if (height < MINIMUM_SIZE) {
		throw std::invalid_argument(
				"Height must be greater than or equal to " + MINIMUM_SIZE);
	}

	this->board = new Board();

	SaveHandler saver = SaveHandler();

	this->nodes = saver.loadSave(save);

	this->board->setNodes(this->nodes);

	this->numberRows = this->board->getNumberRows();
	this->numberColumns = this->board->getNumberColumns();
	int maxNumber = this->numberColumns * this->numberRows;

	Fl_Fontsize inputBoxFontSize = calculateSizes(width, height);

	this->begin();

	this->buildNodeSquares(maxNumber, inputBoxFontSize);

	this->puzzleTitle = save;
	this->timer = new Fl_Output(this->middleX, this->timerY,
			this->otherObjectsWidth, this->otherObjectsHeight, "");
	this->timer->value(this->puzzleTitle.c_str());
	this->timer->align(FL_ALIGN_CENTER);

	this->closeButton = new Fl_Button(
			this->middleX - this->otherObjectsWidth - 5, this->closeButtonY,
			this->otherObjectsWidth, this->otherObjectsHeight, "Close");
	this->closeButton->callback(cb_close, this);

	this->checkButton = new Fl_Button(this->middleX, this->closeButtonY,
			this->otherObjectsWidth, this->otherObjectsHeight, "Check");
	this->checkButton->callback(cb_check, this);

	this->checkButton = new Fl_Button(
			this->middleX + this->otherObjectsWidth + 5, this->closeButtonY,
			this->otherObjectsWidth, this->otherObjectsHeight, "Reset");
	this->checkButton->callback(cb_reset, this);

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

	int index = 0;
	for (int i = 0; i < numberColumns; i++) {
		for (int j = 0; j < numberRows; j++) {

			int inputX = j * this->inputBoxWidth + this->widthCentering;
			int inputY = i * this->inputBoxHeight + this->heightCentering;

			Node *newNode = this->nodes[index++];

			Fl_Widget *newControl;
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
	delete this->board;
}

void GameWindow::cb_close(Fl_Widget*, void *data) {
	((GameWindow*) data)->saveGame();
	((GameWindow*) data)->hide();
}

void GameWindow::saveGame() {
	SaveHandler saver = SaveHandler();
	saver.saveGame(this->puzzleTitle, this->nodes);
}

void GameWindow::cb_check(Fl_Widget*, void *data) {
	cout << ((GameWindow*) data)->board->isSolved() << endl;
}

void GameWindow::cb_reset(Fl_Widget*, void *data) {
	vector<Fl_Widget*> widgets = ((GameWindow*) data)->gameBoard;

//	for (Fl_Widget* current : widgets) {
//		try {
//			EmptyNode* currentEmptyNode = current;
//		} catch (const char* message) {
//
//		}
//	}
}

} /* namespace view */
