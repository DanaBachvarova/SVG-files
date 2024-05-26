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

class CommandsManager
{
public:
    static CommandsManager& getInstance();
    void getCommand(std::string&);

private:
    CommandsManager();
    CommandsManager(CommandsManager const&) = delete;
    CommandsManager(CommandsManager const&) = delete;
};

