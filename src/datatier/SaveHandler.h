/*
 * SaveHandler.h
 *
 *  Created on: Apr 21, 2023
 *      Author: larry
 */

#ifndef DATATIER_SAVEHANDLER_H_
#define DATATIER_SAVEHANDLER_H_

#include <BoardNode.h>
#include <Board.h>
#include <PlaitedRecordList.h>
using namespace model;

#include <RecordOutputter.h>

#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include <regex>
using namespace std;

#include <BoardReader.h>
using namespace datatier;

namespace datatier {

/**
 *  A save handler class responsible for handling saves
 */
class SaveHandler {

private:
	Board* readSaveFile(string &fileName);

	const char *RECORDS_FILE = "./data/records.txt"; // FIXME: Move to utils const file
	const char *SETTINGS_FILE = "./data/settings.txt";
	const char *DELIMITER = ",";
	static const char LINE_DELIMETER = ',';
	const char *PUZZLE_FILE_NAME = "Puzzle";
	const char *SAVES_DIRECTORY = "./data/saves/";
	const char *RECORDS_DIRECTORY = "./data/records/";
	const char *RECORD_FILE_NAME = "./data/records/records";

public:
	/**
	 * Initializes a save handler.
	 */
	SaveHandler();

	/**
	 * Deconstructs a save handler.
	 */
	virtual ~SaveHandler();

	/**
	 * Load a save given a file name.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param fileName The file to load.
	 *
	 * @return The board in the file.
	 */
	Board* loadSave(string &fileName);

	/**
	 * Save a game to a give file.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param fileName The file to save to.
	 * @param nodes The nodes to save out.
	 * @param time The time spent on the board in seconds.
	 */
	void saveGame(string &fileName, vector<BoardNode*> nodes, int time);

	/**
	 * Get saves that are in the main directory of the project.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return A vector of all save names.
	 */
	vector<string> getSaves();

	/**
	 * Saves the records in a given list.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param level the level
	 * @param records The high scores to save out.
	 */
	void saveRecords(PlaitedRecordList *records, int level);

	/**
	 * Loads a plaited list of records.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param level the level
	 * @return PlaitedRecordList of high scores.
	 */
	PlaitedRecordList* loadRecords(int level);

	/**
	 * Loads a plaited list of all records.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return PlaitedRecordList of high scores.
	 */
	PlaitedRecordList* loadAllRecords();

	/**
	 * Loads a list of user settings.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return The list of settings.
	 */
	vector<string> loadUserSettings();

	/**
	 * Save a list of user settings.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param settings The list of settings to save.
	 */
	void saveUserSettings(vector<string> settings);
};

} /* namespace datatier */

#endif /* DATATIER_SAVEHANDLER_H_ */
