#include "cell.h"
#include <string>
#include <iostream>
using namespace std;

void cell::setType(char newType) {
	type=newType;
}

string cell::getType() {
	return(string(1,type));
}

void cell::setXY(int newRow, int newCol) {
	row = newRow;
	col = newCol;
}

bool cell::initCell(char type,int row,int col) {
	counted = false;
	setType(type);
	setXY(row,col);
	return true;
}

string cell::getOutput() {
	string output = "";
	if(occupant == nullptr && theItem == nullptr) {
		output += type;
	} else if(occupant != nullptr) {
		output += occupant->getOutput();
	} else if(theItem != nullptr) {
		output += theItem->getOutput();
	}
	return output;
}

int cell::getRow() {
	return row;
}

int cell::getCol() {
        return col;
}

shared_ptr<person> cell::getOccupant() {
	return occupant;
}

shared_ptr<item> cell::getItem() {
	return theItem;
}

bool cell::accountedFor() {
	return counted;
}

void cell::accounted() {
	counted = true;
}

bool cell::setOccupant(shared_ptr<person> newOccupant) {
	if(newOccupant == nullptr) {
		if(occupant->getHoard() != nullptr) {
			occupant->getHoard()->setGuard(nullptr);
		}
		occupant = nullptr;
		return(true);
	} else if((type == '.' || type == '+' || type == '#' || type == '/') && occupant == nullptr) {
		occupant = newOccupant;
		return(true);
	} else {
		return(false);
	}
}

bool cell::setItem(shared_ptr<item> newItem) {
        if(newItem == nullptr) {
                theItem = nullptr;
                return(true);
        } else if(type == '.') {
                theItem = newItem;
                return(true);
        } else {
                return(false);
        }
}

void cell::makeStair() {
	setType('\\');
}
