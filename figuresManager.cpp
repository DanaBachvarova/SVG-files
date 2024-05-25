#include "figuresManager.hpp"
#include "fileManager.hpp"
#include "figure.hpp"
#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

FiguresManager &FiguresManager::getInstance()
{
    static FiguresManager instance;
    return instance;
}

FiguresManager::FiguresManager() {}

void FiguresManager::print() const
{
    std::vector<Figure *> figures = FileManager::getInstance().getFiguresInFile();

    for (auto figure : figures)
    {
        figure->print();
    }
}

Figure *FiguresManager::create(std::string &input)
{
    std::istringstream iss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, ' '))
    {
        if (!token.empty())
        {
            tokens.push_back(token);
        }
    }

    if (tokens[1] == "rectangle")
    {
        double vx = std::stod(tokens[2]);
        double vy = std::stod(tokens[3]);
        double width = std::stod(tokens[4]);
        double height = std::stod(tokens[5]);

        return new Rect(Point{vx, vy}, width, height, tokens[6]);
    }
    else if (tokens[1] == "circle")
    {
        double cx = std::stod(tokens[2]);
        double cy = std::stod(tokens[3]);
        double radius = std::stod(tokens[4]);

        return new Circle(Point{cx, cy}, radius, tokens[5]);
    }
    else if (tokens[1] == "line")
    {
        double sx = std::stod(tokens[2]);
        double sy = std::stod(tokens[3]);
        double ex = std::stod(tokens[4]);
        double ey = std::stod(tokens[5]);

        return new Line(Point{sx, sy}, Point{ex, ey}, tokens[6]);
    }
    else
    {
        throw std::invalid_argument("Invalid figure type: " + tokens[1]);
    }
}
