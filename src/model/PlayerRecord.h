/*
 * PlayerRecord.h
 *
 *  Created on: Apr 29, 2023
 *      Author: larry
 */

#ifndef MODEL_PLAYERRECORD_H_
#define MODEL_PLAYERRECORD_H_

#include <string>
using namespace std;

namespace model {

/**
 * Representation of a player record
 */
class PlayerRecord {
private:
	int time;
	string playerName;
	string level;
public:

	/**
	 * Instantiate a instance of a player record
	 *
	 * @pre none
	 * @post this->level == level && this->playerName == playerName && this->time == time
	 *
	 * @param level
	 * @param playerName
	 * @param time
	 */
	PlayerRecord(string level, string playerName, int time);
	virtual ~PlayerRecord();

	/**
	 * Get the level
	 *
	 * @return the level
	 */
	const string& getLevel(){
		return this->level;
	}

	/**
	 * Get the player name
	 *
	 * @return the player name
	 */
	const string& getPlayerName(){
		return this->playerName;
	}

	/**
	 * Get the time
	 *
	 * @return the time
	 */
	int getTime(){
		return this->time;
	}

};

} /* namespace model */

#endif /* MODEL_PLAYERRECORD_H_ */
