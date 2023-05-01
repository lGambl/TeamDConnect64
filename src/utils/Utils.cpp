/*
 * Utils.cpp
 *
 *  Created onApril 11, 2023
 *      AuthorSteven Kight
 */

#include "Utils.h"

#include <algorithm>
#include <sstream>

int toInt(const string &text, const char *errorMessage) {
	istringstream streamConversion(text);
	int value = 0;
	if (!(streamConversion >> value)) {
		throw errorMessage;
	}

	return value;
}

map<string, Fl_Color> getColors() {
	map<string, Fl_Color> colorMap;

	colorMap["Black"] = FL_BLACK;
    colorMap["White"] = FL_WHITE;
    colorMap["Red"] = FL_RED;
    colorMap["Green"] = FL_GREEN;
    colorMap["Yellow"] = FL_YELLOW;
    colorMap["Blue"] = FL_BLUE;
    colorMap["Magenta"] = FL_MAGENTA;
    colorMap["Cyan"] = FL_CYAN;
    colorMap["Dark Red"] = FL_DARK_RED;
    colorMap["Dark Green"] = FL_DARK_GREEN;
    colorMap["Dark Yellow"] = FL_DARK_YELLOW;
    colorMap["Dark Blue"] = FL_DARK_BLUE;
    colorMap["Dark Magenta"] = FL_DARK_MAGENTA;
    colorMap["Dark Cyan"] = FL_DARK_CYAN;

	return colorMap;
}
