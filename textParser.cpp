#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include "textParser.hpp"

std::vector<std::string> splitInput(const std::string &userInput)
{
    std::istringstream iss(userInput);
    std::vector<std::string> substrings;
    std::string token;

    while (iss >> token){
        substrings.push_back(token);
    }

    return substrings;
}