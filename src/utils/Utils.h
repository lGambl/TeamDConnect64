/*
 * Utils.h
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <string>
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
 * @return The int form of the given text.
 */
int toInt(const string &text, const char *errorMessage);

/**
 * Converts a given integer to text.
 *
 * @precondition none
 * @postcondition none
 *
 * @param value The integer to convert.
 * @param errorMessage The error message if it fails
 *
 * @return The text form of the given integer.
 */
string toString(int value, const char *errorMessage);

#endif /* UTILS_UTILS_H_ */
