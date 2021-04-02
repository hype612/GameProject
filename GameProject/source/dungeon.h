#pragma once


#include "header.h"
#include "classes.h"
#include <fstream>
#include "init.h"




class Room
{
public:
    enum tileType : char;
	Room(std::string filepath, bool encounter);
	void roomLoop(Player& player);
	void printRoom();
    Room(std::vector<std::string>& layout);
private:
	std::array<tileType, 8* 8> map;
};



void dungeonLoop(int roomnumber);
