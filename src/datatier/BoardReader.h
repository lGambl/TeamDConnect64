/*
 * BoardReader.h
 *
 *  Created on: Apr 14, 2023
 *      Author: larry
 */

#ifndef DATATIER_BOARDREADER_H_
#define DATATIER_BOARDREADER_H_

#include <BoardNode.h>
using namespace model;

#include "Utils.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

namespace datatier {

/**
 * A board reader class responsible for reading boards from files
 */
class BoardReader {
private:
	const char *BOARDSFILE = "./data/boards.txt";

public:
	/**
	 * Initializes a file handler.
	 */
	BoardReader();

	/**
	 * Deconstructs a file handler.
	 */
	virtual ~BoardReader();

	/**
	 * Reads a file for nodes.
	 *
	 * @precondition fileName.exists() && nodes in file == 64
	 * @postcondition none
	 *
	 * @param difficulty The difficulty (line) to load from the file.
	 *
	 * @throw Illegal argument if file is not found.
	 *
	 * @return A vector of node pointers.
	 */
	vector<BoardNode*> readNodeFile(int difficulty);

	/**
	 * Split given string into nodes if possible.
	 *
	 * @precondition none
	 * @postcondition none
	 *
	 * @param str The line of nodes.
	 *
	 * @return A vector of node pointers.
	 */
	vector<BoardNode*> splitByComma(const string &str);
};

} /* namespace datatier */

#endif /* DATATIER_BOARDREADER_H_ */
