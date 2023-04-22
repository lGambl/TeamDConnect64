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

			return splitByComma(line);
		}
	}

	return nodes;
}

vector<Node*> BoardReader::splitByComma(const std::string& s) {
    vector<int> values;
    vector<bool> editables;
    istringstream ss(s);
    string token;

    int count = 0;
    while (std::getline(ss, token, ',')) {
    	if (count % 2) {
    		editables.push_back((bool)std::stoi(token));
    	}
    	else {
    		values.push_back(std::stoi(token));
    	}
    	count++;
    }

    vector<Node*> nodes;
    for (vector<int>::size_type i = 0; i < values.size(); i++) {
    	nodes.push_back(new Node(values[i], editables[i]));
    }

    return nodes;
}

} /* namespace datatier */
