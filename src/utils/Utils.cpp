/*
 * Utils.cpp
 *
 *  Created on: April 11, 2023
 *      Author: Steven Kight
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
