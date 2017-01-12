#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "floor.h"
#include "game.h"


using namespace std;

string move(game *theGame, int rowChange, int colChange) {
	return theGame->movePlayer(rowChange,colChange);
}

void printGame(game *theGame, string action) {
        stats playerStats = theGame->getPlayer()->getStats();
        cout << theGame->getOutput() << endl;
        cout << "Race: " << theGame->getPlayer()->getRace();
        cout << " Gold: " << playerStats.GOLD;
        cout << "                                    Floor: " << theGame->getFloorNum() << endl;
        cout << "HP: " << playerStats.HP << endl;
        cout << "ATK: " << playerStats.ATK << endl;
        cout << "DEF: " << playerStats.DEF << endl;
        cout << "Action: " << action << endl;
}

string useOrAttack(game *theGame, int rowChange, int colChange,string command) {
	string outPut = "";
	if(command == "a") {
		outPut += "Player Attacked ";
		outPut += theGame->playerAttack(rowChange,colChange);
		return outPut;
	} else {
		outPut += "player used a ";
		outPut += theGame->useItem(rowChange,colChange);
		return outPut;
	}
}

void newGame(game *theGame, string source,bool allFF) {
        cout << "PLEASE SELECT YOUR RACE: s,d,v,g,t." << endl;
        string race;
        cin >> race;
	theGame->spawnPlayer(race);
	theGame->startGame(source,allFF);
        if(allFF) {
		theGame->getPlayer();
	} else {
		int playerRoom = theGame->placePlayer(theGame->getPlayer());
		cout << "spawning stairs" << endl;
		theGame->spawnStairs(playerRoom);
		int numEnemies = 20;
		cout << "spawning enemies" << endl;
		theGame->spawnEnemies(numEnemies);
		int numPotions = 10;
		cout << "spawning Potions" << endl;
		theGame->spawnPotions(numPotions);
		int numTreasure = 10;
		theGame->spawnTreasure(numTreasure);
	}
}

void newFloor(game *theGame, string source, bool allFF) {
	auto thePlayer = theGame->getPlayer();
	int playerRoom = theGame->startNewFloor(source,thePlayer,allFF);
        if(!allFF) {
		theGame->spawnStairs(playerRoom);
        	int numEnemies = 20;
        	theGame->spawnEnemies(numEnemies);
		int numPotions = 10;
                cout << "spawning Potions" << endl;
                theGame->spawnPotions(numPotions);
                int numTreasure = 10;
                theGame->spawnTreasure(numTreasure);
	}
	thePlayer->clearTempPotions();
	ostringstream out;
	out << "Player has proceeded to floor " << theGame->getFloorNum() << endl;
        printGame(theGame,out.str());
	theGame->setNewFloor(false);
}

