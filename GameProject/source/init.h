#include "main.h"
#include "classes.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>


std::vector<std::string> FileToStringVector(std::string filepath);
std::vector<std::string> splitString(const std::string& splitted, char delimeter);
int randomNumber(int maxNumber);
void playerInit();
