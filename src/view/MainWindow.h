/*
 * SimpleWindow.h
 *
 *  Created on: Mar 15, 2023
 *      Author: dyoder
 */

#ifndef VIEW_MAINWINDOW_H_
#define VIEW_MAINWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <string>

//#include "GameWindow.h"
//using namespace std;

namespace view {

class MainWindow : public Fl_Window
{
private:
	Fl_Box* inputDisplay;
    Fl_Button* quitButton;
    Fl_Button* playNewWindowButton;

public:
    MainWindow(int width, int height, const char* title);
    ~MainWindow();

private:
    static void cb_show(Fl_Widget*, void*);

    static void cb_quit(Fl_Widget*, void*);
    inline void cb_quit_i();

    void updateInputDisplay(const char* text);
};

} /* namespace view */

#endif /* VIEW_MAINWINDOW_H_ */
