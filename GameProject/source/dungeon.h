#pragma once


#include "main.h"
#include "classes.h"
#include <fstream>
#include "init.h"




class Room
{
public:
    enum tileType : char;
	Room(std::string filepath, bool encounter);
	void roomLoop(Player& player);
	void printRoom(int xpos, int ypos);
    Room(std::vector<std::string>& layout);
    char enemyCount;
    char lootCount;
private:
    //old system, now remade
    //return to this in case it wont work
	//std::array<tileType, 8 * 8> map;
    std::array<std::string, 8> map;
};



void dungeonLoop(int roomnumber);
