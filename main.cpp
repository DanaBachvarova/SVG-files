#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"
#include "fileManager.hpp"
#include <iostream>
#include <cstring>

int main()
{
    // FileManager &fileManager = FileManager::getInstance();
    // std::string argument = "test.svg";

    // if (!fileManager.openFile(argument))
    // {
    //     std::cout << "Failed to open the file." << std::endl;
    // }

    // fileManager.erase(1);
    // fileManager.saveFile();
    // fileManager.closeFile();

    std::string str = "horizontal=10";
    str = str.substr(11);
    std::cout<<str<<std::endl;
}