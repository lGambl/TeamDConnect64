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

void SaveHandler::saveRecords(PlaitedRecordList *records, int level) {
	ofstream file("records"+ to_string(level) +".txt");
	string toSave = "";
	getRecordsCSVOutput(records, toSave);

	file << toSave;
}

PlaitedRecordList* SaveHandler::loadRecords(int level) {
	ifstream file("records"+ to_string(level) +".txt");
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

PlaitedRecordList* SaveHandler::loadAllRecords(){
	PlaitedRecordList *records = new PlaitedRecordList();

	vector<string> recordFiles;

		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir(".")) != NULL) {
			/* print all the files and directories within directory */
			while ((ent = readdir(dir)) != NULL) {
				string file = ent->d_name;
				if (file.find("records") != string::npos) {
					recordFiles.push_back(file);
				}
			}
			closedir(dir);
		} else {
			/* could not open directory */
			perror("");
		}

		for(string recordsFile : recordFiles){
			int level = stoi(recordsFile);
			PlaitedRecordList* list = this->loadRecords(level);
			for(RecordNode* node : list->getRecordsByTime(false)){
				records->addRecord(node->getRecord());
			}
		}

		return records;

}

vector<string> SaveHandler::loadUserSettings() {
	ifstream file(SETTINGS_FILE);
	string line;
	vector<string> settings;

	while (getline(file, line)) {
		istringstream ss(line);
		string token;

		while (getline(ss, token, ',')) {
			settings.push_back(token);
		}
	}

	return settings;
}

void SaveHandler::saveUserSettings(vector<string> settings) {
	ofstream file(SETTINGS_FILE);
	stringstream ss;
	for (string setting : settings) {
		ss << setting << ",";
	}

	file << ss.str();
}

} /* namespace datatier */
