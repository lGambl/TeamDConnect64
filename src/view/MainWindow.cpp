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

	vector<string> difficulties = { "1", "2", "3", "4" };
	this->puzzleChoice = new Fl_Choice(widthCentering - itemWidth / 2,
			heightCentering - 50, itemWidth, itemHeight, "Puzzle: ");

	for (string current : difficulties) {
		this->puzzleChoice->add(current.c_str());
	}

	this->playNewWindowButton = new Fl_Button(widthCentering - itemWidth / 2,
			heightCentering, itemWidth, itemHeight, "Play");
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
	while (window->shown())
		Fl::wait();
}

void MainWindow::cb_quit(Fl_Widget*, void *data) {
	((MainWindow*) data)->cb_quit_i();
}

void MainWindow::cb_quit_i() {
	this->hide();
}

} /* namespace view */
