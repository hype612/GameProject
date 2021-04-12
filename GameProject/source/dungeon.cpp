#include "main.h"
#include "classes.h"
#include "dungeon.h"
#include "events.h"
#include "resources.h"
#include <fstream>
//
//
//namespace not needed, since there are 
//no blank functions floating in the file
//


	
enum Room::tileType : char
{
	floor = 0, wall, chest, enemy, prop
};


//8 and 8 being the x and y of the room
//NOTE TO SELF: add flexible sized
//room class in the future


Room::Room(std::string filepath, bool encounter)
{
    //int x, y = 8;
	//std::string line;
	//std::ifstream roomFile(filepath);
	//for (size_t i = 0; i < 8; i++)
	//{
	//	std::getline(roomFile, line);
	//	for (size_t j = 0; j < 8; j++)
	//	{
	//		map[i + j * 8] = (tileType)line[j];
	//	}
	//}
}


Room::Room(std::vector<std::string>& layout)
{
    //int x, y = 8;
	//for (size_t i = 0; i < 8; i++)
	//{
	//	for (size_t j = 0; j < 8; j++)
	//	{
	//		map[i + j * 8] = (Room::tileType)tempArray[i + j * 8];
	//	}
	//}
    for(size_t i = 0; i < layout.size(); i++)
    {
        map[i] = layout[i];
    }
}

void Room::printRoom(int xpos, int ypos)
 {
     //map[i + j * v8]
     std::cout << " 1 = wall, 2 = chest, 3 = enemy\n";
     for (size_t i = 0; i < 8; i++)
     {
         for (size_t j = 0; j < 8; j++)
         {
             if (xpos == i && ypos == j)
             {
                 std::cout << " o ";
                 continue;
             }
             else
             {
                //if (j == (8 - 1))
                //    std::cout <<  map[i][j] << "\n";
                //else
                //{
                  if (map[i][j] == '0')
                     std::cout << "   ";
                 else
                     std::cout << " " << map[i][j] << " ";
                //}
             }
         }
         std::cout << "\n";
     }
     std::cout << "\n";
 }



void Room::roomLoop(Player& player)
{
    std::vector<Enemy> hostiles;
    std::vector<Item> loot;
    player.roomPos[0] = 1;
    player.roomPos[1] = 1;
    //for(size_t i = 0; i < enemyCount; i++)
    //{
        hostiles.push_back(Enemy(Resources::enemyList[0]));
    //}
    loot.push_back(Item(Resources::itemList[7]));
    char moveDirection;
    std::array<int, 2> preUpdatePos {0, 0};
    do
    {
        std::cout << loot[0].itemName << ":" << loot[0].dmg << ":" << loot[0].type << std::endl;
        std::cout << player.roomPos[0] << ":" << player.roomPos[1] << std::endl;
        printRoom(player.roomPos[0], player.roomPos[1]);
        std::cin >> moveDirection;
        player.dMove(moveDirection, preUpdatePos);
        switch(map[player.roomPos[0]][player.roomPos[1]])
        {
            case '1':
                player.roomPos[0] = preUpdatePos[0];
                player.roomPos[1] = preUpdatePos[1];
                break;    
            case '2':
                if(player.equip(loot[0]) == true)
                    map[player.roomPos[0]][player.roomPos[1]] = '0';
                break;
            case '3':
                if(WorldEvent::Fight(player, hostiles[0]))
                    map[player.roomPos[0]][player.roomPos[1]] = '0';
                else
                {
                    player.roomPos[0] = 1;
                    player.roomPos[1] = 1;
                }
                break;
            default:
                break;
        }
        system("clear");
    } while(player.roomPos[0] != 8 && player.roomPos[1] != 8);
}

//make it throw a quest at the end
//for now its h
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
}
