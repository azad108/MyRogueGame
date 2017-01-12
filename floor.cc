#include "floor.h"
#include "cell.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "item.h"
#include "treasure.h"
#include "potion.h"
#include "person.h"
#include "enemy.h"
#include "player.h"
using namespace std;


// used for initializing room vectors
bool floor::cascade(int row, int col, int roomNum) {
	// Check if current cell has been accounted for in a room, if so move on if not add it
	if(theFloor[row][col].accountedFor() == false) {
		theRooms[roomNum].emplace_back(&theFloor[row][col]);
		theFloor[row][col].accounted();
	}
	//cascade to all surrounding cells that are both floor tiles and have NOT been accounted for in a room
	if(theFloor[row-1][col].getOutput() == "." && !theFloor[row-1][col].accountedFor()) {
		cascade(row-1,col, roomNum);
	} if(theFloor[row-1][col+1].getOutput() == "." && !theFloor[row-1][col+1].accountedFor()) {
                cascade(row-1,col+1, roomNum);
        } if(theFloor[row][col+1].getOutput() == "." && !theFloor[row][col+1].accountedFor()) {
                cascade(row,col+1, roomNum);
        } if(theFloor[row+1][col+1].getOutput() == "." && !theFloor[row+1][col+1].accountedFor()) {
                cascade(row+1,col+1, roomNum);
        } if(theFloor[row+1][col].getOutput() == "." && !theFloor[row+1][col].accountedFor()) {
                cascade(row+1,col, roomNum);
        } if(theFloor[row+1][col-1].getOutput() == "." && !theFloor[row+1][col-1].accountedFor()) {
                cascade(row+1,col-1, roomNum);
        } if(theFloor[row][col-1].getOutput() == "." && !theFloor[row][col-1].accountedFor()) {
                cascade(row,col-1, roomNum);
        } if(theFloor[row-1][col-1].getOutput() == "." && !theFloor[row-1][col-1].accountedFor()) {
                cascade(row-1,col-1, roomNum);
        }
	return(true);
}

shared_ptr<person> floor::getOccupantAt(int row,int col) {
	return theFloor[row][col].getOccupant();
}

shared_ptr<item> floor::getItemAt(int row,int col) {
        return theFloor[row][col].getItem();
}

shared_ptr<person> floor::findPlayer() {
	for(unsigned roomNum=0;roomNum<theFloor.size();++roomNum) {
		for(unsigned cell=0;cell<theFloor[roomNum].size();++cell) {
			auto occupant = theFloor[roomNum][cell].getOccupant();
                        if(occupant != nullptr && occupant->getType() == "player") {
                                return(occupant);
                        }
               }
	}
	return(nullptr);
}

string floor::findPotions(shared_ptr<person> thePlayer) {
	int row = thePlayer->getRow();
	int col = thePlayer->getCol();
	string outPut = "";
	if(theFloor[row-1][col].getItem() != nullptr) {
		outPut += theFloor[row-1][col].getItem()->lookAt();

	} else if(theFloor[row-1][col+1].getItem() != nullptr) {
		outPut += theFloor[row-1][col+1].getItem()->lookAt();

	} else if(theFloor[row][col+1].getItem() != nullptr) {
                outPut += theFloor[row][col+1].getItem()->lookAt();

        } else if(theFloor[row+1][col+1].getItem() != nullptr) {
                outPut += theFloor[row+1][col+1].getItem()->lookAt();

        } else if(theFloor[row+1][col].getItem() != nullptr) {
                outPut += theFloor[row+1][col].getItem()->lookAt();

        } else if(theFloor[row+1][col-1].getItem() != nullptr) {
                outPut += theFloor[row+1][col-1].getItem()->lookAt();

        } else if(theFloor[row][col-1].getItem() != nullptr) {
                outPut += theFloor[row][col-1].getItem()->lookAt();

        } else if(theFloor[row-1][col-1].getItem() != nullptr) {
                outPut += theFloor[row-1][col-1].getItem()->lookAt();

        }
	if(outPut != "") {
		outPut = "Player sees a " + outPut;
	}
	return outPut;
}


