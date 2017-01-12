#include <iostream>
#include <string>
#include "treasure.h"

using namespace std;

treasure::treasure(string type):item{"treasure"},treasureType{type}{};

string treasure::getOutput() {
	return("G");
}

string treasure::getSubType() {
	return(treasureType);
}

void treasure::setGuard(shared_ptr<person> newGuard) {}

shared_ptr<person> treasure::getGuard() {
	return nullptr;
}

bool treasure::getSeen(){
return(false);
}
void treasure::setSeen(bool){}
string treasure::lookAt(){
return("TREASURE");
}
void treasure::setMagnitude(float NM){}
float treasure::getMagnitude(){return(-1);}

treasure::~treasure(){};


basic::basic(int value):treasure{"basic"},value{value}{}

void basic::modify(std::shared_ptr<stats> playerStats) {
        int raise = value;
        playerStats->GOLD += raise;
}

dragonHoard::dragonHoard():treasure{"dragonHoard"},value{6} {
}

void dragonHoard::setGuard(shared_ptr<person> newGuard) {
	dragon = newGuard;
}

shared_ptr<person> dragonHoard::getGuard() {
	return dragon;
}

void dragonHoard::modify(std::shared_ptr<stats> playerStats) {
        int raise = value;
        playerStats->GOLD += raise;
}
