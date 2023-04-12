/*
 * Utils.cpp
 *
 *  Created on: Apr 11, 2023
 *      Author: steven
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

string toString(int value, const char *errorMessage) {
	try {
		return to_string(value);
	}
    catch (const char* message)
    {
    	throw message;
    }
}
