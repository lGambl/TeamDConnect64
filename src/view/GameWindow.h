/*
 * GameWindow.h
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#ifndef VIEW_GAMEWINDOW_H_
#define VIEW_GAMEWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

#include "EmptyNode.h"
#include "ExistingNode.h"

#include <iostream>
#include <vector>
using namespace std;

namespace view {

class GameWindow: public Fl_Window {
private:
	Fl_Button *closeButton;

	int numberRows;
	int numberColumns;

	vector<void*> gameBoard;

public:
	/**
	 * Initializes a game window for display.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param title The title of the window.
	 */
	GameWindow(int width, int height, const char *title);

	/**
	 * Deconstructor for the game window display.
	 */
	~GameWindow();

private:
	static void cb_close(Fl_Widget*, void*);
};

} /* namespace view */

#endif /* VIEW_GAMEWINDOW_H_ */
