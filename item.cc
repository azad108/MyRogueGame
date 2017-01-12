#include "item.h"
#include "person.h"
using namespace std;

item::item(string type):type{type},row{-1},col{-1}{};

item::~item(){};

void item::setPosn(int newRow, int newCol) {
	row = newRow;
	col = newCol;
}

void item::setGuard(shared_ptr<person> newGuard) {}

shared_ptr<person> item::getGuard() {return nullptr;}

int item::getRow() {
	return(row);
}

int item::getCol() {
	return(col);
}

string item::getType() {
	return(type);
}
