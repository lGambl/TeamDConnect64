/*
 * RecordNode.cpp
 *
 *  Created on: Apr 29, 2023
 *      Author: larry
 */

#include <RecordNode.h>

namespace model {

RecordNode::RecordNode(PlayerRecord *record) {
	if (record != nullptr) {
		this->record = record;
	} else {
		throw std::invalid_argument("Record cannot be null");
	}
	this->nextLevel = nullptr;
	this->nextName = nullptr;
	this->nextTime = nullptr;
}

RecordNode::~RecordNode() {
	delete this->record;

	if (this->nextLevel != nullptr) {
		delete this->nextLevel;
	}
	if (this->nextTime != nullptr) {
		delete this->nextTime;
	}
	if (this->nextName != nullptr) {
		delete this->nextName;
	}
}

void RecordNode::setNextTime(RecordNode *node) {
	this->nextTime = node;
}

void RecordNode::setNextName(RecordNode *node) {
	this->nextName = node;
}

void RecordNode::setNextLevel(RecordNode *node) {
	this->nextLevel = node;
}

} /* namespace model */
