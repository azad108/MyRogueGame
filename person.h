#ifndef __PERSON_H__
#define __PERSON_H__

#include <string>
#include <vector>
#include <memory>
#include "item.h"
#include "potion.h"

class stats {
 public:
	int ATK,DEF,HP,MAXHP,GOLD;
	stats();
};

class person {
 public:
	//cTor dTor
        person(std::string);
        virtual ~person();

        //accessor methods
        virtual std::string getOutput()=0;
        virtual bool getTookTurn()=0;
        virtual int getRow()=0;
        virtual int getCol()=0;
        virtual stats getStats()=0;
	virtual stats getRawStats()=0;
        virtual std::string getType()=0;
        virtual std::string getRace()=0;
	virtual std::shared_ptr<item> getHoard()=0;

        //set methods
        virtual void setTookTurn(bool)=0;
        virtual void setPosn(int,int)=0;
	virtual void setStats(std::shared_ptr<stats>)=0;
	virtual void setRace(std::string)=0;	
	virtual void setHostile(bool)=0;
	virtual void setHoard(std::shared_ptr<item>)=0;

        //actual player functions
        virtual int getAttackedBy(std::shared_ptr<person>)=0;
        virtual std::string useItem(std::shared_ptr<item>)=0;
        virtual void clearTempPotions()=0;
	virtual bool isHostile()=0;
};

class basicPerson: public person {
        std::string type;
	std::string race;
        int row,col;
        bool tookTurn;
        std::vector<std::shared_ptr<item>> permPotions;
        std::vector<std::shared_ptr<item>> tempPotions;
 protected:
        std::shared_ptr<stats> personStats;
 public:
	//cTor dTor
	basicPerson(std::string type);
        ~basicPerson();
	
	//accessor methods
        std::string getOutput();
        bool getTookTurn();
        int getRow();
	int getCol();
	stats getStats();
	stats getRawStats();
        std::string getType();
        std::string getRace();
	std::shared_ptr<item> getHoard();

	//set methods
	void setTookTurn(bool);
        void setPosn(int,int);
	void setStats(std::shared_ptr<stats>);
        void setRace(std::string);
	void setHostile(bool);
	void setHoard(std::shared_ptr<item>);
	
	//actual player functions
	int getAttackedBy(std::shared_ptr<person>);
        std::string useItem(std::shared_ptr<item>);
        void clearTempPotions();
	bool isHostile();
};

class specialPerson: public person {
 protected:
	std::shared_ptr<person> basePerson;
 public:
	//cTor dTor
        specialPerson(std::shared_ptr<person>);
        virtual ~specialPerson()=0;

        //accessor methods
        virtual std::string getOutput();
        virtual bool getTookTurn();
        virtual int getRow();
        virtual int getCol();
        virtual stats getStats();
	virtual stats getRawStats();
	virtual std::string getType();
        virtual std::string getRace();
	virtual std::shared_ptr<item> getHoard();

        //set methods
        virtual void setTookTurn(bool);
        virtual void setPosn(int,int);
	virtual void setStats(std::shared_ptr<stats>);
	virtual void setRace(std::string);
	virtual void setHostile(bool);	
	virtual void setHoard(std::shared_ptr<item>);

        //actual player functions
        virtual int getAttackedBy(std::shared_ptr<person>);
        virtual std::string useItem(std::shared_ptr<item>);
        virtual void clearTempPotions();
	virtual bool isHostile();
};

#endif
