#include "commandsManager.hpp"
#include "fileManager.hpp"
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

CommandsManager &CommandsManager::getInstance()
{
    static CommandsManager instance;
    return instance;
}

CommandsManager::CommandsManager() : fileLoaded(false), programTerminated(false), savedChanges(true) {}

void CommandsManager::getCommand(std::string &input)
{
    command.clear();
    std::istringstream iss(input);
    std::string token;

    while (std::getline(iss, token, ' '))
    {
        if (!token.empty())
        {
            command.push_back(token);
        }
    }
}

void CommandsManager::parseAndExecute()
{
    if (command.size() == 0)
    {
        return;
    }

    std::string mainCommand = command[0];

    if (mainCommand == "open")
    {
        if (fileLoaded)
        {
            std::cout << "File already loaded!\n";
            return;
        }

        if (command.size() == 1)
        {
            std::cout << "Expected more arguments!\n";
            return;
        }

        if (command.size() > 2)
        {
            std::cout << "Expected fewer arguments!\n";
            return;
        }

        std::string path = command[1];
        FileManager::getInstance().openFile(path);
        if (FileManager::getInstance().getFileLoaded())
        {
            fileLoaded = true;
        }
        return;
    }

    if (mainCommand == "close")
    {
        if (!fileLoaded)
        {
            std::cout << "No file loaded!\n";
            return;
        }

        if (command.size() > 1)
        {
            std::cout << "Expected fewer arguments!\n";
            return;
        }

        FileManager::getInstance().closeFile();
        if (!FileManager::getInstance().getFileLoaded())
        {
            fileLoaded = false;
        }

        return;
    }

    if (mainCommand == "save")
    {
        if (!fileLoaded)
        {
            std::cout << "No file loaded!\n";
            return;
        }

        if (command.size() > 1)
        {
            std::cout << "Expected fewer arguments!\n";
            return;
        }

        FileManager::getInstance().saveFile();
        return;
    }

    if (mainCommand == "saveas")
    {
        if (!fileLoaded)
        {
            std::cout << "No file loaded!\n";
            return;
        }

        if (command.size() == 1)
        {
            std::cout << "Expected more arguments!\n";
            return;
        }

        if (command.size() > 2)
        {
            std::cout << "Expected fewer arguments!\n";
            return;
        }

        std::string path = command[1];
        FileManager::getInstance().saveFileAs(path);
        return;
    }

    if (mainCommand == "help")
    {
        if (command.size() > 1)
        {
            std::cout << "Expected fewer arguments!\n";
            return;
        }

        FileManager::getInstance().displayHelp();
        return;
    }

    if (mainCommand == "exit")
    {
        if (command.size() > 1)
        {
            std::cout << "Expected fewer arguments!\n";
            return;
        }

        FileManager::getInstance().exit();
        programTerminated = true;
        return;
    }

    if (mainCommand == "print")
    {
        if (command.size() > 1)
        {
            std::cout << "Expected fewer arguments!\n";
            return;
        }

        if (FileManager::getInstance().getFiguresInFileSize() == 0)
        {
            std::cout << "No figures in current file!\n";
            return;
        }

        FileManager::getInstance().print();
        return;
    }

    if (mainCommand == "create")
    {
        if (command.size() == 1)
        {
            std::cout << "Expected more arguments!\n";
            return;
        }

        FileManager::getInstance().create(command);
        return;
    }

    if (mainCommand == "erase")
    {
        if (command.size() == 1)
        {
            std::cout << "Expected more arguments!\n";
            return;
        }

        if (command.size() > 2)
        {
            std::cout << "Expected fewer arguments!\n";
            return;
        }

        size_t index = std::stoi(command[1]);
        if (index > FileManager::getInstance().getFiguresInFileSize() || index <= 0)
        {
            std::cout << "There is no figure number " << index << "!\n";
            return;
        }
        FileManager::getInstance().erase(index);
        return;
    }

    if (mainCommand == "translate")
    {
        if (command.size() < 3)
        {
            std::cout << "Expected more arguments!\n";
            return;
        }

        if (command.size() > 4)
        {
            std::cout << "Expected fewer arguments!\n";
            return;
        }

        if (command.size() == 3)
        {
            command[1] = command[1].substr(9);
            command[2] = command[2].substr(11);

            double v = std::stod(command[1]);
            double h = std::stod(command[2]);

            FileManager::getInstance().translateAll(v, h);
            return;
        }

        size_t index = std::stoi(command[1]);

        if (index <= 0 || index > FileManager::getInstance().getFiguresInFileSize())
        {
            std::cout << "There is no figure number " << index << "!\n";
            return;
        }

        command[2] = command[2].substr(9);
        command[3] = command[3].substr(11);

        double v = std::stod(command[2]);
        double h = std::stod(command[3]);

        FileManager::getInstance().translateByIndex(index, v, h);
        return;
    }

    if (mainCommand == "within")
    {
        if (command.size() == 1)
        {
            std::cout << "Expected more arguments!\n";
            return;
        }

        std::string regionType = command[1];

        if (regionType == "rectangle")
        {
            if (command.size() != 6)
            {
                std::cout << "Invalid region!\n";
                return;
            }

            double vx = std::stod(command[2]);
            double vy = std::stod(command[3]);
            double width = std::stod(command[4]);
            double height = std::stod(command[5]);

            FileManager::getInstance().withinRect(vx, vy, width, height);
            return;
        }

        if (regionType == "circle")
        {
            if (command.size() != 5)
            {
                std::cout << "Invalid region!\n";
                return;
            }

            double cx = std::stod(command[2]);
            double cy = std::stod(command[3]);
            double r = std::stod(command[4]);

            FileManager::getInstance().withinCircle(cx, cy, r);
            return;
        }

        std::cout << "Unsupported region: " << regionType << std::endl;
        return;
    }

    std::cout << "Invalid command. See help for more information!\n";
    return;
}

void CommandsManager::run()
{
    while (!programTerminated)
    {
        std::string input;
        std::cout << "> ";

        std::getline(std::cin, input);

        getCommand(input);
        parseAndExecute();
    }

    return;
}
