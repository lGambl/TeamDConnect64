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

namespace utils {

class RecordOutputter {
private:
	vector<PlayerRecord> getRecordsListBySort(int sort,PlaitedRecordList* records);
public:
	RecordOutputter();
	virtual ~RecordOutputter();

	/**
	 * Get the Records output in string csv format
	 *
	 * @param records
	 * @param result passed in string to hold output
	 */
	void getRecordsCSVOutput(PlaitedRecordList *records,string &result);
	string getRecordsOutput(PlaitedRecordList* records,int sort);
};

} /* namespace utils */

#endif /* UTILS_RECORDOUTPUTTER_H_ */
