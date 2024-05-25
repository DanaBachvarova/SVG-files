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

    Line line = Line(Point{0, 0}, Point{3,4}, "brown");

    std::cout << line.toSVG() << std::endl;
}