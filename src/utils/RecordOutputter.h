/*
 * RecordOutputter.h
 *
 *  Created on: Apr 30, 2023
 *      Author: larry
 */

#ifndef UTILS_RECORDOUTPUTTER_H_
#define UTILS_RECORDOUTPUTTER_H_

#include <PlaitedRecordList.h>
#include <PlayerRecord.h>
using namespace model;

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

/**
 * Format the records list in string csv format.
 *
 * @precondition none
 * @postcondition none
 *
 * @param records The list of high scores to format.
 * @param result The passed in string to hold output.
 */
void getRecordsCSVOutput(PlaitedRecordList *records, string &result);

/**
 * Format the records list for display on screen.
 *
 * @precondition none
 * @postcondition none
 *
 * @param records The list of high scores to format.
 * @param sort The number 0-5 for what sort to do to the list.
 *
 * @return The string to display.
 */
string getRecordsOutput(PlaitedRecordList *records, int sort);

/**
 * Sorts the records list for display on screen.
 *
 * @precondition none
 * @postcondition none
 *
 * @param records The list of high scores to format.
 * @param sort The number 0-5 for what sort to do to the list.
 *
 * @return The list of scores to display.
 */
vector<PlayerRecord> getRecordsListBySort(PlaitedRecordList *records, int sort);

#endif /* UTILS_RECORDOUTPUTTER_H_ */
