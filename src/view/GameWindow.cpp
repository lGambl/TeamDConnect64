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

	this->puzzleTitle = "Puzzle " + to_string(difficulty + 1);
	this->buildDisplay(width, height);
}

GameWindow::GameWindow(int width, int height, const char *title, string &save) :
		Fl_Window(width, height, title) {
	if (width < MINIMUM_SIZE) {
		throw std::invalid_argument(
				"Width must be greater than or equal to " + MINIMUM_SIZE);
	}

	if (height < MINIMUM_SIZE) {
		throw std::invalid_argument(
				"Height must be greater than or equal to " + MINIMUM_SIZE);
	}

	SaveHandler saver = SaveHandler();

	this->board = saver.loadSave(save);
	this->nodes = this->board->getNodes();

	this->puzzleTitle = save;
	this->buildDisplay(width, height);

	this->timer_update();
}

void GameWindow::buildDisplay(int width, int height) {
	this->result = false;
	this->complete = false;

	Fl::add_timeout(1.0, cb_timer, this);

	this->numberRows = this->board->getNumberRows();
	this->numberColumns = this->board->getNumberColumns();
	int maxNumber = this->numberColumns * this->numberRows;

	Fl_Fontsize inputBoxFontSize = this->calculateSizes(width, height);

	this->begin();

	this->buildNodeSquares(maxNumber, inputBoxFontSize);

	this->timerOutput = new Fl_Output(this->middleX, this->timerY,
			this->otherObjectsWidth, this->otherObjectsHeight, "");
	this->timerOutput->value("00:00");
	this->timerOutput->align(FL_ALIGN_CENTER);

	this->closeButton = new Fl_Button(
			this->middleX - this->otherObjectsWidth * 2 - 5,
			this->bottomButtonY, this->otherObjectsWidth,
			this->otherObjectsHeight, "Close");
	this->closeButton->callback(cb_close, this);

	this->checkButton = new Fl_Button(
			this->middleX - this->otherObjectsWidth / 2 - 15,
			this->bottomButtonY, this->otherObjectsWidth,
			this->otherObjectsHeight, "Check");
	this->checkButton->callback(cb_check, this);

	this->pauseButton = new Fl_Button(
			this->middleX + this->otherObjectsWidth / 2 + 15,
			this->bottomButtonY, this->otherObjectsWidth,
			this->otherObjectsHeight, "Pause");
	this->pauseButton->callback(cb_pause, this);

	this->resetButton = new Fl_Button(
			this->middleX + this->otherObjectsWidth * 2 + 5,
			this->bottomButtonY, this->otherObjectsWidth,
			this->otherObjectsHeight, "Reset");
	this->resetButton->callback(cb_reset, this);

	this->end();
	this->size_range(MINIMUM_SIZE, MINIMUM_SIZE);
	this->resizable(this);
}

Fl_Fontsize GameWindow::calculateSizes(int width, int height) {
	this->inputBoxWidth = (width / 4 * 3) / this->numberColumns;
	this->inputBoxHeight = (height / 4 * 3) / this->numberRows;

	Fl_Fontsize inputBoxFontSize = 12;

	this->otherObjectsWidth = 70;
	this->otherObjectsHeight = 30;

	this->widthCenteringFactor = ((inputBoxWidth + 1) * (numberColumns / 2));
	this->widthCentering = (width / 2) - widthCenteringFactor;

	this->heightCenteringFactor = ((inputBoxHeight + 1) * (numberColumns / 2));
	this->heightCentering = (height / 2) - heightCenteringFactor;

	this->middleX = width / 2 - (otherObjectsWidth / 2);

	this->bottomButtonY = height - heightCentering
			- (otherObjectsHeight / (this->numberColumns / 2)) + 5;

	this->timerY = heightCentering
			- (otherObjectsHeight / (this->numberColumns / 2)) - 25;

	return inputBoxFontSize;
}

void GameWindow::setColors(Fl_Color cellColor, Fl_Color textColor) {
	for (Fl_Widget *current : this->gameBoard) {
		current->color(cellColor);

		if (EmptyBoardNode *node = dynamic_cast<EmptyBoardNode*>(current)) {
			node->textcolor(textColor);
		}
		else if (ExistingBoardNode *node = dynamic_cast<ExistingBoardNode*>(current)) {
			node->textcolor(textColor);
		}
	}
}

void GameWindow::buildNodeSquares(int maxNumber, Fl_Fontsize inputBoxFontSize) {

	int index = 0;
	for (int i = 0; i < numberColumns; i++) {
		for (int j = 0; j < numberRows; j++) {

			int inputX = j * this->inputBoxWidth + this->widthCentering;
			int inputY = i * this->inputBoxHeight + this->heightCentering;

			BoardNode *newNode = this->nodes[index++];

			Fl_Widget *newControl;
			if (newNode->getPreset()) {
				newControl = new ExistingBoardNode(inputX, inputY,
						this->inputBoxWidth, this->inputBoxHeight, newNode);
			} else {
				newControl = new EmptyBoardNode(inputX, inputY,
						this->inputBoxWidth, this->inputBoxHeight, "",
						maxNumber, newNode);
			}

			this->gameBoard.push_back(newControl);
		}
	}

}

GameWindow::~GameWindow() {
	delete this->board;
}

bool GameWindow::nextGame() {
	return this->result;
}

