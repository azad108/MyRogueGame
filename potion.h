#ifndef __POTION_H__
#define __POTION_H__

#include <string>
#include <memory>
#include "item.h"
#include "person.h"

class potion: public item {
	std::string potionType;
	float magnitude;
 public:
	potion(std::string);
	std::string getOutput();
	std::string getSubType();
	std::string lookAt();
	void setMagnitude(float);
	float getMagnitude();
	virtual void setSeen(bool)=0;
	virtual bool getSeen()=0;
	virtual void modify(std::shared_ptr<stats>) = 0;
	virtual ~potion()=0;
};

class RH: public potion {
	static bool beenSeen;
 public:
	void setSeen(bool);
	bool getSeen();
 	RH();
	void modify(std::shared_ptr<stats>);
};


class BA: public potion {
        static bool beenSeen;
 public:
        void setSeen(bool);
        bool getSeen();
 	BA();
	void modify(std::shared_ptr<stats>);
};


class BD: public potion {
        static bool beenSeen;
 public:
        void setSeen(bool);
        bool getSeen();
 	BD();
	void modify(std::shared_ptr<stats>);
};


class PH: public potion {
        static bool beenSeen;
 public:
        void setSeen(bool);
        bool getSeen();
 	PH();
	void modify(std::shared_ptr<stats>);
};


class WA: public potion {
        static bool beenSeen;
 public:
        void setSeen(bool);
        bool getSeen();
 	WA();
	void modify(std::shared_ptr<stats>);
};


class WD: public potion {
        static bool beenSeen;
 public:
	void setSeen(bool);
	bool getSeen();
 	WD();
	void modify(std::shared_ptr<stats>);
};
#endif
