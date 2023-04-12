/*
 * SimpleWindow.cpp
 *
 *  Created on: Mar 15, 2023
 *      Author: dyoder
 */

#include "MainWindow.h"

namespace view {

MainWindow::MainWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    this->begin();
    this->inputDisplay = new Fl_Box(125, 50, 70, 30);

    this->quitButton = new Fl_Button(125, 150, 70, 30, "Quit");
    this->quitButton->callback(cb_quit, this);

    this->playNewWindowButton = new Fl_Button(125, 100, 70, 30, "Play");
    this->playNewWindowButton->callback(cb_show, this);

    this->end();
    this->resizable(this);
    this->show();
}


MainWindow::~MainWindow()
{
}

void MainWindow::cb_show(Fl_Widget* o, void* data)
{
	GameWindow* window = new GameWindow(400, 400, "Game"); // Minimum of 300x300
    window->set_modal();
    window->show();
    while (window->shown()) Fl::wait();
}

void MainWindow::cb_quit(Fl_Widget* , void* data)
{
    ((MainWindow*)data)->cb_quit_i();
}

void MainWindow::cb_quit_i()
{
    this->hide();
}

} /* namespace view */
