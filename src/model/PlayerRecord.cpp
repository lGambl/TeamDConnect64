/*
 * PlayerRecord.cpp
 *
 *  Created on: Apr 29, 2023
 *      Author: larry
 */

#include <PlayerRecord.h>

namespace model {

PlayerRecord::PlayerRecord(string level, string playerName, int time) {
	this->level = level;
	this->playerName = playerName;
	this->time = time;
}

PlayerRecord::~PlayerRecord() {
	this->level = "";
	this->playerName = "";
	this->time = 0;

}

} /* namespace model */
