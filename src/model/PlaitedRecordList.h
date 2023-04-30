/*
 * PlaitedRecordList.h
 *
 *  Created on: Apr 29, 2023
 *      Author: larry
 */

#ifndef MODEL_PLAITEDRECORDLIST_H_
#define MODEL_PLAITEDRECORDLIST_H_

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include <RecordNode.h>
#include <PlayerRecord.h>
using namespace model;

namespace model {

class PlaitedRecordList {
private:
	RecordNode *timeHeader;
	RecordNode *levelHeader;
	RecordNode *nameHeader;
	int size;

	void insertByTime(RecordNode *node);
	void insertByLevel(RecordNode *node);
	void insertByName(RecordNode *node);

	void getRecordsByNameASC(vector<PlayerRecord> &nodes, RecordNode *current);
	void getRecordsByNameDSC(vector<PlayerRecord> &nodes, RecordNode *current);
	void getRecordsByTimeASC(vector<PlayerRecord> &nodes, RecordNode *current);
	void getRecordsByTimeDSC(vector<PlayerRecord> &nodes, RecordNode *current);
	void getRecordsByLevelASC(vector<PlayerRecord> &nodes, RecordNode *current);
	void getRecordsByLevelDSC(vector<PlayerRecord> &nodes, RecordNode *current);
	void removeNodeFromTimeList(RecordNode *nodeToRemove);
	void removeNodeFromPlayerNameList(RecordNode *nodeToRemove);
	void removeNodeFromLevelList(RecordNode *nodeToRemove);

	RecordNode* getNodeWithHighestTime();

	void removeRecord(RecordNode *nodeToRemove);
public:
	PlaitedRecordList();
	virtual ~PlaitedRecordList();

	void addRecord(PlayerRecord *node);

	vector<PlayerRecord> getRecordsByPlayerName(bool direction);
	vector<PlayerRecord> getRecordsByLevel(bool direction);
	vector<PlayerRecord> getRecordsByTime(bool direction);
};

} /* namespace model */

#endif /* MODEL_PLAITEDRECORDLIST_H_ */
