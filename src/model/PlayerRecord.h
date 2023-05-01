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
	 * Instantiate a instance of a player record.
	 *
	 * @precondition none
	 * @postcondition this->level == level &&
	 * 					this->playerName == playerName &&
	 * 					this->time == time
	 *
	 * @param level The name of the level.
	 * @param playerName The name of the player.
	 * @param time The time of the score (seconds).
	 */
	PlayerRecord(string level, string playerName, int time);
	virtual ~PlayerRecord();

	/**
	 * Getter for the level of the score.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The level of the score.
	 */
	const string& getLevel() {
		return this->level;
	}

	/**
	 * Getter for the player name of the score.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The player name of the score.
	 */
	const string& getPlayerName() {
		return this->playerName;
	}

	/**
	 * Getter for the time of the score.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The time of the score (seconds).
	 */
	int getTime() {
		return this->time;
	}

};

} /* namespace model */

#endif /* MODEL_PLAYERRECORD_H_ */
