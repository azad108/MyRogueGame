#include <iostream>
#include <string>
#include "potion.h"

using namespace std;

potion::potion(string type):item{"potion"},potionType{type},magnitude{1}{};

string potion::getOutput() {
	return("P");
}

string potion::getSubType() {
	return(potionType);
}

string potion::lookAt() {
	if(getSeen()) {
		return(potionType);
	}
	return("unknown potion");
}

void potion::setMagnitude(float newMagnitude) {
	magnitude = newMagnitude;
}

float potion::getMagnitude() {
	return magnitude;
}

potion::~potion(){};


void RH::setSeen(bool newSeen) {
	beenSeen = newSeen;
}

bool RH::getSeen() {
	return(beenSeen);
}

bool RH::beenSeen = false;

RH::RH():potion{"RH"} {}

void RH::modify(shared_ptr<stats> playerStat) {
	int raise = getMagnitude() * 10;
	if (playerStat->HP + raise >= playerStat->MAXHP) {
		playerStat->HP = playerStat->MAXHP;
	} else playerStat->HP += raise;
}

void BA::setSeen(bool newSeen) {
        beenSeen = newSeen;
}

bool BA::getSeen() {
        return(beenSeen);
}

BA::BA() :potion{"BA"}{}

bool BA::beenSeen = false;

void BA::modify(shared_ptr<stats> playerStat) {
	int raise = getMagnitude() * 5;
	playerStat->ATK += raise;
}

void BD::setSeen(bool newSeen) {
        beenSeen = newSeen;
}

bool BD::getSeen() {
        return(beenSeen);
}

bool BD::beenSeen = false;

BD::BD():potion{"BD"}{}

void BD::modify(shared_ptr<stats> playerStat) {
	int raise = getMagnitude() * 5;
	playerStat->DEF += raise;
}

void PH::setSeen(bool newSeen) {
        beenSeen = newSeen;
}

bool PH::getSeen() {
        return(beenSeen);
}

bool PH::beenSeen = false;

PH::PH():potion{"PH"}{}

void PH::modify(shared_ptr<stats> playerStat) {
	int raise = getMagnitude() * 10;
	if (playerStat->HP <= raise) {
		playerStat->HP = 0;
	} else playerStat->HP -= raise;
}

void WA::setSeen(bool newSeen) {
        beenSeen = newSeen;
}

bool WA::getSeen() {
        return(beenSeen);
}

bool WA::beenSeen = false;

WA::WA():potion{"WA"}{}

void WA::modify(shared_ptr<stats> playerStat) {
	int raise = getMagnitude() * 5;
	if (playerStat->ATK <= raise) {
		playerStat->ATK = 0;
	} else playerStat->ATK -= raise;
}

void WD::setSeen(bool newSeen) {
        beenSeen = newSeen;
}

bool WD::getSeen() {
        return(beenSeen);
}

bool WD::beenSeen = false;

WD::WD():potion{"WD"}{}

void WD::modify(shared_ptr<stats> playerStat) {
	int raise = getMagnitude() * 5;
	if (playerStat->DEF <= raise) {
		playerStat->DEF = 0;
	} else playerStat->DEF -= raise;
}
