#include "textParser.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>

TextParser &TextParser::getInstance()
{
    static TextParser instance;
    return instance;
}

TextParser::TextParser() {}

std::vector<std::string> TextParser::splitInput(const std::string &userInput)
{
    std::istringstream iss(userInput);
    std::vector<std::string> substrings;
    std::string token;

    while (iss >> token){
        substrings.push_back(token);
    }

    return substrings;
}

