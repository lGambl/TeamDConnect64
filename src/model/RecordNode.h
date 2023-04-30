/*
 * RecordNode.h
 *
 *  Created on: Apr 29, 2023
 *      Author: larry
 */

#ifndef MODEL_RECORDNODE_H_
#define MODEL_RECORDNODE_H_

#include <string>
#include <iostream>
using namespace std;

#include <PlayerRecord.h>
using namespace model;

namespace model {

class RecordNode {
private:
	PlayerRecord *record;
	RecordNode *nextName;
	RecordNode *nextLevel;
	RecordNode *nextTime;
public:
	/**
	 * Instantiates a Record Node
	 *
	 * @pre record != nullptr
	 * @post this->record == record && this->nextName == nullptr && this->nextLevel == nullptr && this->nextTime == nullptr
	 *
	 * @param record
	 */
	RecordNode(PlayerRecord *record);

	/**
	 * Deconstructor for record node
	 */
	virtual ~RecordNode();

	/**
	 * Get Record
	 *
	 * @return record
	 */
	PlayerRecord* getRecord() {
		return this->record;
	}

	/**
	 * Get record with the next name
	 *
	 * @return record
	 */
	RecordNode* getNextName() {
		return this->nextName;
	}

	/**
	 * Get record with the next time
	 *
	 * @return record
	 */
	RecordNode* getNextTime() {
		return this->nextTime;
	}

	/**
	 * Get record with the next level
	 *
	 * @return record
	 */
	RecordNode* getNextLevel() {
		return this->nextLevel;
	}

	void setNextTime(RecordNode* node);
	void setNextLevel(RecordNode* node);
	void setNextName(RecordNode* node);
};

} /* namespace model */

#endif /* MODEL_RECORDNODE_H_ */
