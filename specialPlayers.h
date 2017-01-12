#ifndef __SPECPLAYER_H__
#define __SPECPLAYER_H__

#include <string>
#include <vector>
#include "person.h"

class specialPlayer: public person {
	std::string race;
	int ATK,DEF,HP,GOLD;
	//vector<potion*> tempPots;
	//vector<potion*> permPots;
 public:
	std::string getOutput();
	player(std::string);
	//void addTempPot(potion*);
	//void addPermPot(potion*);
};

#endif
