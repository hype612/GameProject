#include "init.h"
#include "header.h"


std::vector<std::string> splitString(const std::string& splitted,
 char delimeter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(splitted);
    while(std::getline(tokenStream, token, delimeter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

void playerInit()
{
	Player* player = new Player("Miskunn", 100, -10, 50, 1.0);
	Item SwordOfTruth("Sword of Truth", -99, (Item::itemType)0);
	player->equip(SwordOfTruth);
}


std::vector<std::string> fileInit(const std::string filepath)
{
    std::vector<std::string> oVector;
	std::string line;
	std::ifstream initFile(filepath);
	while(std::getline(initFile, line))
	{
        std::getline(initFile, line);
		oVector.push_back(line);
    }
    return oVector;
}
