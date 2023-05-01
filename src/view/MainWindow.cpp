/*
 * MainWindow.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#include "MainWindow.h"

namespace view {

void MainWindow::buildDisplay(int width, int height) {
	int widthCentering = width / 2;
	int heightCentering = height / 2;
	int itemWidth = 70;
	int itemHeight = 30;
	this->puzzleChoice = new Fl_Choice(widthCentering - itemWidth / 2,
			heightCentering - 40, itemWidth, itemHeight, "Puzzle: ");
	for (int i = 1; i <= MAX_DIFFICULTY + 1; i++) {
		string value = to_string(i);
		this->puzzleChoice->add(value.c_str());
	}
	this->saveChoice = new Fl_Choice(widthCentering - itemWidth / 2,
			heightCentering - 120, itemWidth, itemHeight, "Saves: ");
	this->settingsButton = new Fl_Button(width - itemWidth - 10, 10, itemWidth,
			itemHeight, "Settings");
	this->settingsButton->callback(cb_settings, this);
	this->continueGameButton = new Fl_Button(
			widthCentering - (itemWidth + 50) / 2, heightCentering - 80,
			itemWidth + 50, itemHeight, "Continue Game");
	this->continueGameButton->callback(cb_continue, this);
	this->playNewWindowButton = new Fl_Button(widthCentering - itemWidth / 2,
			heightCentering + 5, itemWidth, itemHeight, "Play");
	this->playNewWindowButton->callback(cb_play, this);
	this->scoreboardButton = new Fl_Button(
			widthCentering - (itemWidth + 20) / 2, heightCentering + 50,
			itemWidth + 20, itemHeight, "Scoreboard");
	this->scoreboardButton->callback(cb_scoreboard, this);
	this->quitButton = new Fl_Button(widthCentering - itemWidth / 2,
			heightCentering + 100, itemWidth, itemHeight, "Quit");
	this->quitButton->callback(cb_quit, this);
	this->checkSaves();
}

MainWindow::MainWindow(int width, int height, const char *title) :
		Fl_Window(width, height, title) {

	this->begin();

	this->buildDisplay(width, height);

	this->end();
	this->resizable(this);
	this->show();

	this->colors = getColors();

	SaveHandler formatter;
	this->highScores = formatter.loadRecords();

	this->settings = formatter.loadUserSettings();
	if (this->settings.size() == 0) {
		this->settings.push_back("White");
		this->settings.push_back("Black");
	}
}

MainWindow::~MainWindow() {
}

void MainWindow::saveRecords() {
	SaveHandler formatter;
	formatter.saveRecords(this->highScores);
}

void MainWindow::cb_settings(Fl_Widget*, void *data) {
	Fl_Window window(250, 150, "Settings");

	Fl_Choice cellColor(125, 25, 75, 30, "Cell Color:");
	Fl_Choice textColor(125, 75, 75, 30, "Value Color:");

	map<string, Fl_Color> colors = ((MainWindow*) data)->colors;
	vector<string> colorStrings;
	for (map<string, Fl_Color>::iterator it = colors.begin();
			it != colors.end(); ++it) {
		cellColor.add(it->first.c_str());
		textColor.add(it->first.c_str());
		colorStrings.push_back(it->first);
	}

	if (!((MainWindow*) data)->settings[0].empty()) {
		int index = distance(colors.begin(),
				colors.find(((MainWindow*) data)->settings[0]));
		cellColor.value(index);
	}
	if (!((MainWindow*) data)->settings[1].empty()) {
		int index = distance(colors.begin(),
				colors.find(((MainWindow*) data)->settings[1]));
		textColor.value(index);
	}

	window.set_modal();
	window.show();

	while (window.shown()) {
		Fl::wait();
	}

	((MainWindow*) data)->settings[0] = colorStrings[cellColor.value()];
	((MainWindow*) data)->settings[1] = colorStrings[textColor.value()];

	SaveHandler saver;
	saver.saveUserSettings(((MainWindow*) data)->settings);
}

void MainWindow::playPuzzles(int difficulty) {
	string title = "Puzzle " + to_string(difficulty + 1);
	GameWindow *window = new GameWindow(400, 400, title.c_str(), difficulty);
	window->setColors(this->colors[this->settings[0]],
			this->colors[this->settings[1]]);

	window->set_modal();
	window->show();

	while (window->shown()) {
		Fl::wait();

		if (window->isComplete()
				&& !window->getGameScore()->getPlayerName().empty()) {

			this->highScores->addRecord(window->getGameScore());
			this->saveRecords();
		}

		if (window->nextGame() && !window->shown()) {
			difficulty++;
			title = "Puzzle " + to_string(difficulty + 1);
			window = new GameWindow(400, 400, title.c_str(), difficulty);
			window->setColors(this->colors[this->settings[0]],
					this->colors[this->settings[1]]);
			window->set_modal();
			window->show();
		}
	}
}

void MainWindow::cb_play(Fl_Widget *o, void *data) {

	int difficulty = ((MainWindow*) data)->puzzleChoice->value();

	if (difficulty < 0) {
		fl_message("%s", "Please select a puzzle to play.");
		return;
	}

	((MainWindow*) data)->playPuzzles(difficulty);
	((MainWindow*) data)->checkSaves();
	((MainWindow*) data)->saveChoice->value(-1);
}

void MainWindow::buildOutput(void *data, int sort) {
	Fl_Text_Buffer *scoresBuffer = new Fl_Text_Buffer();

	string output = getRecordsOutput(((MainWindow*) (data))->highScores, sort);

	scoresBuffer->text(output.c_str());

	this->scoresList->buffer(scoresBuffer);
	this->saveRecords();
}

void MainWindow::cb_scoreboard(Fl_Widget*, void *data) { // FIXME: Refactor or make its own class
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

void MainWindow::cb_continue(Fl_Widget*, void *data) {
	int choice = ((MainWindow*) data)->saveChoice->value();

	if (choice < 0) {
		fl_message("%s", "Please select a  save to continue.");
		return;
	}

	string puzzle = ((MainWindow*) data)->saves[choice];

	GameWindow *window = new GameWindow(400, 400, puzzle.c_str(), puzzle);
	window->setColors(
			((MainWindow*) data)->colors[((MainWindow*) data)->settings[0]],
			((MainWindow*) data)->colors[((MainWindow*) data)->settings[1]]);

	window->set_modal();
	window->show();
	while (window->shown())
		Fl::wait();
}

} /* namespace view */
