#include <iostream>
#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"
#include "fileManager.hpp"
#include <cstring>

int main()
{
    FileManager& fileManager = FileManager::getInstance();
    std::string argument;

    if (!fileManager.openFile(argument)){
        std::cout<<"Failed to open the file."<<std::endl;
    }
}