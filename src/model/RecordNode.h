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
	 * Instantiates a Record Node.
	 *
	 * @precondition record != nullptr
	 * @postcondition this->record == record && this->nextName == nullptr &&
	 * 					this->nextLevel == nullptr &&
	 * 					this->nextTime == nullptr
	 *
	 * @param The record of the score.
	 */
	RecordNode(PlayerRecord *record);

	/**
	 * Deconstructor for record node.
	 */
	virtual ~RecordNode();

	/**
	 * Getter for the record.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The current score record.
	 */
	PlayerRecord* getRecord() {
		return this->record;
	}

	/**
	 * Get record with the next name.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The next score by name.
	 */
	RecordNode* getNextName() {
		return this->nextName;
	}

	/**
	 * Get record with the next time.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The next score by time.
	 */
	RecordNode* getNextTime() {
		return this->nextTime;
	}

	/**
	 * Get record with the next level.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The next score by level.
	 */
	RecordNode* getNextLevel() {
		return this->nextLevel;
	}

	/**
	 * Set the next time record.
	 *
	 * @precondition node != nullptr
	 * @postcondition this-nextTime == node
	 *
	 * @param node The next time node.
	 */
	void setNextTime(RecordNode *node) {
		this->nextTime = node;
	}

	/**
	 * Set the next level record.
	 *
	 * @precondition node != nullptr
	 * @postcondition this-nextLevel == node
	 *
	 * @param node The next level node.
	 */
	void setNextLevel(RecordNode *node) {
		this->nextLevel = node;
	}

	/**
	 * Set the next name record.
	 *
	 * @precondition node != nullptr
	 * @postcondition this-nextName == node
	 *
	 * @param node The next name node.
	 */
	void setNextName(RecordNode *node) {
		this->nextName = node;
	}

};

} /* namespace model */

#endif /* MODEL_RECORDNODE_H_ */
