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
#include <FL/Fl_Box.H>
#include <FL/Enumerations.H>

#include "EmptyBoardNode.h"
#include "ExistingBoardNode.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

#include <BoardNode.h>
#include <Board.h>
#include <PlayerRecord.h>
using namespace model;

#include <BoardReader.h>
#include <SaveHandler.h>
using namespace datatier;

namespace view {

class GameWindow: public Fl_Window {
private:
	static const int MINIMUM_SIZE = 300;
	static const int MAX_DIFFICULTY = 4;

	Fl_Output *timerOutput;
	Fl_Button *closeButton;
	Fl_Button *checkButton;
	Fl_Button *resetButton;
	Fl_Button *pauseButton;

	string puzzleTitle;

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
	int bottomButtonY;
	int timerY;

	int difficulty;

	bool result;
	bool pause;
	bool complete;

	Board *board;
	vector<BoardNode*> nodes;

	PlayerRecord *playerRecord;

	vector<Fl_Widget*> gameBoard;

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

	GameWindow(int width, int height, const char *title, string &save);

	/**
	 * Deconstructor for the game window display.
	 */
	~GameWindow();

	bool nextGame();

	bool isComplete();

	PlayerRecord* getGameScore();

private:
	static void cb_timer(void*);
	static void cb_pause(Fl_Widget*, void*);
	static void cb_close(Fl_Widget*, void*);
	static void cb_check(Fl_Widget*, void*);
	static void cb_reset(Fl_Widget*, void*);

	void buildNodeSquares(int maxNumber, Fl_Fontsize inputBoxFontSize);

	void saveGame();

	Fl_Fontsize calculateSizes(int width, int height);
	void buildDisplay(int width, int height);

	void enableNextGame();
	void timer_update();

	void displayCompleteDialog();
	void displayPauseDialog();
	string displayUsernameDialog();
};

} /* namespace view */

#endif /* VIEW_GAMEWINDOW_H_ */
