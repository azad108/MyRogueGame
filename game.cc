#include <string>
#include <iostream>
#include <memory>
#include <sstream>
#include "game.h"
#include "floor.h"
#include "person.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "potion.h"
#include "treasure.h"
using namespace std;


//Init floor, if allFF then read everything from file
bool game::startGame(string sourceFile,bool allFF) {
	gameFloor = make_shared<floor>();
	if(allFF) {
		gameFloor->initFloorFF(sourceFile,1,thePlayer);
	} else {
		gameFloor->initFloor(sourceFile);
	}
	newFloor = false;
        floorNum = 1;
	return(true);
}


//either stars a new floor normally or read it from a file, returns the roomt he player is in
// if stairs still need to be spawned, otherwise returns -1
int game::startNewFloor(string sourceFile, shared_ptr<person> thePlayer,bool allFF) {
        gameFloor = nullptr;
	gameFloor = make_shared<floor>();
        if(allFF) {
		gameFloor->initFloorFF(sourceFile,floorNum,thePlayer);
        	return(-1);
	} else {
		gameFloor->initFloor(sourceFile);
        	int roomNum = rand() % gameFloor->numRooms();
        	int cell = rand() % gameFloor->roomSize(roomNum);
        	gameFloor->placePerson(thePlayer,roomNum,cell);
        	return(roomNum);
	}
}

int game::getFloorNum() {
	return floorNum;
}

bool game::isNewFloor() {
	return newFloor;
}

void game::setNewFloor(bool newSetting) {
	newFloor = newSetting;
}

bool game::isWon(int winningNumber) {
	return winningNumber == floorNum;
}

//get outPut string with the game floor.
string game::getOutput() {
	string output = "";
	output += gameFloor->getOutput();
	return output;
}


//return the player pointer for main interfacing
shared_ptr<person> game::getPlayer() {
	if(thePlayer == nullptr) {
		thePlayer = gameFloor->findPlayer();
	}
	return thePlayer;
}


//spawns player and places it on a random tile
void game::spawnPlayer(string race) {
	thePlayer = make_shared<basicPerson>("player");
	if(race == "d") {
		thePlayer = make_shared<drow>(thePlayer);
	} else if(race == "v") {
		thePlayer = make_shared<vampire>(thePlayer);
	} else if(race == "t") {
                thePlayer = make_shared<troll>(thePlayer);
        } else if(race == "g") {
                thePlayer = make_shared<goblin>(thePlayer);
        }
}

int game::placePlayer(shared_ptr<person> thePlayer) {
	int roomNum = rand() % gameFloor->numRooms();
        int cell = rand() % gameFloor->roomSize(roomNum);
        gameFloor->placePerson(thePlayer,roomNum,cell);
        return roomNum;
}


//spawns the stairs taking in the room the player is in to ensure they
//are placed in different rooms
void game::spawnStairs(int playerRoom) {
	int stairRoom = rand() % gameFloor->numRooms();
	while(stairRoom == playerRoom) {
		stairRoom = rand() %gameFloor->numRooms();
	}
	int cell = rand() % gameFloor->roomSize(stairRoom);
	gameFloor->placeStair(stairRoom,cell);
}

shared_ptr<person> randomEnemy() {
	int enemyNum = rand() % 18;
	shared_ptr<person> newEnemy = make_shared<basicPerson>("enemy");
	if(0<= enemyNum && enemyNum <=3) {
		newEnemy = make_shared<human>(newEnemy);
	} else if(4<= enemyNum && enemyNum <=6) {
		newEnemy = make_shared<dwarf>(newEnemy);
	} else if(7<= enemyNum && enemyNum <=11) {
		newEnemy = make_shared<halfling>(newEnemy);
	} else if(12 <= enemyNum && enemyNum <=13) {
		newEnemy = make_shared<elf>(newEnemy);
	} else if(14 <= enemyNum && enemyNum <=15) {
		newEnemy = make_shared<orc>(newEnemy);
	} else if(16 <= enemyNum && enemyNum <=17) {
		newEnemy = make_shared<merchant>(newEnemy);
	}
	return(newEnemy);
}

//spawns the given number of enemies and places them
void game::spawnEnemies(int numEnemies) {
	for(int i=0;i<numEnemies;++i) {
		//pick random enemy
		shared_ptr<person> newEnemy = randomEnemy();
		int roomNum = rand() % gameFloor->numRooms();
        	int cell = rand() % gameFloor->roomSize(roomNum);;
		while(!gameFloor->placePerson(newEnemy,roomNum,cell)) {
			roomNum = rand() % gameFloor->numRooms();
                	cell = rand() % gameFloor->roomSize(roomNum);;
		}
	}
}

