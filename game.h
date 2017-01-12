#ifndef __GAME_H__
#define __GAME_H__
#include <vector>
#include <string>
#include <memory>
#include "floor.h"
#include "person.h"


class game {
	std::shared_ptr<floor> gameFloor;
	std::shared_ptr<person> thePlayer;
	int floorNum;
	bool newFloor;
 public:
	bool startGame(std::string,bool);
	int startNewFloor(std::string,std::shared_ptr<person>,bool);
	std::string getOutput();
	bool isWon(int);
	int getFloorNum();
	bool isNewFloor();
	void getNewFloor();
	void setNewFloor(bool);
	void spawnPlayer(std::string);
	int placePlayer(std::shared_ptr<person>);
	void spawnStairs(int);
	void spawnEnemies(int);
	void spawnPotions(int);
	void spawnTreasure(int);
	std::string toggleTurn(bool);
	std::string playerAttack(int,int);
	std::string useItem(int,int);
	std::string movePlayer(int,int);
	std::shared_ptr<person> getPlayer();
};

#endif
