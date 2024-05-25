#include "figuresManager.hpp"
#include "figure.hpp"
#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"

FiguresManager &FiguresManager::getInstance()
{
    static FiguresManager instance;
    return instance;
}

FiguresManager::FiguresManager() {}

// static Figure* FiguresManager::createNewFigure(std::string input)
// {

// }