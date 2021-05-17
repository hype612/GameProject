#include "main.h"
#include "classes.h"
#include "dungeon.h"
#include "events.h"
#include "resources.h"
#include <fstream>
#include <cstdlib>
//
//
//namespace not needed, since there are 
//no blank functions floating in the file
//


	
enum Room::tileType : char
{
	floor = 0, wall, chest, enemy, door
};





Room::Room(std::string filepath)
{
    std::vector<std::string> layoutVector = FileToStringVector(filepath);
    for(size_t i = 0; i < layoutVector.size(); i++)
    {
        map[i] = layoutVector[i];
        for(size_t j = 0; j < map[i].size(); j++)
        {
            switch(map[i][j])
            {
                case '2':
                    lootCount++;
                    break;
                case '3':
                    enemyCount++;
                    break;
                default:
                    break;
            }
        }
    }
}


Room::Room(std::vector<std::string>& layout)
{
    for(size_t i = 0; i < layout.size(); i++)
    {
        map[i] = layout[i];
        for(size_t j = 0; j < map[i].size(); j++)
        {
            switch(map[i][j])
            {
                case '2':
                    lootCount++;
                    break;
                case '3':
                    enemyCount++;
                    break;
                default:
                    break;
            }
        }
    }
}

void Room::printRoom(int xpos, int ypos)
 {
     //map[i + j * v8]
     std::cout << " 1 = wall, 2 = chest, 3 = enemy 4 = door\n";
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
    std::cout << "roomloop started" << std::endl;
    std::vector<Enemy> hostiles;
    std::vector<Item> loot;
    player.roomPos[0] = 1;
    player.roomPos[1] = 1;
    std::cout << "declared basic vectors and set the players default pos\n";
    if(enemyCount > 0)
    {
        for(size_t i = 0; i < enemyCount; i++)
        {
            hostiles.push_back(Enemy(Resources::enemyList[randomNumber(Resources::enemyList.size())]));
            std::cout << "currently generated enemy: "<< hostiles[i].entityName << std::endl;
        }
    }
    std::cout << "filled hostiles vector\n";
    if(lootCount > 0)
    {
        for(size_t i = 0; i < lootCount; i++)
        {
            loot.push_back(Item(Resources::itemList[randomNumber(Resources::itemList.size())]));
            std::cout << "currently generated item: "<< loot[i].itemName << std::endl;
        }
    }
    std::cout << "filled loot vector\n";
    char moveDirection;
    std::array<int, 2> preUpdatePos {0, 0};
    do
    {
    std::cout << "Player's current stats: \n" << 
                "weapon's dmg: " << player.equipment[0]->dmg <<
                "\nweapon's name: " << player.equipment[0]->itemName << "\n";
        std::cout << "itemcount: " << loot.size() << "\n";
        std::cout << "enemycount: " << hostiles.size() << "\n";


        std::cout << "Your current position: "<< player.roomPos[0] << ":" << player.roomPos[1] << std::endl;


        printRoom(player.roomPos[0], player.roomPos[1]);
        std::cin >> moveDirection;
        player.dMove(moveDirection, preUpdatePos);
        int vIndx;
        switch(map[player.roomPos[0]][player.roomPos[1]])
        {
            case '1':
                player.roomPos[0] = preUpdatePos[0];
                player.roomPos[1] = preUpdatePos[1];
                break;    
            case '2':
                vIndx = randomNumber(loot.size());
                //if(player.equip(loot[vIndx]) == true)
                //{
                    player.equip(loot[vIndx]);
                    map[player.roomPos[0]][player.roomPos[1]] = '0';
                    loot.erase(loot.begin() + vIndx);
                //}
                break;
            case '3':
                vIndx = randomNumber(hostiles.size());
                if(WorldEvent::Fight(player, hostiles[vIndx]))
                {
                    map[player.roomPos[0]][player.roomPos[1]] = '0';
                    hostiles.erase(hostiles.begin() + vIndx);
                }
                else
                {
                    player.roomPos[0] = 1;
                    player.roomPos[1] = 1;
                }
                break;
            case '4':
                return;
            default:
                break;
        }
        system("clear");
    } while(player.roomPos[0] != 8 && player.roomPos[1] != 8);
}




//
//
//Dungeon
//
Dungeon::Dungeon(int dSize)
{
    //dungeonMap.reserve(5);
    for(size_t i = 0; i < dSize; i++)
    {
        dungeonMap.push_back(Room(Resources::roomList[randomNumber(Resources::roomList.size())]));
        dungeonMap[i].printRoom(1, 1);
        std::cout << "room " << i << " printed" << std::endl;
    }

}

void Dungeon::DungeonLoop(Player& passedPlayer)
{
    for(Room i : dungeonMap)
    {
        i.roomLoop(passedPlayer);
    }
}
