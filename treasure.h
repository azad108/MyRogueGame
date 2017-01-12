#ifndef __TREASURE_H__
#define __TREASURE_H__

#include <string>
#include <memory>
#include "item.h"
#include "person.h"

class treasure: public item {
	std::string treasureType;
 public:
	treasure(std::string);
	std::string getOutput();
	std::string getSubType();
	void setSeen(bool);
	bool getSeen();
	std::string lookAt();
	void setMagnitude(float);
	float getMagnitude();
	virtual void setGuard(std::shared_ptr<person>);
	virtual std::shared_ptr<person> getGuard();
	virtual void modify(std::shared_ptr<stats>) = 0;
	virtual ~treasure()=0;
};

class basic: public treasure {
        int value;
 public:
        basic(int);
        void modify(std::shared_ptr<stats>);
};

class dragonHoard: public treasure {
        std::shared_ptr<person> dragon;
        int value;
 public:
	void setGuard(std::shared_ptr<person>);
	std::shared_ptr<person> getGuard();
        dragonHoard();
        void modify(std::shared_ptr<stats>);
};

#endif