shared_ptr<potion> randomPotion() {
	int potionNum = rand() % 6;
	shared_ptr<potion> randPotion;
	if(potionNum == 0) {
		randPotion = make_shared<RH>();
        } else if(potionNum == 1) {
             	randPotion = make_shared<BA>();
	} else if(potionNum == 2) {
             	randPotion = make_shared<BD>();
        } else if(potionNum == 3) {
              	randPotion = make_shared<PH>();
        } else if(potionNum == 4) {
		randPotion = make_shared<WA>();
        } else if(potionNum == 5) {
                randPotion = make_shared<WD>();
	}
	return(randPotion);	
}

//spawns the given number of potions and places them
void game::spawnPotions(int numPotions) {
        for(int i=0;i<numPotions;++i) {
                auto newPotion = randomPotion();
                int roomNum = rand() % gameFloor->numRooms();
                int cell = rand() % gameFloor->roomSize(roomNum);;
                while(!gameFloor->placeItem(newPotion,roomNum,cell)) {
                        roomNum = rand() % gameFloor->numRooms();
                        cell = rand() % gameFloor->roomSize(roomNum);;
                }
        }
}

shared_ptr<treasure> randomTreasure() {
        int treasureNum = rand() % 8;
        shared_ptr<treasure> randTreasure;
        if(0 <= treasureNum && treasureNum <= 4) {
		randTreasure = make_shared<basic>(1);
        } else if(5 <= treasureNum && treasureNum <= 6) {
		randTreasure = make_shared<basic>(2);
	} else {
		randTreasure = make_shared<dragonHoard>();
	}
	return(randTreasure);
}

//spawns the given number of treasure and places them
void game::spawnTreasure(int numTreasure) {
        for(int i=0;i<numTreasure;++i) {
                auto newTreasure = randomTreasure();
		int roomNum = rand() % gameFloor->numRooms();
                int cell = rand() % gameFloor->roomSize(roomNum);;
                while(!gameFloor->placeItem(newTreasure,roomNum,cell)) {
                        roomNum = rand() % gameFloor->numRooms();
                        cell = rand() % gameFloor->roomSize(roomNum);;
                }
        }
	gameFloor->linkDragons();
}


//used to have the player attack an enemy, returns the output sting for this interaction;
string game::playerAttack(int rowChange, int colChange) {
	int row = thePlayer->getRow() + rowChange;
	int col = thePlayer->getCol() + colChange;
	shared_ptr<person> enemy = gameFloor->getOccupantAt(row,col);
	ostringstream output;
	if(enemy != nullptr) {
		int damage = enemy->getAttackedBy(thePlayer);
		if(enemy->getStats().HP == 0) {
			gameFloor->killOccupant(row,col);	
			if(enemy->getRace() != "d" && enemy->getRace() != "h" && enemy->getRace() != "m") {
				shared_ptr<stats> newStats = make_shared<stats>();
				*newStats = thePlayer->getRawStats();
				newStats->GOLD += (rand() % 2) *2;
				thePlayer->setStats(newStats);
			}
		}

		output << "Player did " << damage << "HP damage.";
	} else {
		output << "Nothing to attack there." << endl;
	}
	return output.str();
}

//used to have player use an item;
string game::useItem(int rowChange, int colChange) {
        int row = thePlayer->getRow() + rowChange;
        int col = thePlayer->getCol() + colChange;
        shared_ptr<item> theItem = gameFloor->getItemAt(row,col);
	ostringstream output;
	if(theItem != nullptr) {
		string itemString = thePlayer->useItem(theItem);
		
		gameFloor->killItem(row,col);

        	output << "Player used a " << itemString << ". ";
	} else {
		output << "Nothing to use there.";
	}
        return output.str();
}

//takes in the row and col change then moves the player
string game::movePlayer(int rowChange, int colChange) {
        int row = thePlayer->getRow() + rowChange;
        int col = thePlayer->getCol() + colChange;
	string outPut = "";
	if(gameFloor->isStairs(row,col)) {
		newFloor = true;
		++floorNum;
	}
	if(!gameFloor->movePerson(thePlayer,rowChange,colChange)) {
		outPut += "Cant't move there right now.";
	}
	if(gameFloor->getItemAt(row,col) != nullptr && 
		gameFloor->getItemAt(row,col)->getType() == "treasure" && gameFloor->getItemAt(row,col)->getGuard() == nullptr) {
		useItem(0,0);
	}
	outPut += gameFloor->findPotions(thePlayer);
	return outPut;
}

//starts and ends the turn for the enemies, also returns output for the turn.
string game::toggleTurn(bool turn) {
	if(turn) {
		return gameFloor->actEnemies(thePlayer);
	} else {
		gameFloor->endTurn();
		return "";
	}
}

