/*
 * Utils.h
 *
 *  Created on: Apr 11, 2023
 *      Author: steven
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <string>
using namespace std;

int toInt(const string &text, const char *errorMessage);
string toString(int value, const char *errorMessage);

#endif /* UTILS_UTILS_H_ */
