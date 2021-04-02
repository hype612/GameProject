#include "main.h"
#include "classes.h"
#include "dungeon.h"
#include "events.h"
#include <fstream>

//
//
//namespace not needed, since there are 
//no blank functions floating in the file
//


	
enum Room::tileType : char
{
	floor = -1, wall, chest, enemy, prop
};


//8 and 8 being the x and y of the room
//NOTE TO SELF: add flexible sized
//room class in the future


Room::Room(std::string filepath, bool encounter)
{
    //int x, y = 8;
	std::string line;
	std::ifstream roomFile(filepath);
	for (size_t i = 0; i < 8; i++)
	{
		std::getline(roomFile, line);
		for (size_t j = 0; j < 8; j++)
		{
			map[i + j * 8] = (tileType)line[j];
		}
	}
}


Room::Room(std::vector<std::string>& layout)
{
    //int x, y = 8;
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			map[i + j * 8] = (tileType)layout[i + j * 8];
		}
	}
}

void Room::printRoom()
 {
     std::cout << " 1 = wall, 2 = chest, 3 = enemy\n";
     for (size_t i = 0; i < 8; i++)
     {
         for (size_t j = 0; j < 8; j++)
         {
             if (j == (8 - 1))
                 std::cout << map[i + j * 8] << "\n";
             else
             {
                 if (map[i + j * 8] == '0')
                     std::cout << "  ";
                 else
                     std::cout << map[i + j * 8] << " ";
             }
         }
     }
     std::cout << "\n";
 }

//make it throw a quest at the end
//for now its void
void Room::roomLoop(Player& player)
{
        //==============================================
        //you should write a different function later on
        //when the player can actually move in the room
        //and alltogether in the dungeon.
        //==============================================
    //printRoom();
    //if(isEncounterRoom)
    //{
    //    Entity enemy("evilCreature", 50, 50, 1.0f, 10);
    //    WorldEvent::Fight(player, enemy); 
    //}
    //else
    //{
    //}
}

void dungeonLoop(Player& player)
{

    //=========================================================
    //Same goes for this. IDK why I even wrote this, 
    //I always planned that the player will be able to move
    //in the room, not just enter it.
    //__________________________________________
    //also, just straight up make it take the number of rooms as
    //an argument
    //=========================================================

    //now 2 const rooms
    //there'll be added support for flexible 
    //sized dungeons
    //std::array<const char*, 2> paths{"../resources/room.txt", "../resources/bossroom.txt"};
    //std::array<bool, 2> ncount{false, true};
    
    //for(int roomCounter = 0; roomCounter < paths.size(); roomCounter++)
    //{
    //    Dungeon::Room tRoom(paths[roomCounter], ncount[roomCounter]);
    //    tRoom.roomLoop(player);
    
}
        

}

