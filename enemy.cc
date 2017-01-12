#include <iostream>
#include <math.h>
#include "person.h"
#include "enemy.h"
using namespace std;

human::human(std::shared_ptr<person> basePerson):specialPerson{basePerson} {
	shared_ptr<stats> newStats = make_shared<stats>();
	newStats->HP = 140;
	newStats->ATK = 20;
	newStats->DEF = 20;
	newStats->MAXHP = 140;
	setStats(newStats);
	setRace("h");
}

human::~human(){};

string human::getOutput() {
	return("H");
}

dwarf::dwarf(std::shared_ptr<person> basePerson):specialPerson{basePerson} {
        shared_ptr<stats> newStats = make_shared<stats>();
        newStats->HP = 100;
        newStats->ATK = 20;
        newStats->DEF = 30;
        newStats->MAXHP = 100;
        setStats(newStats);
	setRace("w");
}

dwarf::~dwarf(){};

string dwarf::getOutput() {
        return("W");
}

elf::elf(std::shared_ptr<person> basePerson):specialPerson{basePerson} {
        shared_ptr<stats> newStats = make_shared<stats>();
        newStats->HP = 140;
        newStats->ATK = 30;
        newStats->DEF = 10;
        newStats->MAXHP = 140;
        setStats(newStats);
	setRace("e");
}

elf::~elf(){};

string elf::getOutput() {
        return("E");
}

orc::orc(std::shared_ptr<person> basePerson):specialPerson{basePerson} {
        shared_ptr<stats> newStats = make_shared<stats>();
        newStats->HP = 180;
        newStats->ATK = 30;
        newStats->DEF = 25;
        newStats->MAXHP = 180;
        setStats(newStats);
	setRace("o");
}

orc::~orc(){};

string orc::getOutput() {
        return("O");
}

merchant::merchant(std::shared_ptr<person> basePerson):specialPerson{basePerson} {
        shared_ptr<stats> newStats = make_shared<stats>();
        newStats->HP = 30;
        newStats->ATK = 70;
        newStats->DEF = 5;
        newStats->MAXHP = 30;
        setStats(newStats);
	setRace("m");
}

bool merchant::hostile = false;

merchant::~merchant(){};

string merchant::getOutput() {
        return("M");
}

int merchant::getAttackedBy(shared_ptr<person> attacker) {
 //ceiling((100/(100+Def (Def ender)))⇤Atk(Attacker))
        //if mercant is getting attacked 
	setHostile(true);
	cout << "SETHOSTIMETRUELKJH" <<endl;

	stats personStats = getStats();
	float defenderDef = personStats.DEF;
        stats attackerStats = attacker->getStats();
        float attackerAtk = attackerStats.ATK;
        //check if attacker is vampire if so add 5HP
        if(attacker->getRace() == "v") {
                shared_ptr<stats> newStats = make_shared<stats>();
                cout << "DWARF?: " << getRace() << endl;
                if(getRace() != "w") {
                        attackerStats.HP += 5;
                } else {
                        attackerStats.HP -= 5;
                }
                *newStats = attackerStats;
                attacker->setStats(newStats);
        }
        float damage = ceil((100/(100+defenderDef))*attackerAtk);

        // check to see if attacker is hostile
        if(attacker->isHostile()) {
                personStats.HP -= damage;
        }
	
	if(personStats.HP <= 0) {
                personStats.HP = 0;
                if(attacker->getRace() == "g") {
                        shared_ptr<stats> newStats = make_shared<stats>();
                        attackerStats.GOLD += 5;
                        *newStats = attackerStats;
                        attacker->setStats(newStats);
                }
        }
	
	shared_ptr<stats> newStats = make_shared<stats>();
	*newStats = personStats;
	setStats(newStats);
	
        return damage;	
}

bool merchant::isHostile() {
	return(hostile);
}

void merchant::setHostile(bool newHostile) {
	hostile = newHostile;
}

dragon::dragon(std::shared_ptr<person> basePerson):specialPerson{basePerson},hoard{nullptr} {
        shared_ptr<stats> newStats = make_shared<stats>();
        newStats->HP = 150;
        newStats->ATK = 20;
        newStats->DEF = 20;
        newStats->MAXHP = 150;
        setStats(newStats);
	setRace("d");
}

void dragon::setHoard(std::shared_ptr<item> newHoard) {
	hoard = newHoard;
}


std::shared_ptr<item> dragon::getHoard() {
	return hoard;
}


dragon::~dragon(){};

string dragon::getOutput() {
        return("D");
}

halfling::halfling(std::shared_ptr<person> basePerson):specialPerson{basePerson} {
        shared_ptr<stats> newStats = make_shared<stats>();
        newStats->HP = 100;
        newStats->ATK = 15;
        newStats->DEF = 20;
        newStats->MAXHP = 100;
        setStats(newStats);
	setRace("l");
}

halfling::~halfling(){};

string halfling::getOutput() {
        return("L");
}
