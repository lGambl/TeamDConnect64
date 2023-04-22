/*
 * BoardReader.h
 *
 *  Created on: Apr 14, 2023
 *      Author: larry
 */

#ifndef DATATIER_BOARDREADER_H_
#define DATATIER_BOARDREADER_H_

#include <Node.h>
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
	vector<Node*> splitByComma(const string& str);

public:
	/**
	 * Initializes a file handler
	 */
	BoardReader();

	/**
	 * Deconstructs a file handler
	 */
	virtual ~BoardReader();

	/**
	 * Reads a file for nodes
	 *
	 * @pre File must have 64 nodes && exist
	 * @post none
	 *
	 * @param fileName
	 *
	 * @throw Illegal argument if file is not found
	 *
	 * @return vector of node pointer
	 */
	vector<Node*> readNodeFile(const string fileName, int difficulty);
};

} /* namespace datatier */

#endif /* DATATIER_BOARDREADER_H_ */
