/*
 * FileHandler.cpp
 *
 *  Created on: Apr 14, 2023
 *      Author: larry
 */

#include "FileHandler.h"

namespace datatier {

FileHandler::FileHandler() {

}

FileHandler::~FileHandler() {

}

vector<Node*> FileHandler::readNodeFile(const string fileName) {
	ifstream infile(fileName);
	if (!infile) {
		throw invalid_argument("\nFile " + fileName + " does not exist\n");
	}
	vector<Node*> nodes;
	string line;
	vector<int> usedNumbers;

	int number;
	int xpos;
	int ypos;

	while (getline(infile, line)) {

		stringstream ss;
		vector<int> values = this->splitByComma(line);
		try {
			number = values[0];
			xpos = values[1];
			ypos = values[2];
			if (number != -1) {
				usedNumbers.push_back(number);
			}
			Node *node = new Node(number, xpos, ypos);
			nodes.push_back(node);
		} catch (const char *message) {
			infile.close();
			return nodes;
		}

	}
	if (nodes.size() == 64) {
		infile.close();
		return nodes;
	} else {
		throw std::invalid_argument(
				"File must contain 64 nodes. <number>,<x position>,<y position>");
	}
}

vector<int> FileHandler::splitByComma(const std::string& s) {
    std::vector<int> values;
    std::istringstream ss(s);
    std::string token;
    while (std::getline(ss, token, ',')) {
        values.push_back(std::stoi(token));
    }
    return values;
}

} /* namespace datatier */