bool GameWindow::isComplete() {
	return this->complete;
}

void GameWindow::enableNextGame() {
	this->result = true;
}

PlayerRecord* GameWindow::getGameScore() {
	return this->playerRecord;
}

void GameWindow::timer_update() {
	this->board->setTimer(this->board->getTimer() + 1);

	int minutes = this->board->getTimer() / 60;
	int seconds = this->board->getTimer() % 60;

	stringstream ss;
	ss << setw(2) << setfill('0') << seconds;
	string secondsString = ss.str();

	stringstream ms;
	ms << setw(2) << setfill('0') << minutes;
	string minutesString = ms.str();

	string timerOutputString = minutesString + ":" + secondsString;
	this->timerOutput->value(timerOutputString.c_str());
}

void GameWindow::cb_timer(void *data) {
	((GameWindow*) data)->timer_update();

	if (!((GameWindow*) data)->pause) {
		Fl::add_timeout(1.0, cb_timer, ((GameWindow*) data));
	}
}

void GameWindow::cb_pause(Fl_Widget*, void *data) { // FIXME: Refactor or make its own class
	Fl_Window *pauseDialog = new Fl_Window(300, 250, "Puzzle Paused");

	Fl_Button ok_button(75, 95, 150, 30, "Continue Puzzle");
	ok_button.callback([](Fl_Widget *w, void *buttonData) {
		((Fl_Window*) buttonData)->hide();
	}, pauseDialog);

	pauseDialog->set_modal();
	pauseDialog->show();

	while (pauseDialog->shown()) {
		((GameWindow*) data)->pause = true;
		Fl::wait();
	}

	((GameWindow*) data)->pause = false;
	Fl::add_timeout(1.0, cb_timer, ((GameWindow*) data));
}

void GameWindow::cb_close(Fl_Widget*, void *data) {
	((GameWindow*) data)->saveGame();
	((GameWindow*) data)->hide();
}

void GameWindow::saveGame() {
	SaveHandler saver = SaveHandler();
	saver.saveGame(this->puzzleTitle, this->nodes, this->board->getTimer());
}

void GameWindow::displayCompleteDialog() { // FIXME: Refactor or make its own class
	Fl_Window puzzleCompleteDialog(300, 150, "Puzzle Complete");

	Fl_Box heading(125, 25, 50, 10, "Great job!!");

	bool result = false;

	Fl_Button ok_button(50, 50, 100, 30, "Next Puzzle");
	ok_button.callback([](Fl_Widget *w, void *buttonData) {
		*((bool*) (buttonData)) = true;
		((Fl_Window*) (w->parent()))->hide();
	}, &result);

	puzzleCompleteDialog.add(ok_button);

	int stopPlayingX = 150;
	if (this->difficulty >= MainWindow::MAX_DIFFICULTY) {
		ok_button.hide();
		stopPlayingX = 100;
	}

	Fl_Button cancel_button(stopPlayingX, 50, 100, 30, "Stop Playing");
	cancel_button.callback([](Fl_Widget *w, void *buttonData) {
		*((bool*) (buttonData)) = false;
		((Fl_Window*) (w->parent()))->hide();
	}, &result);

	puzzleCompleteDialog.add(cancel_button);
	puzzleCompleteDialog.set_modal();
	puzzleCompleteDialog.show();

	while (puzzleCompleteDialog.shown()) {
		this->pause = true;
		Fl::wait();
	}

	this->hide();

	if (result) {
		this->enableNextGame();
	}
}

string GameWindow::displayUsernameDialog() { // FIXME: Refactor or make its own class
	Fl_Window usernameDialog(300, 100, "Enter Username");
	Fl_Input input(100, 50, 100, 25, "Username:");
	Fl_Box message(100, 20, 100, 25, "Please enter a username below.");

	string username = "";

	Fl_Button submit_button(220, 50, 70, 25, "Submit");
	submit_button.callback([](Fl_Widget *w, void *buttonData) {
		Fl_Window *window = ((Fl_Window*) ((w->parent())));
		Fl_Input *input = (Fl_Input*) (window->child(0));
		*((string*) ((buttonData))) = input->value();
		window->hide();
	}, &username);

	usernameDialog.add(input);
	usernameDialog.add(message);
	usernameDialog.add(submit_button);
	usernameDialog.set_modal();
	usernameDialog.show();

	while (usernameDialog.shown()) {
		Fl::wait();
	}

	return username;
}

void GameWindow::cb_check(Fl_Widget*, void *data) {
	GameWindow *gameData = ((GameWindow*) data);
	if (gameData->board->isSolved()) {
		((GameWindow*) data)->displayCompleteDialog();

		string username = gameData->displayUsernameDialog();

		gameData->playerRecord = new PlayerRecord(gameData->puzzleTitle,
				username, gameData->board->getTimer());

		gameData->complete = true;
	} else {
		fl_message("%s", "Puzzle incomplete!");
	}
}

void GameWindow::cb_reset(Fl_Widget*, void *data) {
	vector<Fl_Widget*> widgets = ((GameWindow*) data)->gameBoard;

	((GameWindow*) data)->board->setTimer(0);

	for (Fl_Widget *current : widgets) {
		if (EmptyBoardNode *newValue = dynamic_cast<EmptyBoardNode*>(current)) {
			newValue->reset();
		}
	}
}

} /* namespace view */
