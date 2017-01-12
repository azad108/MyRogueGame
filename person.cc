#include "person.h"
#include <string>
#include <iostream>
#include <math.h>
#include <memory>
#include <vector>
#include "item.h"
#include "potion.h"

using namespace std;

stats::stats():ATK{25},DEF{25},HP{125},MAXHP{125},GOLD{0}{};


person::person(string type){};
person::~person(){};

basicPerson::basicPerson(string type):person{type},type{type},row{-1},col{-1},tookTurn{false}{
	shared_ptr<stats> defaultStats = make_shared<stats>();
	if(type == "enemy") {
		defaultStats->HP = 10;
	}
	
	personStats = defaultStats;	
	setRace("s");
};

basicPerson::~basicPerson(){};


string basicPerson::getOutput() {
	if(getType() == "player") {
		return("@");
	} else {
		return("E");
	}
}

bool basicPerson::getTookTurn() {
        return tookTurn;
}

int basicPerson::getRow() {
	return row;
}

int basicPerson::getCol() {
	return col;
}

stats basicPerson::getStats() {
        shared_ptr<stats> toReturn = make_shared<stats>();
        *toReturn = *personStats;
        for(unsigned i=0; i<permPotions.size();++i) {
                permPotions[i]->modify(toReturn);
        }
        for(unsigned j=0; j<tempPotions.size();++j) {
                tempPotions[j]->modify(toReturn);
        }
        return *toReturn;
}

stats basicPerson::getRawStats() {
	return(*personStats);
}

string basicPerson::getType() {
	return type;
}

string basicPerson::getRace() {
	return race;
}

shared_ptr<item> basicPerson::getHoard(){return nullptr;}

void basicPerson::setTookTurn(bool newTookTurn) {
        tookTurn = newTookTurn;
}

void basicPerson::setPosn(int newRow, int newCol) {
	row = newRow;
	col = newCol;
}

void basicPerson::setStats(shared_ptr<stats> newStats) {
	personStats=newStats;
}

void basicPerson::setRace(string newRace) {
	race = newRace;
}

void basicPerson::setHostile(bool newHostile){
}

void basicPerson::setHoard(std::shared_ptr<item> newHoard){
}

int basicPerson::getAttackedBy(shared_ptr<person> attacker) {
	//ceiling((100/(100+Def (Def ender)))⇤Atk(Attacker))
	float defenderDef = personStats->DEF;
	stats attackerStats = attacker->getStats();
	float attackerAtk = attackerStats.ATK;
	//check if attacker is vampire if so add 5HP
	if(attacker->getRace() == "v") {
		shared_ptr<stats> newStats = make_shared<stats>();
		*newStats = attacker->getRawStats();
		if(getRace() != "w") {
			newStats->HP += 5;
		} else {
			newStats->HP -= 5;
		}
		attacker->setStats(newStats);
        }
	float damage = ceil((100/(100+defenderDef))*attackerAtk);
	
	// check to see if attacker is hostile
	if(attacker->isHostile()) {
		personStats->HP -= damage;	
	}
	
	//if attacker is elf it gets a second attack, unless player is drow
	if(attacker->getRace() == "e") {
		if(getRace() != "d") {
			personStats->HP -= damage;
		}
	} else if(attacker->getRace() == "o") {
		if(getRace() == "g") {
			personStats->HP -= (damage * 0.5);
		}
	} 
	
	if(getRace() == "l" || attacker->getType() == "enemy") {
		if((rand() % 2) == 1) {
			personStats->HP += damage;
		}
	}

	if(personStats->HP <= 0) {
		personStats->HP = 0;
		if(attacker->getRace() == "g") {
		        shared_ptr<stats> newStats = make_shared<stats>();
                	attackerStats.GOLD += 5;
                	*newStats = attackerStats;
                	attacker->setStats(newStats);
		}
	}
	return damage;
}

string basicPerson::useItem(shared_ptr<item> theItem) {
	string itemType = theItem->getType();
	string outPut = "";
	if(itemType == "potion") {
		string potionType = theItem->getSubType();
		outPut += potionType + " " + itemType;
		if(potionType == "RH" || potionType == "PH") {
			permPotions.emplace_back(theItem);
			theItem->setSeen(true);		
		} else {
			tempPotions.emplace_back(theItem);
			theItem->setSeen(true);
		}
	} else if(itemType == "treasure") {
		string treasureType = theItem->getSubType();
		outPut += treasureType + " " + itemType;
		theItem->modify(personStats);
	}
	return outPut;
}

void basicPerson::clearTempPotions() {
	tempPotions.clear();
}

bool basicPerson::isHostile() {
	return true;
}

//Special person dummy impliamentation, decorator in decorator pattern:
specialPerson::specialPerson(std::shared_ptr<person> base):person{base->getType()},basePerson(base){};
        string outPut = "";
specialPerson::~specialPerson(){};

string specialPerson::getOutput() {
	return basePerson->getOutput();
}

bool specialPerson::getTookTurn() {
	return basePerson->getTookTurn();
}

int specialPerson::getRow() {
	return basePerson->getRow();
}

int specialPerson::getCol() {
	return basePerson->getCol();
}

stats specialPerson::getStats() {
	return basePerson->getStats();
}

stats specialPerson::getRawStats() {
	return basePerson->getRawStats();
}

string specialPerson::getType() {
	return basePerson->getType();
}

string specialPerson::getRace() {
	return basePerson->getRace();
}

shared_ptr<item> specialPerson::getHoard() {
	return basePerson->getHoard();
}

void specialPerson::setTookTurn(bool newTookTurn) {
	basePerson->setTookTurn(newTookTurn);
}

void specialPerson::setPosn(int row, int col) {
	basePerson->setPosn(row,col);
}

void specialPerson::setStats(shared_ptr<stats> newStats) {
	basePerson->setStats(newStats);
}

void specialPerson::setRace(string newRace) {
	basePerson->setRace(newRace);
}

void specialPerson::setHostile(bool newHostile){
	basePerson->setHostile(newHostile);
}

void specialPerson::setHoard(shared_ptr<item> newHoard) {
	basePerson->setHoard(newHoard);
}

int specialPerson::getAttackedBy(std::shared_ptr<person> attacker) {
	return basePerson->getAttackedBy(attacker);
}

string specialPerson::useItem(std::shared_ptr<item> theItem) {
	return basePerson->useItem(theItem);
}

void specialPerson::clearTempPotions() {
	basePerson->clearTempPotions();
}

bool specialPerson::isHostile() {
	return basePerson->isHostile();
}
