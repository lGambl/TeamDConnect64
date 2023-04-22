/*
 * SaveHandler.cpp
 *
 *  Created on: Apr 21, 2023
 *      Author: larry
 */

#include <SaveHandler.h>

namespace datatier {

SaveHandler::SaveHandler() {

}

SaveHandler::~SaveHandler() {

}

vector<Node*> SaveHandler::loadSave(string &fileName) {
	BoardReader reader = BoardReader();
	vector<Node*> nodes = reader.readNodeFile(fileName, 0);
	remove(fileName.c_str());
	return nodes;
}

void SaveHandler::saveGame(string &fileName, vector<Node*> nodes) {
	ofstream file(fileName);
	string toSave = "";

	int counter = 0;
	for (Node *node : nodes) {
		if (counter < 63) {
			toSave += to_string(node->getNumber()) + ",";
		} else {
			toSave += to_string(node->getNumber()) + ",";
		}
	}
	file << toSave;

}

vector<string> SaveHandler::getSaves() {
	vector<string> puzzleFiles;
	    for (const auto& entry : filesystem::directory_iterator(".")) {
	        string filename = entry.path().filename().string();
	        if (filename.find("Puzzle") != string::npos) {
	            puzzleFiles.push_back(filename);
	        }
	    }
	    return puzzleFiles;
}

} /* namespace datatier */
