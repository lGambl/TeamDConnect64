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
	static const int MAX_SIZE = 10;

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
	/**
	 * Initializes a high score list.
	 *
	 * @precondition none
	 * @postcondition this->timeHeader == nullptr &&
	 * 					this->nameHeader == nullptr &&
	 * 					this->levelHeader == nullptr &&
	 * 					this->size == 0
	 */
	PlaitedRecordList();

	/**
	 * Deconstructor for the list.
	 */
	virtual ~PlaitedRecordList();

	/**
	 * Adds a scores to the list.
	 *
	 * @precondition none
	 * @postcondition this->size @pre + 1 == this->size
	 *
	 * @param node The score to add.
	 */
	void addRecord(PlayerRecord *node);

	/**
	 * Gets the scores by name depending on direction.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param direction True for ascending, False for descending.
	 * @return The list of scores in order.
	 */
	vector<PlayerRecord> getRecordsByPlayerName(bool direction);

	/**
	 * Gets the scores by length depending on direction
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param direction True for ascending, False for descending
	 * @return The list of scores in order
	 */
	vector<PlayerRecord> getRecordsByLevel(bool direction);

	/**
	 * Gets the scores by time depending on direction.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param direction True for ascending, False for descending.
	 *
	 * @return The list of scores in order.
	 */
	vector<PlayerRecord> getRecordsByTime(bool direction);
};

} /* namespace model */

#endif /* MODEL_PLAITEDRECORDLIST_H_ */