//initializing the cell objects then storing them in theFloor and then init theRooms.
bool floor::initFloor(string sourceFile) {
	ifstream source {sourceFile}; //check to make sure file is good first
	int j=0;
	//theFloor init
	for(string row; getline(source,row);++j) {
		int len = row.length();
		vector<cell> vecRow(len,cell{});
		for(int i=0;i<len;++i) {
			vecRow[i].initCell(row[i],j,i);
		}
		theFloor.emplace_back(vecRow);
	}
	//start room init
	int currRoom = 0;
 	for(unsigned row=0;row<theFloor.size();++row) {
                for(unsigned col=0;col<theFloor[row].size();++col) {
                        if(theFloor[row][col].getOutput() == "." && theFloor[row][col].accountedFor() == false) {
				vector<cell*> newRoom;
				theRooms.emplace_back(newRoom);
				cascade(row,col,currRoom);
				++currRoom;
			}
                }
        }
	return(true);
}

bool floor::initFloorFF(string sourceFile,int floorNum, shared_ptr<person> thePlayer) {
	ifstream source {sourceFile}; //check to make sure file is good first
        int j=0;
	int numRows=25; 
        
	int i=1;
	//discard previous floors
	for(string discard;i<floorNum;++i) {
		for(int k=0;k<numRows;++k) {
			getline(source,discard);
		}
	}
	//theFloor init
        cout << "starting floor init" << endl;
        for(string row;j<numRows;++j) {
		getline(source,row);
                int len = row.length();
                vector<cell> vecRow(len,cell{});
                for(int i=0;i<len;++i) {
                        vecRow[i].initCell(row[i],j,i);
			//set cell to be floor tile if it was occupant, and init occupant;
			
			if(row[i] == '@') {
				vecRow[i].setType('.');
				vecRow[i].setOccupant(thePlayer);
				thePlayer->setPosn(j,i);
			} else if(row[i] == '\\') {
				vecRow[i].setType('\\');
			} else if('0' <= row[i] && row[i] <= '5') { //using char comparison
				vecRow[i].setType('.');
				int potionNum = row[i] - '0'; // converting char to int
				shared_ptr<potion> newPotion;
     				if(potionNum == 0) {
                			newPotion = make_shared<RH>();
        			} else if(potionNum == 1) {
                			newPotion = make_shared<BA>();
        			} else if(potionNum == 2) {
                			newPotion = make_shared<BD>();
        			} else if(potionNum == 3) {
                			newPotion = make_shared<PH>();
        			} else if(potionNum == 4) {
                			newPotion = make_shared<WA>();
        			} else if(potionNum == 5) {
                			newPotion = make_shared<WD>();
        			}
				vecRow[i].setItem(newPotion);
				newPotion->setPosn(j,i);		
			} else if('6' <= row[i] && row[i] <= '9'){
				vecRow[i].setType('.');
				int treasureNum = row[i] - '0';
				shared_ptr<treasure> newTreasure;
				if(treasureNum == 6) {
					newTreasure = make_shared<basic>(1);
				} else if(treasureNum == 7) {
					newTreasure = make_shared<basic>(2);
				} else if(treasureNum == 8) {
					newTreasure = make_shared<basic>(4);
				} else if(treasureNum == 9) {
					newTreasure = make_shared<dragonHoard>();
				}
				vecRow[i].setItem(newTreasure);
				newTreasure->setPosn(j,i);
			} else if(row[i] == 'D' || row[i] == 'H' || row[i] == 'W' || row[i] == 'L' || row[i] == 'E' || row[i] == 'O' || row[i] == 'M') {
				vecRow[i].setType('.');
				shared_ptr<person> newEnemy = make_shared<basicPerson>("enemy");
        			if(row[i] == 'H') {
                			newEnemy = make_shared<human>(newEnemy);
        			} else if(row[i] == 'W') {
                			newEnemy = make_shared<dwarf>(newEnemy);
        			} else if(row[i] == 'L') {
                			newEnemy = make_shared<halfling>(newEnemy);
        			} else if(row[i] == 'E') {
                			newEnemy = make_shared<elf>(newEnemy);
        			} else if(row[i] == 'O') {
                			newEnemy = make_shared<orc>(newEnemy);
        			} else if(row[i] == 'M') {
                			newEnemy = make_shared<merchant>(newEnemy);
        			} else if(row[i] == 'D') {
					newEnemy = make_shared<dragon>(newEnemy);
				}
				vecRow[i].setOccupant(newEnemy);
                                newEnemy->setPosn(j,i);
                	}
		}
                theFloor.emplace_back(vecRow);
        }
        //start room init

        int currRoom = 0;
        for(unsigned row=0;row<theFloor.size();++row) {
                for(unsigned col=0;col<theFloor[row].size();++col) {
                        if(theFloor[row][col].getOutput() == "." && theFloor[row][col].accountedFor() == false) {
                                vector<cell*> newRoom;
                                theRooms.emplace_back(newRoom);
                                cascade(row,col,currRoom);
                                ++currRoom;
                        }
                }
        }

	linkDragons();
        return(true);
}


