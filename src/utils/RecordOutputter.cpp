/*
 * RecordOutputter.cpp
 *
 *  Created on: Apr 30, 2023
 *      Author: larry
 */

#include <RecordOutputter.h>

void getRecordsCSVOutput(PlaitedRecordList *records, string &result) {

	vector<PlayerRecord> list;
	list = records->getRecordsByPlayerName(true);

	stringstream ss;
	for (PlayerRecord single : list) {
		ss << single.getPlayerName() << "," << single.getLevel() << ","
				<< single.getTime() << endl;
	}

	result = ss.str();
}

string getRecordsOutput(PlaitedRecordList *records, int sort) {

	vector<PlayerRecord> list = getRecordsListBySort(records, sort);

	stringstream ss;
	for (PlayerRecord single : list) {

		ss << left << setw(35) << single.getPlayerName().c_str() << setw(35)
				<< single.getLevel().c_str() << setw(30) << single.getTime()
				<< endl;
	}

	return ss.str();
}

vector<PlayerRecord> getRecordsListBySort(PlaitedRecordList *records,
		int sort) {

	switch (sort) {
	case 0:
		return records->getRecordsByTime(true);
		break;
	case 1:
		return records->getRecordsByTime(false);
		break;
	case 2:
		return records->getRecordsByPlayerName(true);
		break;
	case 3:
		return records->getRecordsByPlayerName(false);
		break;
	case 4:
		return records->getRecordsByLevel(true);
		break;
	case 5:
		return records->getRecordsByLevel(false);
		break;
	default:
		return records->getRecordsByTime(true);
		break;
	}
}
