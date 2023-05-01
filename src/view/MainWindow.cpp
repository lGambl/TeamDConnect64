/*
 * MainWindow.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include "MainWindow.h"

namespace view {

MainWindow::MainWindow(int width, int height, const char *title) :
		Fl_Window(width, height, title) {

	this->begin();

	int widthCentering = width / 2;
	int heightCentering = height / 2;

	int itemWidth = 70;
	int itemHeight = 30;

	vector<string> difficulties = { "1", "2", "3", "4", "5" };
	this->puzzleChoice = new Fl_Choice(widthCentering - itemWidth / 2,
			heightCentering - 40, itemWidth, itemHeight, "Puzzle: ");

	for (string current : difficulties) {
		this->puzzleChoice->add(current.c_str());
	}

	this->saveChoice = new Fl_Choice(widthCentering - itemWidth / 2,
			heightCentering - 120, itemWidth, itemHeight, "Saves: ");

	this->continueGameButton = new Fl_Button(
			widthCentering - (itemWidth + 50) / 2, heightCentering - 80,
			itemWidth + 50, itemHeight, "Continue Game");
	this->continueGameButton->callback(cb_showContinue, this);

	this->playNewWindowButton = new Fl_Button(widthCentering - itemWidth / 2,
			heightCentering + 5, itemWidth, itemHeight, "Play");
	this->playNewWindowButton->callback(cb_show, this);

	this->scoreboardButton = new Fl_Button(
			widthCentering - (itemWidth + 20) / 2, heightCentering + 50,
			itemWidth + 20, itemHeight, "Scoreboard");
	this->scoreboardButton->callback(cb_scoreboard, this);

	this->quitButton = new Fl_Button(widthCentering - itemWidth / 2,
			heightCentering + 100, itemWidth, itemHeight, "Quit");
	this->quitButton->callback(cb_quit, this);

	this->checkSaves();

	this->end();
	this->resizable(this);
	this->show();

	SaveHandler formatter;
	this->highScores = formatter.loadRecords();
}

MainWindow::~MainWindow() {
}

void MainWindow::saveRecords() {
	SaveHandler formatter;
	formatter.saveRecords(this->highScores);
}

void MainWindow::cb_show(Fl_Widget *o, void *data) {

	int difficulty = ((MainWindow*) data)->puzzleChoice->value();

	if (difficulty < 0) {
		fl_message("%s", "Please select a puzzle to play.");
		return;
	}

	string title = "Puzzle "
			+ toString(difficulty + 1, "Difficuly must be a number.");

	GameWindow *window = new GameWindow(400, 400, title.c_str(), difficulty);
	window->set_modal();
	window->show();
	while (window->shown()) {
		Fl::wait();

		if (window->isComplete()
				&& !window->getGameScore()->getPlayerName().empty()) {
			((MainWindow*) data)->highScores->addRecord(window->getGameScore());

			((MainWindow*) data)->saveRecords();
		}

		if (window->nextGame() && !window->shown()) {
			difficulty++;
			string title = "Puzzle "
					+ toString(difficulty + 1, "Difficuly must be a number.");
			window = new GameWindow(400, 400, title.c_str(), difficulty);
			window->set_modal();
			window->show();
		}
	}

	((MainWindow*) data)->checkSaves();
	((MainWindow*) data)->saveChoice->value(-1);
}

void MainWindow::buildOutput(void *data, int sort) {
	// FIXME: allow selection of sort method and direction.
	Fl_Text_Buffer *scoresBuffer = new Fl_Text_Buffer();

	RecordOutputter formatter;
	string output = formatter.getRecordsOutput(
			((MainWindow*) (data))->highScores, sort);

	scoresBuffer->text(output.c_str());

	this->scoresList->buffer(scoresBuffer);
	this->saveRecords();
}

void MainWindow::cb_scoreboard(Fl_Widget*, void *data) {
	Fl_Window scoreboardWindow(300, 350, "High Scoreboard");

	((MainWindow*) data)->scoreboardSortChoice = new Fl_Choice(125, 15, 100, 30,
			"Sort: ");

	vector<string> sorts = { "Time Ascending", "Time Descending",
			"Name Ascending", "Name Descending", "Level Ascending",
			"Level Descending" };
	for (vector<string>::size_type i = 0; i < sorts.size(); i++) {
		((MainWindow*) data)->scoreboardSortChoice->add(sorts[i].c_str());
	}
	((MainWindow*) data)->scoreboardSortChoice->value(1);
	((MainWindow*) data)->scoreboardSortChoice->callback(
			[](Fl_Widget *w, void *buttonData) {
							((MainWindow*) buttonData)->buildOutput(
									((MainWindow*) buttonData),
									((MainWindow*) buttonData)->scoreboardSortChoice->value());
						}, ((MainWindow*) data));

	Fl_Choice puzzleOptions(125, 50, 100, 30, "Puzzle: ");

	Fl_Box heading(125, 100, 50, 10, "Top 10:");
	((MainWindow*) data)->scoresList = new Fl_Text_Display(75, 125, 150, 150,
			"");

	Fl_Button resetButton(125, 290, 50, 30, "Reset");
	resetButton.callback(
			[](Fl_Widget *w, void *buttonData) {
				delete ((MainWindow*) buttonData)->highScores;
				((MainWindow*) buttonData)->highScores =
						new PlaitedRecordList();

				((MainWindow*) buttonData)->buildOutput(
						((MainWindow*) buttonData),
						((MainWindow*) buttonData)->scoreboardSortChoice->value());
			}, ((MainWindow*) data));

	((MainWindow*) data)->buildOutput(data,
			((MainWindow*) data)->scoreboardSortChoice->value());

	scoreboardWindow.add(((MainWindow*) data)->scoreboardSortChoice);
	scoreboardWindow.add(puzzleOptions);
	scoreboardWindow.add(heading);
	scoreboardWindow.add(((MainWindow*) data)->scoresList);
	scoreboardWindow.add(resetButton);

	scoreboardWindow.set_modal();
	scoreboardWindow.show();

	while (scoreboardWindow.shown()) {
		Fl::wait();
	}
}

void MainWindow::cb_quit(Fl_Widget*, void *data) {
	((MainWindow*) data)->cb_quit_i();
}

void MainWindow::cb_quit_i() {
	this->hide();
}

void MainWindow::checkSaves() {
	SaveHandler saver = SaveHandler();

	this->saveChoice->clear();
	this->saves = saver.getSaves();
	for (string save : saver.getSaves()) {
		this->saveChoice->add(save.c_str());
	}

}

void MainWindow::cb_showContinue(Fl_Widget*, void *data) {
	int choice = ((MainWindow*) data)->saveChoice->value();

	if (choice < 0) {
		fl_message("%s", "Please select a  save to continue.");
		return;
	}

	string puzzle = ((MainWindow*) data)->saves[choice];

	GameWindow *window = new GameWindow(400, 400, puzzle.c_str(), puzzle);
	window->set_modal();
	window->show();
	while (window->shown())
		Fl::wait();
}

} /* namespace view */
