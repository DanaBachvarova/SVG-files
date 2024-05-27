#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"
#include "fileManager.hpp"
#include "commandsManager.hpp"
#include <iostream>
#include <cstring>

int main()
{
    CommandsManager::getInstance().run();

    return 0;
}