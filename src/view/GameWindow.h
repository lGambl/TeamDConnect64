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
#include <FL/Fl_Output.H>
#include <FL/Enumerations.H>

#include "EmptyNode.h"
#include "ExistingNode.h"

#include <iostream>
#include <vector>
using namespace std;

#include <Node.h>
#include <Board.h>
using namespace model;

#include <FileHandler.h>
using namespace datatier;

namespace view {

class GameWindow: public Fl_Window {
private:
	Fl_Output *timer;
	Fl_Button *closeButton;
	Fl_Button *checkButton;

	int numberRows;
	int numberColumns;

	int inputBoxWidth;
	int inputBoxHeight;

	int otherObjectsWidth;
	int otherObjectsHeight;

	int widthCenteringFactor;
	int heightCenteringFactor;
	int widthCentering;
	int heightCentering;

	int middleX;
	int closeButtonY;
	int timerY;

	Board* board;
	vector<Node*> nodes;

	vector<Fl_Widget*> gameBoard;
	static const int MINIMUM_SIZE = 300;

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
	GameWindow(int width, int height, const char *title, int difficulty);

	/**
	 * Deconstructor for the game window display.
	 */
	~GameWindow();

private:
	static void cb_close(Fl_Widget*, void*);
	static void cb_check(Fl_Widget*, void*);
	static void cb_reset(Fl_Widget*, void*);

	void buildNodeSquares(int maxNumber, Fl_Fontsize inputBoxFontSize);

	Fl_Fontsize calculateSizes(int width, int height);
};

} /* namespace view */

#endif /* VIEW_GAMEWINDOW_H_ */
