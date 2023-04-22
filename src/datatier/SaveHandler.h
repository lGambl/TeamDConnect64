/*
 * SaveHandler.h
 *
 *  Created on: Apr 21, 2023
 *      Author: larry
 */

#ifndef DATATIER_SAVEHANDLER_H_
#define DATATIER_SAVEHANDLER_H_

#include <Node.h>
using namespace model;

#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include <filesystem>
using namespace std;

#include <BoardReader.h>
using namespace datatier;

namespace datatier {

class SaveHandler {

public:
	SaveHandler();
	virtual ~SaveHandler();
	vector<Node*> loadSave(string &fileName);
	void saveGame(string &fileName, vector<Node*> nodes);
	vector<string> getSaves();
};

} /* namespace datatier */

#endif /* DATATIER_SAVEHANDLER_H_ */
