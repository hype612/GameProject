#include "header.h"
#include "classes.h"
#include "dungeon.h"
#include "events.h"
#include <fstream>

//
//
//dungeon namespace
//
//

namespace Dungeon{

		
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
            isEncounterRoom = encounter;
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
                             std::cout << map[i + j * 8] << " "
 ;
                     }
                 }
             }
             std::cout << "\n";
         }

        //make it throw a quest at the end
        //for now its void
        void Room::roomLoop(Player& player)
        {
            printRoom();
            if(isEncounterRoom)
            {
                Entity enemy("evilCreature", 50, 50, 1.0f, 10);
                WorldEvent::Fight(player, enemy); 
            }
            else
            {
                std::cout << "there's some loot in this room.\nDo you want to take it?(Y/N) ";
                char action;
			    std::cin >> action;
                if(action == 'y')
                {
                    std::cout << "Taking loot...\n";
                    /*
                    for_each(Consumable loot in ConsumableList)
                    {
                       player.addConsumable();
                    }
                    */
                }
                std::cout << "leaving the room..\n";
            }
        }

        void dungeonLoop(Player& player)
        {
            //now 2 const rooms
            //there'll be added support for flexible 
            //sized dungeons
            std::array<const char*, 2> paths{"../resources/room.txt", "../resources/bossroom.txt"};
            std::array<bool, 2> ncount{false, true};
            
            for(int roomCounter = 0; roomCounter < paths.size(); roomCounter++)
            {
                Dungeon::Room tRoom(paths[roomCounter], ncount[roomCounter]);
                tRoom.roomLoop(player);
            }
                 

    }
}

