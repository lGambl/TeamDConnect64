/*
 * MainWindow.h
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#ifndef VIEW_MAINWINDOW_H_
#define VIEW_MAINWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Box.H>

#include <string>
#include <vector>

#include <GameWindow.h>
#include <PlaitedRecordList.h>
using namespace std;

namespace view {

/**
 * Defines a main window for display.
 */
class MainWindow: public Fl_Window {
private:
	vector<string> saves;
	Fl_Choice *puzzleChoice;
	Fl_Choice *saveChoice;
	Fl_Button *continueGameButton;
	Fl_Button *quitButton;
	Fl_Button *playNewWindowButton;
	Fl_Button *scoreboardButton;

	PlaitedRecordList highScores;

public:
	/**
	 * Initializes a main window for display.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param title The title of the window.
	 */
	MainWindow(int width, int height, const char *title);

	/**
	 * Deconstructor for the main window display.
	 */
	~MainWindow();

private:
	static void cb_scoreboard(Fl_Widget*, void*);
	static void cb_show(Fl_Widget*, void*);
	static void cb_showContinue(Fl_Widget*, void*);

	static void cb_quit(Fl_Widget*, void*);
	inline void cb_quit_i();

	void checkSaves();

	void updateInputDisplay(const char *text);
};

} /* namespace view */

#endif /* VIEW_MAINWINDOW_H_ */
