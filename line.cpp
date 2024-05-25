#include "line.hpp"
#include "point.hpp"
#include "figure.hpp"
#include <iostream>

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

// bool Line::within(std::string input) const
// {
//     return false;
// }