void floor::linkDragons() {
        for(unsigned row=0;row<theFloor.size();++row) {
                for(unsigned col=0;col<theFloor[row].size();++col) {
                        auto hoard = theFloor[row][col].getItem();
                        if(hoard != nullptr && hoard->getSubType() == "dragonHoard") {
                        	if(theFloor[row-1][col].getOccupant() != nullptr && theFloor[row-1][col].getOccupant()->getRace() == "d") {
					theFloor[row-1][col].getOccupant()->setHoard(hoard);
                                        hoard->setGuard(theFloor[row-1][col].getOccupant());

        			} else if(theFloor[row-1][col+1].getOccupant() != nullptr && theFloor[row-1][col+1].getOccupant()->getRace() == "d") {
                			theFloor[row-1][col+1].getOccupant()->setHoard(hoard);
                                        hoard->setGuard(theFloor[row-1][col+1].getOccupant());

        			} else if(theFloor[row][col+1].getOccupant() != nullptr && theFloor[row][col+1].getOccupant()->getRace() == "d") {
                			theFloor[row][col+1].getOccupant()->setHoard(hoard);
                                        hoard->setGuard(theFloor[row][col+1].getOccupant());

        			} else if(theFloor[row+1][col+1].getOccupant() != nullptr && theFloor[row+1][col+1].getOccupant()->getRace() == "d") {
                			theFloor[row+1][col+1].getOccupant()->setHoard(hoard);
                                        hoard->setGuard(theFloor[row+1][col+1].getOccupant());

        			} else if(theFloor[row+1][col].getOccupant() != nullptr && theFloor[row+1][col].getOccupant()->getRace() == "d") {
                			theFloor[row+1][col].getOccupant()->setHoard(hoard);
                                        hoard->setGuard(theFloor[row+1][col].getOccupant());

        			} else if(theFloor[row+1][col-1].getOccupant() != nullptr && theFloor[row+1][col-1].getOccupant()->getRace() == "d") {
                			theFloor[row+1][col-1].getOccupant()->setHoard(hoard);
                                        hoard->setGuard(theFloor[row+1][col-1].getOccupant());

        			} else if(theFloor[row][col-1].getOccupant() != nullptr && theFloor[row][col-1].getOccupant()->getRace() == "d") {
                			theFloor[row][col-1].getOccupant()->setHoard(hoard);
                                        hoard->setGuard(theFloor[row][col-1].getOccupant());

        			} else if(theFloor[row-1][col-1].getOccupant() != nullptr && theFloor[row-1][col-1].getOccupant()->getRace() == "d") {
					theFloor[row-1][col-1].getOccupant()->setHoard(hoard);
					hoard->setGuard(theFloor[row-1][col-1].getOccupant());
        			} else {
					shared_ptr<person> newDragon = make_shared<dragon>(make_shared<basicPerson>("enemy"));
					newDragon->setHoard(hoard); 
					hoard->setGuard(newDragon);
					int dragonRow = row + ((rand() % 3) - 1);
					int dragonCol = col + ((rand() % 3) - 1);
					newDragon->setPosn(dragonRow,dragonCol);
					while(!theFloor[dragonRow][dragonCol].setOccupant(newDragon)) {
						dragonRow = row + ((rand() % 3) - 1);
                                        	dragonCol = col + ((rand() % 3) - 1);
						newDragon->setPosn(dragonRow,dragonCol);
					}
				}			
                        }
               }
        
	}
}

bool floor::isStairs(int row, int col) {
	if(theFloor[row][col].getOutput() == "\\") {
		return true;
	}
	return false;
}

string floor::getOutput() {
	ostringstream output;
	for( auto vCell:theFloor) {
		for( auto cell:vCell) {
			output << cell.getOutput();
		}
		output << endl;
	}
	return(output.str());
}

int floor::numRooms() {
	return theRooms.size();
}

int floor::roomSize(int roomNum) {
	return theRooms[roomNum].size();
}

void floor::placeStair(int roomNum,int cell) {
	theRooms[roomNum][cell]->makeStair();
}

