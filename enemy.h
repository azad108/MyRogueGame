#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <string>
#include <vector>
#include "person.h"

class human: public specialPerson {
 public:
	human(std::shared_ptr<person>);
	~human();
	std::string getOutput();
};

class dwarf: public specialPerson {
 public:
        dwarf(std::shared_ptr<person>);
        ~dwarf();
	std::string getOutput();
};

class elf: public specialPerson {
 public:
        elf(std::shared_ptr<person>);
        ~elf();
        std::string getOutput();
};

class orc: public specialPerson {
 public:
        orc(std::shared_ptr<person>);
        ~orc();
        std::string getOutput();
};

class merchant: public specialPerson {
	static bool hostile;
 public:
        merchant(std::shared_ptr<person>);
        ~merchant();
        std::string getOutput();
	bool isHostile();
	void setHostile(bool);
	int getAttackedBy(std::shared_ptr<person>);
};

class dragon: public specialPerson {
	std::shared_ptr<item> hoard;
 public:
	void setHoard(std::shared_ptr<item>);
	std::shared_ptr<item> getHoard();

        dragon(std::shared_ptr<person>);
        ~dragon();
        std::string getOutput();
};

class halfling: public specialPerson {
 public:
        halfling(std::shared_ptr<person>);
        ~halfling();
        std::string getOutput();
};

#endif
