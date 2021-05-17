#pragma once


#include "main.h"
#include "classes.h"
#include <fstream>
#include "init.h"




class Room
{
public:
    enum tileType : char;
    Room(std::string filepath);
	void roomLoop(Player& player);
	void printRoom(int xpos, int ypos);
    Room(std::vector<std::string>& layout);
    char enemyCount = 0;
    char lootCount = 0;

private:
    std::array<std::string, 8> map;
};


//dungeons are fixed 5  member arrays of rooms
class Dungeon
{
public:
    Dungeon(int dSize);
    void DungeonLoop(Player&);
private:
    //for some reason it doesn't work with arrays
    //it says that the constructor has been deleted
    //look into it and change into array ASAP
    std::vector<Room> dungeonMap;
};



//void dungeonLoop(int roomnumber);
