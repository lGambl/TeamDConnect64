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
	this->checkSaves();
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

	for (string save : this->saves) {
		this->saveChoice->add(save.c_str());
	}

	this->continueGameButton = new Fl_Button(widthCentering - (itemWidth + 50) / 2,
			heightCentering - 80, itemWidth + 50, itemHeight, "Continue Game");
	this->continueGameButton->callback(cb_showContinue, this);

	this->playNewWindowButton = new Fl_Button(widthCentering - itemWidth / 2,
			heightCentering + 5, itemWidth, itemHeight, "Play");
	this->playNewWindowButton->callback(cb_show, this);

	this->quitButton = new Fl_Button(widthCentering - itemWidth / 2,
			heightCentering + 50, itemWidth, itemHeight, "Quit");
	this->quitButton->callback(cb_quit, this);

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

	GameWindow *window = new GameWindow(400, 400, "Game", difficulty);
	window->set_modal();
	window->show();
	while (window->shown()) {
		Fl::wait();
	}

	if (window->nextGame() && !window->shown()) {
		window = new GameWindow(400, 400, "Game", ++difficulty);
		window->set_modal();
		window->show();
	}

	((MainWindow*) data)->checkSaves();
	((MainWindow*) data)->saveChoice->value(-1);
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
	for (string save : this->saves) {
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

	GameWindow *window = new GameWindow(400, 400, "Game", puzzle);
	window->set_modal();
	window->show();
	while (window->shown())
		Fl::wait();
}

} /* namespace view */