int main(int argc, char* argv[]) {
	int seed = 123456;	
	
	srand(seed);
	game theGame;
	string inFile;
	bool allFF = false;
	bool bonus = false;
	string prefix = "floor";
	string postfix = ".txt";
		

        if(argc == 2 || argc == 3) {
                allFF = true;
                inFile=argv[1];
		if(inFile == "bonus") {
			allFF = false;
			bonus = true;
			if(argc == 3) {
                                seed=stoi(argv[2]);
                                srand(seed);
                        }
			inFile = prefix + to_string(rand() % 12 + 1 ) + postfix;
		}
                newGame(&theGame,inFile,allFF);
        } else {
		inFile="stdFloor.txt";
		newGame(&theGame,inFile,allFF);
        }
	cout << "game started" << endl;
	auto thePlayer = theGame.getPlayer();
	stats playerStats = thePlayer->getStats();
	bool enemyMovement = true;
	
	printGame(&theGame,"Player spawned. ");
	
	string command;
	while(cin >> command) {
		ostringstream turnOutput;
//		cout << theGame.getOutput() << endl;
		if (command == "u" || command == "a") {
			string firstCommand = command;
			cin >> command;
			if (command == "no") {
				turnOutput << useOrAttack(&theGame,-1,0,firstCommand);
			} else if(command == "ne") {
	                        turnOutput << useOrAttack(&theGame,-1,1,firstCommand);	
	                } else if(command == "ea") {
        		        turnOutput << useOrAttack(&theGame,0,1,firstCommand);
               		} else if(command == "se") {
                       		turnOutput << useOrAttack(&theGame,1,1,firstCommand);
	       	        } else if(command == "so") {
       	        	        turnOutput << useOrAttack(&theGame,1,0,firstCommand);
	                } else if(command == "sw") {
        	              	turnOutput << useOrAttack(&theGame,1,-1,firstCommand);
               	 	} else if(command == "we") {
                       		turnOutput << useOrAttack(&theGame,0,-1,firstCommand);
               		} else if(command == "nw") {
                       		turnOutput << useOrAttack(&theGame,-1,-1,firstCommand);
               		}		


		} else if(command == "no") {
			turnOutput << "Player moved " << command << ". " << move(&theGame,-1,0);
		} else if(command == "ne") {
			turnOutput << "Player moved " << command << ". "  << move(&theGame,-1,1);
		} else if(command == "ea") {
        	        turnOutput << "Player moved " << command << ". "  << move(&theGame,0,1);
      	  	} else if(command == "se") {
                	turnOutput << "Player moved " << command << ". "  << move(&theGame,1,1);
        	} else if(command == "so") {
                	turnOutput << "Player moved " << command << ". "  << move(&theGame,1,0);
        	} else if(command == "sw") {
                	turnOutput << "Player moved " << command << ". "  << move(&theGame,1,-1);
        	} else if(command == "we") {
                	turnOutput << "Player moved " << command << ". "  << move(&theGame,0,-1);
        	} else if(command == "nw") {
                	turnOutput << "Player moved " << command << ". "  << move(&theGame,-1,-1);
        	} else if(command == "f") {
                        enemyMovement = !enemyMovement;
                } else if(command == "q") {
			cout << "YOU QUIT....LOSER" << endl;
			break;
		} else if(command == "r") {
			cout << "RESTARTING" << endl;
			thePlayer = nullptr;
		        if(argc == 2 || argc == 3) {
                		allFF = true;
                		inFile=argv[1];
               	 		if(inFile == "bonus") {
                        		allFF = false;
                        		bonus = true;
                        		if(argc == 3) {
                                		seed=stoi(argv[2]);
                                		srand(seed);
                        		}
                        	inFile = prefix + to_string(rand() % 12 + 1 ) + postfix;
                		}
                	newGame(&theGame,inFile,allFF);
        		} else {
                		inFile="stdFloor.txt";
                		newGame(&theGame,inFile,allFF);
        		}
        		cout << "NEW game started" << endl;
        		thePlayer = theGame.getPlayer();
        		playerStats = thePlayer->getStats();
        		enemyMovement = true;

        		printGame(&theGame,"Player spawned. ");
		} else {
			command = "f";
			turnOutput << "invalid command";
		}


		if(!enemyMovement || command == "f") {
                        //do nothing 
                }else {
                        theGame.toggleTurn(true);
                        theGame.toggleTurn(false);
                }

		//used to see if player lost HP after the enemies took their turn.
		playerStats = thePlayer->getStats();
		int origonalHp = playerStats.HP;

                if(theGame.isWon(6)) {
                        cout << "YOU WON.....LOSER" << endl;
                        if(thePlayer->getRace() == "s") {
                                playerStats.GOLD *= 1.5;
                        }
                        cout << "SCORE: " << playerStats.GOLD << endl;
                        break;
                } else if(theGame.isNewFloor()) {
                        if(bonus) {
                                inFile = prefix + to_string(rand() % 12 + 1 ) + postfix;
                        }
                        newFloor(&theGame,inFile,allFF);
                }		

		//start Outputting for turn here
		playerStats = thePlayer->getStats();
		if(playerStats.HP == 0) {
			cout << "GAME OVER LOSER" << endl;
			break;
		} else {
			if(origonalHp > playerStats.HP) {
				turnOutput << "The player lost " << (origonalHp - playerStats.HP) <<  " HP.";
			}
			printGame(&theGame,turnOutput.str());
		}	
	}	
}

