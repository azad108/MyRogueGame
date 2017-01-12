#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <vector>
#include "person.h"

class drow: public specialPerson {
 public:
	drow(std::shared_ptr<person>);
	~drow();
	std::string useItem(std::shared_ptr<item>); //potion effects magnified by 1.5x
};

class vampire: public specialPerson {
 public:
	vampire(std::shared_ptr<person>);
	~vampire();
};

class troll: public specialPerson {
 public:
        troll(std::shared_ptr<person>);
        ~troll();
};

class goblin: public specialPerson {
 public:
        goblin(std::shared_ptr<person>);
        ~goblin();
};
#endif
