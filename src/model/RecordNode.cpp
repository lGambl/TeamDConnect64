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
	if (this->nextTime != nullptr) {
		delete this->nextTime;
	}

	this->record = nullptr;
	this->nextLevel = nullptr;
	this->nextName = nullptr;
}

} /* namespace model */
