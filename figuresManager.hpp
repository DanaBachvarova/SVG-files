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
    void print() const;
    Figure* create(std::string&);

private:
    FiguresManager();
    FiguresManager(FiguresManager const&) = delete;
    void operator=(FiguresManager const&) = delete;
};