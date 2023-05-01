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

	const char *RECORDS_FILE = "records.txt"; // FIXME: Move to utils const file
	const char *DELIMITER = ",";
	static const char LINE_DELIMETER = ',';
	const char *PUZZLE_FILE_NAME = "Puzzle";

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
	 * @param records The high scores to save out.
	 */
	void saveRecords(PlaitedRecordList *records);

	/**
	 * Loads a plaited list of records.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @return PlaitedRecordList of high scores.
	 */
	PlaitedRecordList* loadRecords();
};

} /* namespace datatier */

#endif /* DATATIER_SAVEHANDLER_H_ */
