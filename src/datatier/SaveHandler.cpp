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
	Board *board = this->readSaveFile(fileName);
	remove(fileName.c_str());
	return board;
}

void SaveHandler::saveGame(string &fileName, vector<BoardNode*> nodes,
		int time) {
	ofstream file(fileName);
	string toSave = "";

	toSave += to_string(time) + "\n";
	for (vector<BoardNode*>::size_type i = 0; i < nodes.size(); i++) {
		toSave += to_string(nodes[i]->getNumber()) + DELIMITER
				+ to_string(nodes[i]->getPreset()) + DELIMITER;
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
			if (file.find(PUZZLE_FILE_NAME) != string::npos) {
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

void SaveHandler::saveRecords(PlaitedRecordList *records) {
	ofstream file(RECORDS_FILE);
	string toSave = "";
	getRecordsCSVOutput(records, toSave);

	file << toSave;
}

PlaitedRecordList* SaveHandler::loadRecords() {
	ifstream file(RECORDS_FILE);
	string line;
	string playerName, puzzle, timestr;
	PlaitedRecordList *records = new PlaitedRecordList();

	while (getline(file, line)) {
		stringstream ss(line);

		if (getline(ss, playerName, LINE_DELIMETER)
				&& getline(ss, puzzle, LINE_DELIMETER)
				&& getline(ss, timestr)) {
			try {
				int time = stoi(timestr);
				PlayerRecord *record = new PlayerRecord(puzzle, playerName,
						time);
				records->addRecord(record);
			} catch (const char *message) {
				continue;
			}
		}
	}

	return records;
}

} /* namespace datatier */
