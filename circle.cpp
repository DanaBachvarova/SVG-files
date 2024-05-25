#include "circle.hpp"
#include "figure.hpp"
#include "point.hpp"
#include "SVGParser.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

Circle::Circle(Point center, double radius, std::string colour) : center(center), radius(radius), Figure(colour)
{
}

void Circle::print() const
{
    std::cout << "circle " << center.x << " " << center.y << " " << radius << " " << colour << std::endl;
}

bool Circle::within(const std::string &userInput) const
{
    return false;
}

std::string Circle::toSVG() const
{
    std::string result = "<circle cx=\"" + std::to_string(center.x) + "\" cy=\"" + std::to_string(center.y) + "\" r=\"" + std::to_string(radius) + "\" fill=\"" + colour + "\" />";

    return result;
}
