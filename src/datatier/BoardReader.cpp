/*
 * FileHandler.cpp
 *
 *  Created on: Apr 14, 2023
 *      Author: larry
 */

#include <BoardReader.h>

namespace datatier {

BoardReader::BoardReader() {

}

BoardReader::~BoardReader() {

}

vector<BoardNode*> BoardReader::readNodeFile(int difficulty) {
	ifstream infile(BOARDSFILE);
	if (!infile) {
		throw invalid_argument("\nFile does not exist\n");
	}

	vector<BoardNode*> nodes;
	string line;

	int lineNumber = 0;
	while (getline(infile, line)) {

		if (lineNumber++ == difficulty) {

			return splitByComma(line);
		}
	}

	return nodes;
}

vector<BoardNode*> BoardReader::splitByComma(const std::string &s) {
	vector<int> values;
	vector<bool> editables;
	istringstream ss(s);
	string token;

	int count = 0;
	while (std::getline(ss, token, ',')) {
		if (count % 2) {
			editables.push_back((bool) std::stoi(token));
		} else {
			values.push_back(std::stoi(token));
		}
		count++;
	}

	vector<BoardNode*> nodes;
	for (vector<int>::size_type i = 0; i < values.size(); i++) {
		nodes.push_back(new BoardNode(values[i], editables[i]));
	}

	return nodes;
}

} /* namespace datatier */
