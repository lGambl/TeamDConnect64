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

	vector<string> difficulties = { "1", "2", "3", "4", "5", "6", "7" }; // FIXME: Populate
	this->puzzleChoice = new Fl_Choice(widthCentering - itemWidth / 2,
			heightCentering - 40, itemWidth, itemHeight, "Puzzle: ");

	for (string current : difficulties) {
		this->puzzleChoice->add(current.c_str());
	}

	this->saveChoice = new Fl_Choice(widthCentering - itemWidth / 2,
			heightCentering - 120, itemWidth, itemHeight, "Saves: ");

	this->continueGameButton = new Fl_Button(widthCentering - (itemWidth + 50) / 2,
			heightCentering - 80, itemWidth + 50, itemHeight, "Continue Game");
	this->continueGameButton->callback(cb_showContinue, this);

	this->playNewWindowButton = new Fl_Button(widthCentering - itemWidth / 2,
			heightCentering + 5, itemWidth, itemHeight, "Play");
	this->playNewWindowButton->callback(cb_show, this);

	this->scoreboardButton = new Fl_Button(widthCentering - (itemWidth + 20) / 2,
				heightCentering + 50, itemWidth + 20, itemHeight, "Scoreboard");
	this->scoreboardButton->callback(cb_scoreboard, this);

	this->quitButton = new Fl_Button(widthCentering - itemWidth / 2,
			heightCentering + 100, itemWidth, itemHeight, "Quit");
	this->quitButton->callback(cb_quit, this);

	this->checkSaves();

	this->end();
	this->resizable(this);
	this->show();
}

MainWindow::~MainWindow() {
}

void MainWindow::cb_show(Fl_Widget *o, void *data) {

	int difficulty = ((MainWindow*) data)->puzzleChoice->value();

	if (difficulty < 0) {
		fl_message("%s", "Please select a puzzle to play.");
		return;
	}

	string title = "Puzzle " + toString(difficulty + 1, "Difficuly must be a number.");

	GameWindow *window = new GameWindow(400, 400, title.c_str(), difficulty);
	window->set_modal();
	window->show();
	while (window->shown()) {
		Fl::wait();

		if (window->isComplete() && !window->getGameScore()->getPlayerName().empty()) {
			((MainWindow*) data)->highScores.addRecord(window->getGameScore());
		}

		if (window->nextGame() && !window->shown()) {
			difficulty++;
			string title = "Puzzle " + toString(difficulty + 1, "Difficuly must be a number.");
			window = new GameWindow(400, 400, title.c_str(), difficulty);
			window->set_modal();
			window->show();
		}
	}

	((MainWindow*) data)->checkSaves();
	((MainWindow*) data)->saveChoice->value(-1);
}

void MainWindow::cb_scoreboard(Fl_Widget*, void *data) {
	Fl_Window scoreboard(300, 250, "High Scoreboard");
	Fl_Box heading(125, 10, 50, 10, "Top 10:");

	vector<PlayerRecord> scores = ((MainWindow*) data)->highScores.getRecordsByPlayerName(true); // FIXME: allow selection of sort method and direction.

	vector<string> entries;
	int y = 35;
	for (vector<PlayerRecord>::size_type i = 0; i < scores.size(); i++) {

		PlayerRecord record = scores[i];

		entries.push_back(record.getEntry());
		Fl_Box *player_score = new Fl_Box(125, y, 50, 10, entries[i].c_str());
		scoreboard.add(player_score);

		y += 20;
	}

	scoreboard.set_modal();
	scoreboard.show();

	while (scoreboard.shown()) {
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
