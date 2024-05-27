#include "circle.hpp"
#include "figure.hpp"
#include "point.hpp"
#include "SVGParser.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

Circle::Circle(Point center, double radius, std::string colour) : center(center), radius(radius), Figure(colour)
{
}

void Circle::print() const
{
    std::cout << "circle " << center.x << " " << center.y << " " << radius << " " << colour << std::endl;
}

std::string Circle::toSVG() const
{
    std::string result = "<circle cx=\"" + std::to_string(center.x) + "\" cy=\"" + std::to_string(center.y) + "\" r=\"" + std::to_string(radius) + "\" fill=\"" + colour + "\" />";

    return result;
}

void Circle::translate(double vertical, double horizontal)
{
    center.x = center.x + horizontal;
    center.y = center.y + vertical;
}

bool Circle::withinRect(double vx, double vy, double width, double height) const
{
    if (center.x - radius >= vx && center.x + radius <= vx + width && center.y - radius >= vy && center.y + radius <= vy + height)
    {
        return true;
    }

    return false;
}

bool Circle::withinCircle(double cx, double cy, double regionRadius) const
{
    double d = sqrt(pow(cx - center.x, 2) + pow(cy - center.y, 2));

    if (d <= regionRadius - radius)
    {
        return true;
    }

    return false;
}

std::string Circle::getType() const
{
    return "circle";
}
