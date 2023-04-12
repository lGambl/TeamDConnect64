/*
 * NewWindow.h
 *
 *  Created on: Mar 15, 2023
 *      Author: dyoder
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

class GameWindow : public Fl_Window
{
private:
    Fl_Button* closeButton;

    int numberRows;
    int numberColumns;

    vector<void*> gameBoard;

public:
    GameWindow(int width, int height, const char* title );
    ~GameWindow();

private:
    static void cb_close(Fl_Widget*, void*);
};

} /* namespace view */

#endif /* VIEW_GAMEWINDOW_H_ */
