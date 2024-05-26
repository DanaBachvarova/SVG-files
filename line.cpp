#include "line.hpp"
#include "point.hpp"
#include "figure.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

Line::Line(Point start, Point end, std::string colour) : start(start), end(end), Figure(colour)
{
}

void Line::print() const
{
    std::cout << "line " << start.x << " " << start.y << " " << end.x << " " << end.y << " " << colour << std::endl;
}

std::string Line::toSVG() const
{
    std::string result = "<line x1=\"" + std::to_string(start.x) + "\" x2=\"" + std::to_string(start.y) + "\" y1=\"" + std::to_string(end.x) + "\" y2=\"" + std::to_string(end.y) + "\" stroke=\"" + colour + "\" />";

    return result;
}

void Line::translate(std::string &input)
{
    size_t posVertical = input.find("vertical=");
    size_t startVertical = posVertical + 9;
    size_t endVertical = input.find(" ", startVertical);
    double vertical = std::stod(input.substr(startVertical, endVertical - startVertical));

    size_t posHorizontal = input.find("horizontal=");
    size_t startHorizontal = posHorizontal + 11;
    double horizontal = std::stod(input.substr(startHorizontal));

    start.x += horizontal;
    end.x += horizontal;
    start.y += vertical;
    end.y += vertical;
}

bool Line::withinRect(double vx, double vy, double width, double height) const
{
    if ((start.x >= vx && start.x <= vx + width) && (start.y >= vy && start.y <= vy + height) && (end.x >= vx && end.x <= vx + width) && (end.y >= vy && end.y <= vy + height))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Line::withinCircle(double cx, double cy, double radius) const
{
    double d1 = sqrt(pow(cx - start.x, 2) + pow(cy - start.y, 2));
    double d2 = sqrt(pow(cx - end.x, 2) + pow(cy - end.y, 2));

    if (d1 <= radius && d2 <= radius)
    {
        return true;
    }
    else
    {
        return false;
    }
}
