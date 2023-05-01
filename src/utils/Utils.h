/*
 * Utils.h
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <FL/Fl.H>

#include <unistd.h>
#include <map>
#include <string>
#include <iostream>
using namespace std;

/**
 * Converts a given text to integer.
 *
 * @precondition none
 * @postcondition none
 *
 * @param text The text to convert.
 * @param errorMessage The error message if it fails
 *
 * @throw errorMessage if text cannot be converted to a number.
 *
 * @return The int form of the given text.
 */
int toInt(const string &text, const char *errorMessage);

/**
 * Getts a map of strings to colors.
 *
 * @precondition none
 * @postcondition none
 *
 * @return A map of strings and colors.
 */
map<string, Fl_Color> getColors();

string getCWD();

#endif /* UTILS_UTILS_H_ */
