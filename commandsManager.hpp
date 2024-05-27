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

class CommandsManager
{
public:
    static CommandsManager& getInstance();
    void getCommand(std::string&);
    void parseAndExecute();
    void run();

private:
    CommandsManager();
    CommandsManager(CommandsManager const&) = delete;
    void operator=(CommandsManager const&) = delete;

    std::vector<std::string> command;
    bool programTerminated;
    bool fileLoaded;
};

