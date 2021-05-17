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



void playerInit()
{
    Player* player = new Player("Miskunn", 100, -10, 50, 1.0);
    Item SwordOfTruth("Sword of Truth", -99, (Item::itemType)0);
    player->equip(SwordOfTruth);
}


int randomNumber(int maxNumber)
{
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()
                ).count() +
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
                ).count() );

    std::mt19937 gen(seed);

    for( unsigned long j = 0; j < 10; ++j )
    {
        std::mt19937::result_type n;
        while( ( n = gen() ) > std::mt19937::max() -
                                    ( std::mt19937::max() - 5 )%6 )
        { /* bad value retrieved so get next one */ }

        if(j==9)
        {
            return n % maxNumber;
        }
    }
    return 0;
}


//commented out for tests sake 
//Enemy enemyInit(std::string& enemyStats)
//{
//    std::vector<std::string> stats = splitString(enemyStats, ';');
//    return Enemy(stats[0], std::stoi(stats[1]), std::stoi(stats[2]), std::stof(stats[3]), std::stoi(stats[4]));
//}
