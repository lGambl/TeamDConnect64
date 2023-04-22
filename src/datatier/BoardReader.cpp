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

vector<Node*> BoardReader::readNodeFile(const string fileName, int difficulty) {
	ifstream infile(fileName);
	if (!infile) {
		throw invalid_argument("\nFile " + fileName + " does not exist\n");
	}

	vector<Node*> nodes;
	string line;

	int lineNumber = 0;
	while (getline(infile, line)) {

		if (lineNumber++ == difficulty) {

			stringstream ss;
			vector<int> values = splitByComma(line);

			for (int value : values) {
				nodes.push_back(new Node(value));
			}

			return nodes;
		}
	}

	return nodes;
}

vector<int> BoardReader::splitByComma(const std::string& s) {
    std::vector<int> values;
    std::istringstream ss(s);
    std::string token;
    while (std::getline(ss, token, ',')) {
        values.push_back(std::stoi(token));
    }
    return values;
}

} /* namespace datatier */
