/*
 * SaveHandler.h
 *
 *  Created on: Apr 21, 2023
 *      Author: larry
 */

#ifndef DATATIER_SAVEHANDLER_H_
#define DATATIER_SAVEHANDLER_H_

#include <Node.h>
using namespace model;

#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include <filesystem>
using namespace std;

#include <BoardReader.h>
using namespace datatier;

namespace datatier {

/**
 *  A save handler class responsible for handling saves
 */
class SaveHandler {

public:
	/**
	 * Initializes a save handler
	 */
	SaveHandler();

	/**
	 * Deconstructs a save handler
	 */
	virtual ~SaveHandler();

	/**
	 * Load a save given a file name
	 *
	 * @param fileName
	 *
	 * @return nodes of the board
	 */
	vector<Node*> loadSave(string &fileName);

	/**
	 * Save a game to a give file
	 *
	 * @param fileName
	 * @param nodes
	 */
	void saveGame(string &fileName, vector<Node*> nodes);

	/**
	 * Get saves that are in the main directory of the project
	 *
	 * @return a vector of all save names
	 */
	vector<string> getSaves();
};

} /* namespace datatier */

#endif /* DATATIER_SAVEHANDLER_H_ */
