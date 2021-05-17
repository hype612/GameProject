#include "main.h"
#include "classes.h"
#include "dungeon.h"
#include "init.h"


void gameLoop()
{
	Dungeon mainDungeon(5);
	Player player("Miskunn", 100, 50, 1.0f, 1);
    	Item SoSJ("Spear of Shojin", 25, (Item::itemType)0);
	player.equip(SoSJ);
	
	//start of dungeon
	asdasd.DungeonLoop(player);
	
}

int main()
{
    gameLoop();
    std::cin.get();
}
