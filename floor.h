#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <vector>
#include <string>
#include <memory>
#include "cell.h"
#include "person.h"
#include "player.h"


class floor {
	std::vector<std::vector<cell>> theFloor;
	std::vector<std::vector<cell*>> theRooms;
	bool nextToPlayer(std::shared_ptr<person>,int,int);
	bool cascade(int,int,int);
 public:
	std::shared_ptr<person> getOccupantAt(int,int);
	std::shared_ptr<person> findPlayer();
	std::string findPotions(std::shared_ptr<person>);
	std::shared_ptr<item> getItemAt(int,int);
	bool initFloor(std::string);
	bool initFloorFF(std::string,int,std::shared_ptr<person>);
	void linkDragons();
	bool isStairs(int,int);
	std::string getOutput();		
	int numRooms();
	int roomSize(int);
	void placeStair(int,int);
	bool placePerson(std::shared_ptr<person>,int,int);
	bool placeItem(std::shared_ptr<item>,int,int);
	bool movePerson(std::shared_ptr<person>,int,int);
	void killOccupant(int,int);
	void killItem(int,int);
	std::string actEnemies(std::shared_ptr<person>);
	std::string endTurn();
};

#endif
