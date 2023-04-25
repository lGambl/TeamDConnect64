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

	for (vector<Node*>::size_type i = 0; i < nodes.size(); i++) {
		toSave += to_string(nodes[i]->getNumber()) + "," + to_string(nodes[i]->getPreset()) + ",";
	}
	file << toSave;

}

vector<string> SaveHandler::getSaves() {
	vector<string> puzzleFiles;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (".")) != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
		  string file = ent->d_name;
		  if (file.find("Puzzle") != string::npos) {
			  puzzleFiles.push_back(file);
		  }
	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
	  perror ("");
	}

	return puzzleFiles;
}

} /* namespace datatier */
