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

std::string Line::getType() const
{
    return "line";
}

Point Line::getStart() const
{
    return start;
}

Point Line::getEnd() const
{
    return end;
}

std::string Line::getColour() const
{
    return colour;
}

void Line::print() const
{
    std::cout << "line " << start.x << " " << start.y << " " << end.x << " " << end.y << " " << colour << std::endl;
}

/**
 * Converts the Line object to an SVG string representation.
 *
 * @return The SVG string representation of the Line object.
 */
std::string Line::toSVG() const
{
    std::string result = "\t<line x1=\"" + std::to_string(start.x) + "\" x2=\"" + std::to_string(start.y) + "\" y1=\"" + std::to_string(end.x) + "\" y2=\"" + std::to_string(end.y) + "\" stroke=\"" + colour + "\" />";

    return result;
}

void Line::translate(double vertical, double horizontal)
{
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
