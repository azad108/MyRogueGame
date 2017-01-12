#include <iostream>
#include "person.h"
#include "player.h"
using namespace std;

drow::drow(std::shared_ptr<person> basePerson):specialPerson{basePerson} {
	shared_ptr<stats> newStats = make_shared<stats>();
	newStats->HP = 150;
	newStats->ATK = 25;
	newStats->DEF = 15;
	newStats->MAXHP = 150;
	setStats(newStats);
	setRace("d");
}

drow::~drow(){};

string drow::useItem(shared_ptr<item> theItem) {
        string itemType = theItem->getType();
        if(itemType == "potion") {
	 	theItem->setMagnitude(1.5); 
        }
        return basePerson->useItem(theItem);;
}


vampire::vampire(std::shared_ptr<person> basePerson):specialPerson{basePerson} {
        shared_ptr<stats> newStats = make_shared<stats>();
        newStats->HP = 50;
        newStats->ATK = 25;
        newStats->DEF = 25;
        newStats->MAXHP = 999;
        setStats(newStats);
	setRace("v");
}

vampire::~vampire(){};


troll::troll(std::shared_ptr<person> basePerson):specialPerson{basePerson} {
        shared_ptr<stats> newStats = make_shared<stats>();
        newStats->HP = 120;
        newStats->ATK = 25;
        newStats->DEF = 15;
        newStats->MAXHP = 120;
        setStats(newStats);
	setRace("t");
}

troll::~troll(){};

goblin::goblin(std::shared_ptr<person> basePerson):specialPerson{basePerson} {
        shared_ptr<stats> newStats = make_shared<stats>();
        newStats->HP = 110;
        newStats->ATK = 15;
        newStats->DEF = 20;
        newStats->MAXHP = 110;
        setStats(newStats);
	setRace("g");
}

goblin::~goblin(){};

