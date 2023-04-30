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

Board* SaveHandler::loadSave(string &fileName) {
	Board* board = this->readSaveFile(fileName);
	remove(fileName.c_str());
	return board;
}

void SaveHandler::saveGame(string &fileName, vector<BoardNode*> nodes, int time) {
	ofstream file(fileName);
	string toSave = "";

	toSave += to_string(time) + "\n";
	for (vector<BoardNode*>::size_type i = 0; i < nodes.size(); i++) {
		toSave += to_string(nodes[i]->getNumber()) + ","
				+ to_string(nodes[i]->getPreset()) + ",";
	}
	file << toSave;

}

vector<string> SaveHandler::getSaves() {
	vector<string> puzzleFiles;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(".")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			string file = ent->d_name;
			if (file.find("Puzzle") != string::npos) {
				puzzleFiles.push_back(file);
			}
		}
		closedir(dir);
	} else {
		/* could not open directory */
		perror("");
	}

	return puzzleFiles;
}

Board* SaveHandler::readSaveFile(string &fileName) {
	ifstream infile(fileName);
	if (!infile) {
		throw invalid_argument("\nFile " + fileName + " does not exist\n");
	}

	vector<BoardNode*> nodes;
	string line;
	Board *board = new Board();
	getline(infile, line);

	try {
		int time = stoi(line);
		getline(infile, line);
		BoardReader reader = BoardReader();
		board->setNodes(reader.splitByComma(line));
		board->setTimer(time);
	} catch (const char *message) {
		throw invalid_argument("Failed to read file");
	}

	return board;
}

} /* namespace datatier */