bool floor::placePerson(shared_ptr<person> thePerson, int roomNum,int cell) {
        thePerson->setPosn(theRooms[roomNum][cell]->getRow(),theRooms[roomNum][cell]->getCol());
        return theRooms[roomNum][cell]->setOccupant(thePerson);
}

bool floor::placeItem(shared_ptr<item> theItem,int roomNum, int cell) {
        theItem->setPosn(theRooms[roomNum][cell]->getRow(),theRooms[roomNum][cell]->getCol());
        return theRooms[roomNum][cell]->setItem(theItem);
}

void floor::killOccupant(int row, int col) {
	shared_ptr<person> occupant = theFloor[row][col].getOccupant();
	string race = occupant->getRace();
	if(race == "h" || race == "m") {
		theFloor[row][col].setItem(make_shared<basic>(4));
	}
	theFloor[row][col].setOccupant(nullptr);
}

void floor::killItem(int row, int col) {
        theFloor[row][col].setItem(nullptr);
}

bool floor::movePerson(shared_ptr<person> thePerson,int rowChange, int colChange) {
	int newRow = thePerson->getRow() + rowChange;
        int newCol = thePerson->getCol() + colChange;
	string type = theFloor[newRow][newCol].getType();
	if(((type == ".") || ((type == "+" || type == "#" || type == "/") && thePerson->getType() == "player")) 
	&& theFloor[newRow][newCol].getOccupant() == nullptr) {
		theFloor[thePerson->getRow()][thePerson->getCol()].setOccupant(nullptr);
                thePerson->setPosn(newRow,newCol);
                return theFloor[newRow][newCol].setOccupant(thePerson);
	} else {
		return false;
	}
}

bool floor::nextToPlayer(shared_ptr<person> thePlayer,int row,int col) {
	int playerRow = thePlayer->getRow();
	int playerCol = thePlayer->getCol();
	int enemyRow = row;
	int enemyCol = col;
	int rowDiff = playerRow-enemyRow;
	int colDiff = playerCol-enemyCol;
	if(-2 < rowDiff && rowDiff < 2 && -2 < colDiff && colDiff < 2) {
		return true;
	}
	return false;
}

string floor::actEnemies(shared_ptr<person> thePlayer) {
	string turnOutput = "";
	for(unsigned roomNum=0;roomNum<theFloor.size();++roomNum) {
                for(unsigned cell=0;cell<theFloor[roomNum].size();++cell) {
			shared_ptr<person> occupant = theFloor[roomNum][cell].getOccupant();
			//add 5hp to troll
			if(occupant != nullptr && occupant->getType() == "player" && occupant->getRace() =="t") {
				shared_ptr<stats> playerStats = make_shared<stats>();
				*playerStats = occupant->getRawStats();
				if((playerStats->HP + 5) >= playerStats->MAXHP) {
					playerStats->HP = playerStats->MAXHP;
				} else {
					playerStats->HP += 5;
				}
				occupant->setStats(playerStats);
			}
			

			if((occupant != nullptr && nextToPlayer(thePlayer,occupant->getRow(),occupant->getCol()) && occupant->getType() == "enemy")
			|| (occupant != nullptr && occupant->getType() == "enemy" && occupant->getRace() == "d" 
			&& nextToPlayer(thePlayer,occupant->getHoard()->getRow(),occupant->getHoard()->getCol()))) {
				thePlayer->getAttackedBy(occupant);
				occupant->setTookTurn(true);
			} else if(occupant != nullptr && !occupant->getTookTurn() && occupant->getType() == "enemy" && occupant->getRace() != "d") {
		         	int rowChange = (rand() % 3) -1;
				int colChange = (rand() % 3) -1;
				while(!movePerson(theFloor[roomNum][cell].getOccupant(),rowChange,colChange)) {
	                              	rowChange = (rand() % 3) -1;
                               		colChange = (rand() % 3) -1;
				}
				occupant->setTookTurn(true);
                        }
                }
        }
	return turnOutput;
}

string floor::endTurn() {
       for(unsigned roomNum=0;roomNum<theFloor.size();++roomNum) {
                for(unsigned cell=0;cell<theFloor[roomNum].size();++cell) {
                        auto occupant = theFloor[roomNum][cell].getOccupant();
                        if(occupant != nullptr && occupant->getType() == "enemy") {
                                occupant->setTookTurn(false);
                        }
                }
        }
	return "";
}
