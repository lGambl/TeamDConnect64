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
	this->difficulty = difficulty;

	this->nodes = this->board->getNodes();

	this->puzzleTitle = "Puzzle " + toString(difficulty + 1, "Difficuly must be a number.");
	this->buildDisplay(width, height);
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

	this->puzzleTitle = save;
	this->buildDisplay(width, height);
}

void GameWindow::buildDisplay(int width, int height) {
	this->result = false;

	this->timerCount = 0;
	Fl::add_timeout(1.0, cb_timer, this);

	this->numberRows = this->board->getNumberRows();
	this->numberColumns = this->board->getNumberColumns();
	int maxNumber = this->numberColumns * this->numberRows;

	Fl_Fontsize inputBoxFontSize = calculateSizes(width, height);

	this->begin();

	this->buildNodeSquares(maxNumber, inputBoxFontSize);

	this->timerOutput = new Fl_Output(this->middleX, this->timerY,
			this->otherObjectsWidth, this->otherObjectsHeight, "");
	this->timerOutput->value("00:00");
	this->timerOutput->align(FL_ALIGN_CENTER);

	this->closeButton = new Fl_Button(
			this->middleX - this->otherObjectsWidth * 2 - 5, this->closeButtonY,
			this->otherObjectsWidth, this->otherObjectsHeight, "Close");
	this->closeButton->callback(cb_close, this);

	this->checkButton = new Fl_Button(this->middleX - this->otherObjectsWidth / 2 - 15, this->closeButtonY,
			this->otherObjectsWidth, this->otherObjectsHeight, "Check");
	this->checkButton->callback(cb_check, this);

	this->resetButton = new Fl_Button(
			this->middleX + this->otherObjectsWidth * 2 + 5, this->closeButtonY,
			this->otherObjectsWidth, this->otherObjectsHeight, "Reset");
	this->resetButton->callback(cb_reset, this);

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
			if (newNode->getPreset()) {
				newControl = new ExistingNode(inputX, inputY,
						this->inputBoxWidth, this->inputBoxHeight, newNode);
			} else {
				newControl = new EmptyNode(inputX, inputY, this->inputBoxWidth,
						this->inputBoxHeight, "", maxNumber, newNode);
			}

			this->gameBoard.push_back(newControl); // FIXME: Fix font size
		}
	}

}

GameWindow::~GameWindow() {
	delete this->board;
}

bool GameWindow::nextGame() {
	return this->result;
}

void GameWindow::enableNextGame() {
	this->result = true;
}

void GameWindow::timer_update() {
	this->timerCount++;

	int minutes = this->timerCount / 60;
	int seconds = this->timerCount % 60;

	stringstream ss;
	ss << setw(2) << setfill('0') << seconds;
	string secondsString = ss.str();

	stringstream ms;
	ms << setw(2) << setfill('0') << minutes;
	string minutesString = ms.str();

	string timerOutputString = minutesString + ":" + secondsString;
	this->timerOutput->value(timerOutputString.c_str());
}

void GameWindow::cb_timer(void* data) {
	((GameWindow*) data)->timer_update();
	Fl::add_timeout(1.0, cb_timer, ((GameWindow*) data));
}

void GameWindow::cb_pause(Fl_Widget*, void *data) {
	Fl_Window* pauseDialog = new Fl_Window(300, 150,
				"Puzzle Complete");

	Fl_Button ok_button(50, 50, 100, 30, "Continue Puzzle");
	ok_button.callback([](Fl_Widget *w, void *buttonData) {
		((Fl_Window*) buttonData)->hide();
	} , pauseDialog);

	pauseDialog->show();

	while (pauseDialog->shown()) {
		Fl::wait();
	}
}

void GameWindow::cb_close(Fl_Widget*, void *data) {
	((GameWindow*) data)->saveGame();
	((GameWindow*) data)->hide();
}

void GameWindow::saveGame() {
	SaveHandler saver = SaveHandler();
	saver.saveGame(this->puzzleTitle, this->nodes);
}

void GameWindow::displayCompleteDialog() {
	Fl_Window *puzzleCompleteDialog = new Fl_Window(300, 150,
			"Puzzle Complete");

	bool result = false;

	Fl_Button ok_button(50, 50, 100, 30, "Next Puzzle");
	ok_button.callback([](Fl_Widget *w, void *buttonData) {
		*((bool*) (buttonData)) = true;
		((Fl_Window*) (w->parent()))->hide();
	} , &result);

	puzzleCompleteDialog->add(ok_button);

	if (this->difficulty >= 3) {
		ok_button.hide();
	}

	Fl_Button cancel_button(150, 50, 100, 30, "Stop Playing");
	cancel_button.callback([](Fl_Widget *w, void *buttonData) {
		*((bool*) (buttonData)) = false;
		((Fl_Window*) (w->parent()))->hide();
	} , &result);

	puzzleCompleteDialog->add(cancel_button);
	puzzleCompleteDialog->set_modal();
	puzzleCompleteDialog->show();

	while (puzzleCompleteDialog->shown()) {
		Fl::wait();
	}

	this->hide();

	if (result) {
		this->enableNextGame();
	}
}

void GameWindow::cb_check(Fl_Widget*, void *data) {
	GameWindow* gameData = ((GameWindow*) data);
	if (gameData->board->isSolved()) {
		((GameWindow*) data)->displayCompleteDialog();
	}
	else {
		fl_message("%s", "Puzzle incomplete!");
	}
}

void GameWindow::cb_reset(Fl_Widget*, void *data) {
	vector<Fl_Widget*> widgets = ((GameWindow*) data)->gameBoard;

	for (Fl_Widget* current : widgets) {
		if (EmptyNode* newValue = dynamic_cast<EmptyNode*>(current)) {
			newValue->reset();
		}
	}
}

} /* namespace view */
