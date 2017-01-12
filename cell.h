#ifndef __CELL_H__
#define __CELL_H__

#include <string>
#include <memory>
#include "person.h"
#include "item.h"

class cell {
	char type;
	int row,col;
	void setXY(int,int);
	bool counted;
	std::shared_ptr<person> occupant;
	std::shared_ptr<item> theItem;
 public:
	void setType(char);
	std::string getType();
	std::string getOutput();
	bool initCell(char,int,int);
	bool accountedFor();
	void accounted();
	int getRow();
	int getCol();
	bool setOccupant(std::shared_ptr<person>);
	bool setItem(std::shared_ptr<item>);
	std::shared_ptr<person> getOccupant();
	std::shared_ptr<item> getItem();
	void makeStair();
};

#endif
