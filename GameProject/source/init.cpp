#include "init.h"




std::vector<std::string> FileToStringVector(const std::string filepath)
{
    std::vector<std::string> oVector;
    std::string line;
    std::ifstream inFile(filepath);
    while (std::getline(inFile, line))
    {
        oVector.push_back(line);
    }
    return oVector;
}

std::vector<std::string> splitString(const std::string& splitted,
    char delimeter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(splitted);
    while (std::getline(tokenStream, token, delimeter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

//commented out for tests sake 


//void playerInit()
//{
//    Player* player = new Player("Miskunn", 100, -10, 50, 1.0);
//    Item SwordOfTruth("Sword of Truth", -99, (Item::itemType)0);
//    player->equip(SwordOfTruth);
//}


//Enemy enemyInit(std::string& enemyStats)
//{
//    std::vector<std::string> stats = splitString(enemyStats, ';');
//    return Enemy(stats[0], std::stoi(stats[1]), std::stoi(stats[2]), std::stof(stats[3]), std::stoi(stats[4]));
//}
