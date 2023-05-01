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
	string filePath = getCWD() + SAVES_DIRECTORY + fileName;
	Board *board = this->readSaveFile(filePath);
	remove(filePath.c_str());
	return board;
}

void SaveHandler::saveGame(string &fileName, vector<BoardNode*> nodes,
		int time) {
	ofstream file(getCWD() + SAVES_DIRECTORY + fileName);
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
	if ((dir = opendir((getCWD() + SAVES_DIRECTORY).c_str())) != NULL) {
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
	string filePath = getCWD() + RECORD_FILE_NAME + to_string(level) + ".txt";
	ofstream file(filePath.c_str());
	string toSave = "";
	getRecordsCSVOutput(records, toSave);

	file << toSave;
}

PlaitedRecordList* SaveHandler::loadRecords(int level) {
	string filePath = getCWD() + RECORD_FILE_NAME + to_string(level) + ".txt";
	ifstream file(filePath.c_str());
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

PlaitedRecordList* SaveHandler::loadAllRecords() {
	PlaitedRecordList *records = new PlaitedRecordList();

	vector<string> recordFiles;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir((getCWD() + RECORDS_DIRECTORY).c_str())) != NULL) {
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

	regex pattern(R"(\d+)");
	smatch match;
	for (string recordsFile : recordFiles) {

		if (regex_search(recordsFile, match, pattern)) {
			int level = stoi(match[0]);

			PlaitedRecordList *list = this->loadRecords(level);
			for (PlayerRecord node : list->getRecordsByTime(false)) {
				PlayerRecord *newNode = new PlayerRecord(node.getLevel(),
						node.getPlayerName(), node.getTime());

				records->addRecord(newNode);
			}
		}
	}

	return records;

}

vector<string> SaveHandler::loadUserSettings() {
	string filePath = getCWD() + SETTINGS_FILE;
	ifstream file(filePath.c_str());
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
	string filePath = getCWD() + SETTINGS_FILE;
	ofstream file(filePath.c_str());
	stringstream ss;
	for (string setting : settings) {
		ss << setting << ",";
	}

	file << ss.str();
}

} /* namespace datatier */
