#include "fileManager.hpp"
#include "figuresManager.hpp"
#include "SVGParser.hpp"
#include "figure.hpp"
#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include "commandsManager.hpp"

CommandsManager &CommandsManager::getInstance()
{
    static CommandsManager instance;
    return instance;
}

CommandsManager::CommandsManager() {}

void CommandsManager::getCommand(std::string &input)
{
    std::istringstream iss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, ' '))
    {
        if (!token.empty())
        {
            tokens.push_back(token);
        }
    }

    if (tokens[0] == "open"){

    } else if (tokens[0] == "close"){

    } else if (tokens[0] == "save"){

    } else if (tokens[0] == "save as"){

    } else if (tokens[0] == "help"){

    } else if (tokens[0] == "print"){

    } else if (tokens[0] == "create"){

    } else if (tokens[0] == "erase"){

    } else if (tokens[0] == "translate"){
        
    } else if (tokens[0] == "within"){

    } else if (tokens[0] == "exit"){

    } else {
        throw std::invalid_argument("Invalid command: " + tokens[0]);
    }
}