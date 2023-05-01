/*
 * PlaitedRecordList.cpp
 *
 *  Created on: Apr 29, 2023
 *      Author: larry
 */

#include <PlaitedRecordList.h>

namespace model {

PlaitedRecordList::PlaitedRecordList() {
	this->timeHeader = nullptr;
	this->nameHeader = nullptr;
	this->levelHeader = nullptr;
	this->size = 0;
}

PlaitedRecordList::~PlaitedRecordList() {
	if (this->timeHeader != nullptr) {
		delete this->timeHeader;
	}
	this->nameHeader = nullptr;
	this->levelHeader = nullptr;
	this->size = 0;
}

/**
 * Adds a movie to the list
 *
 * @pre none
 * @post this->size @pre + 1 = this->size
 *
 * @param movie to add
 */
void PlaitedRecordList::addRecord(PlayerRecord *movie) {
	RecordNode *newRecord = new RecordNode(movie);

	this->insertByTime(newRecord);
	this->insertByName(newRecord);
	this->insertByLevel(newRecord);
	this->size++;

	if (this->size > 10){
		RecordNode* badNode = this->getNodeWithHighestTime();
		this->removeRecord(badNode);
	}
}

void PlaitedRecordList::insertByName(RecordNode *record) {
	if (this->nameHeader == nullptr) {
		this->nameHeader = record;
		return;
	}

	if (record->getRecord()->getPlayerName()
			< this->nameHeader->getRecord()->getPlayerName()) {
		record->setNextName(this->nameHeader);
		this->nameHeader = record;
		return;
	}

	RecordNode *current = this->nameHeader;
	while (current->getNextName() != nullptr
			&& record->getRecord()->getPlayerName()
					> current->getNextName()->getRecord()->getPlayerName()) {
		current = current->getNextName();
	}
	record->setNextName(current->getNextName());
	current->setNextName(record);
}

void PlaitedRecordList::insertByTime(RecordNode *record) {
	if (this->timeHeader == nullptr) {
		this->timeHeader = record;
		return;
	}

	if (record->getRecord()->getTime()
			< this->timeHeader->getRecord()->getTime()) {
		record->setNextTime(this->timeHeader);
		this->timeHeader = record;
		return;
	}

	RecordNode *current = this->timeHeader;
	while (current->getNextTime() != nullptr
			&& record->getRecord()->getTime()
					> current->getNextTime()->getRecord()->getTime()) {
		current = current->getNextTime();
	}
	record->setNextTime(current->getNextTime());
	current->setNextTime(record);
}

void PlaitedRecordList::insertByLevel(RecordNode *record) {
	if (this->levelHeader == nullptr) {
		this->levelHeader = record;
		return;
	}

	if (record->getRecord()->getLevel()
			> this->levelHeader->getRecord()->getLevel()) {
		record->setNextLevel(this->levelHeader);
		this->levelHeader = record;
		return;
	}

	RecordNode *current = this->levelHeader;
	while (current->getNextLevel() != nullptr
			&& record->getRecord()->getLevel()
					<= current->getNextLevel()->getRecord()->getLevel()) {
		current = current->getNextLevel();
	}
	record->setNextLevel(current->getNextLevel());
	current->setNextLevel(record);
}

/**
 * Removes a movie from the list
 *
 * @pre none
 * @post none || this->size @pre - 1 == this->size
 *
 * @param movieName to remove
 */
void PlaitedRecordList::removeRecord(RecordNode *node) {

	this->removeNodeFromTimeList(node);
	this->removeNodeFromLevelList(node);
	this->removeNodeFromPlayerNameList(node);

	delete node;
	this->size--;
}

void PlaitedRecordList::removeNodeFromTimeList(RecordNode *nodeToRemove) {
	if (this->timeHeader == nullptr) {
		return;
	}
	if (this->timeHeader == nodeToRemove) {
		this->timeHeader = this->timeHeader->getNextTime();
	} else {
		RecordNode *prev = this->timeHeader;
		RecordNode *current = this->timeHeader->getNextTime();
		while (current != nullptr && current != nodeToRemove) {
			prev = current;
			current = current->getNextTime();
		}
		if (current == nullptr) {
			return;
		}
		prev->setNextTime(current->getNextTime());
	}
	nodeToRemove->setNextTime(nullptr);
}

void PlaitedRecordList::removeNodeFromPlayerNameList(RecordNode *nodeToRemove) {
	if (this->nameHeader == nullptr) {
		return;
	}
	if (this->nameHeader == nodeToRemove) {
		this->nameHeader = this->nameHeader->getNextName();
	} else {
		RecordNode *prev = this->nameHeader;
		RecordNode *current = this->nameHeader->getNextName();
		while (current != nullptr && current != nodeToRemove) {
			prev = current;
			current = current->getNextName();
		}
		if (current == nullptr) {
			return;
		}
		prev->setNextName(current->getNextName());
	}
	nodeToRemove->setNextName(nullptr);
}

void PlaitedRecordList::removeNodeFromLevelList(RecordNode *nodeToRemove) {
	if (this->levelHeader == nullptr) {
		return;
	}
	if (this->levelHeader == nodeToRemove) {
		this->levelHeader = this->levelHeader->getNextLevel();
	} else {
		RecordNode *prev = this->levelHeader;
		RecordNode *current = this->levelHeader->getNextLevel();
		while (current != nullptr && current != nodeToRemove) {
			prev = current;
			current = current->getNextLevel();
		}
		if (current == nullptr) {
			return;
		}
		prev->setNextLevel(current->getNextLevel());
	}
	nodeToRemove->setNextLevel(nullptr);
}

/**
 * Gets the movies by name depending on direction
 *
 * @pre none
 * @post none
 *
 * @param direction true for ascending, false for descending
 * @return the list of movies in order
 */
vector<PlayerRecord> PlaitedRecordList::getRecordsByPlayerName(bool direction) {
	vector<PlayerRecord> movies;
	if (this->nameHeader == nullptr) {
		return movies;
	}
	if (direction) {
		this->getRecordsByNameASC(movies, this->nameHeader);
	} else {
		this->getRecordsByNameDSC(movies, this->nameHeader);
	}
	return movies;
}

void PlaitedRecordList::getRecordsByNameASC(vector<PlayerRecord> &movies,
		RecordNode *current) {
	if (current != nullptr) {
		movies.push_back(*(current->getRecord()));
		this->getRecordsByNameASC(movies, current->getNextName());
	}
}

void PlaitedRecordList::getRecordsByNameDSC(vector<PlayerRecord> &movies,
		RecordNode *current) {
	if (current != nullptr) {
		this->getRecordsByNameDSC(movies, current->getNextName());
		movies.push_back(*(current->getRecord()));
	}
}

/**
 * Gets the movies by length depending on direction
 *
 * @pre none
 * @post none
 *
 * @param direction true for ascending, false for descending
 * @return the list of movies in order
 */
vector<PlayerRecord> PlaitedRecordList::getRecordsByLevel(bool direction) {
	vector<PlayerRecord> movies;
	if (this->levelHeader == nullptr) {
		return movies;
	}
	if (direction) {
		this->getRecordsByLevelASC(movies, this->levelHeader);
	} else {
		this->getRecordsByLevelDSC(movies, this->levelHeader);
	}
	return movies;
}

void PlaitedRecordList::getRecordsByLevelASC(vector<PlayerRecord> &records,
		RecordNode *current) {
	if (current != nullptr) {
		records.push_back(*(current->getRecord()));
		this->getRecordsByLevelASC(records, current->getNextLevel());
	}

}

void PlaitedRecordList::getRecordsByLevelDSC(vector<PlayerRecord> &records,
		RecordNode *current) {
	if (current != nullptr) {
		this->getRecordsByLevelDSC(records, current->getNextLevel());
		records.push_back(*(current->getRecord()));
	}
}

/**
 * Gets the movies by length depending on direction
 *
 * @pre none
 * @post none
 *
 * @param direction true for ascending, false for descending
 * @return the list of movies in order
 */
vector<PlayerRecord> PlaitedRecordList::getRecordsByTime(bool direction) {
	vector<PlayerRecord> records;
	if (this->timeHeader == nullptr) {
		return records;
	}
	if (direction) {
		this->getRecordsByTimeASC(records, this->timeHeader);
	} else {
		this->getRecordsByTimeDSC(records, this->timeHeader);
	}
	return records;
}

void PlaitedRecordList::getRecordsByTimeASC(vector<PlayerRecord> &records,
		RecordNode *current) {
	if (current != nullptr) {
		this->getRecordsByTimeASC(records, current->getNextTime());
		records.push_back(*(current->getRecord()));
	}
}

void PlaitedRecordList::getRecordsByTimeDSC(vector<PlayerRecord> &records,
		RecordNode *current) {
	if (current != nullptr) {
		records.push_back(*(current->getRecord()));
		this->getRecordsByTimeDSC(records, current->getNextTime());
	}

}

RecordNode* PlaitedRecordList::getNodeWithHighestTime() {
	RecordNode *highest = this->timeHeader;
	RecordNode *current = this->timeHeader;
	while (current != nullptr) {
		if (current->getRecord()->getTime() > highest->getRecord()->getTime()) {
			highest = current;
		}
		current = current->getNextTime();
	}
	return highest;
}

} /* namespace model */
