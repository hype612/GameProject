#pragma once


#include "header.h"
#include "classes.h"
#include <fstream>

namespace Dungeon {


	
	class Room
	{
	public:
	    enum tileType : char;
        bool isEncounterRoom;
		Room(std::string filepath, bool encounter);
		void roomLoop(Player& player);
		void printRoom();

	private:
		std::array<tileType, 8* 8> map;
	};
    
    
    
    void dungeonLoop(int roomnumber);
    
    /*
	template<int x, int y>
	class Room
	{
	public:

		enum tileType : char
		{
			floor = 0, wall, chest, enemy, prop
		};

		Room(std::string filepath)
		{
			std::string line;
			std::ifstream roomFile(filepath);

			for (size_t i = 0; i < x; i++)
			{
				std::getline(roomFile, line);
				for (size_t j = 0; j < y; j++)
				{
					map[i + j * y] = (tileType)line[j];
				}
			}
		}


	private:
		std::array<tileType, x* y> map;
	};
	*/
}

