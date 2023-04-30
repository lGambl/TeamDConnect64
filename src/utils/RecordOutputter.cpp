/*
 * RecordOutputter.cpp
 *
 *  Created on: Apr 30, 2023
 *      Author: larry
 */

#include <RecordOutputter.h>

namespace utils {

RecordOutputter::RecordOutputter() {
	// TODO Auto-generated constructor stub

}

RecordOutputter::~RecordOutputter() {
	// TODO Auto-generated destructor stub
}

string RecordOutputter::getRecordsOutput(PlaitedRecordList *records, int sort) {
	vector<PlayerRecord> list = this->getRecordsListBySort(sort, records);

	stringstream ss;
	for (PlayerRecord single : list) {

		ss << left << setw(30) << single.getPlayerName().c_str() << setw(20)
				<< single.getLevel().c_str() << setw(10) << single.getTime() << endl;
	}

	return ss.str();
}

vector<PlayerRecord> RecordOutputter::getRecordsListBySort(int sort, PlaitedRecordList* records){
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

void RecordOutputter::getRecordsCSVOutput(PlaitedRecordList *records,
		string &result) {
	vector<PlayerRecord> list;
	list = records->getRecordsByPlayerName(true);

	stringstream ss;
	for (PlayerRecord single : list) {
		ss << single.getPlayerName() << "," << single.getLevel() << ","
				<< single.getTime() << endl;
	}

	result = ss.str();
}

} /* namespace utils */
