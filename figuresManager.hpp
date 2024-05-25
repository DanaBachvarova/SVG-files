#pragma once

#include "figure.hpp"
#include "fileManager.hpp"
#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"

class FiguresManager
{
public:
    static FiguresManager& getInstance();
    static Figure* createNewFigure(std::string input);

private:
    FiguresManager();
    FiguresManager(FiguresManager const&) = delete;
    void operator=(FiguresManager const&) = delete;
};