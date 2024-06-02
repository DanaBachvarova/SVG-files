#include "rect.hpp"
#include "point.hpp"
#include "figure.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>

Rect::Rect(Point vertex, double width, double height, std::string colour) : vertex(vertex), width(width), height(height), Figure(colour)
{
    if (width < 0 || height < 0)
    {
        throw std::invalid_argument("Width and height cannot be negative");
    }
}

std::string Rect::getType() const
{
    return "rectangle";
}

Point Rect::getVertex() const
{
    return vertex;
}

double Rect::getWidth() const
{
    return width;
}

double Rect::getHeight() const
{
    return height;
}

std::string Rect::getColour() const
{
    return colour;
}

void Rect::print() const
{
    std::cout << "rectangle " << vertex.x << " " << vertex.y << " " << width << " " << height << " " << colour << std::endl;
}

/**
 * @brief Converts the Rect object to an SVG string representation.
 * 
 * @return The SVG string representation of the Rect object.
 */
std::string Rect::toSVG() const
{
    std::string result = "\t<rect x=\"" + std::to_string(vertex.x) + "\" y=\"" + std::to_string(vertex.y) + "\" width=\"" + std::to_string(width) + "\" height=\"" + std::to_string(height) + "\" fill=\"" + colour + "\" />";

    return result;
}

void Rect::translate(double vertical, double horizontal)
{
    vertex.x += horizontal;
    vertex.y += vertical;
}

bool Rect::withinRect(double vx, double vy, double regionWidth, double regionHeight) const
{
    if (vertex.x < vx || vertex.y < vy)
    {
        return false;
    }

    if (vertex.x + width > vx + regionWidth || vertex.y + height > vy + regionHeight)
    {
        return false;
    }

    return true;
}

bool Rect::withinCircle(double cx, double cy, double radius) const
{
    double d1 = sqrt(pow(cx - vertex.x, 2) + pow(cy - vertex.y, 2));
    double d2 = sqrt(pow(cx - vertex.x, 2) + pow(cy - (vertex.y + height), 2));
    double d3 = sqrt(pow(cx - (vertex.x + width), 2) + pow(cy - vertex.y, 2));
    double d4 = sqrt(pow(cx - (vertex.x + width), 2) + pow(cy - (vertex.y + height), 2));

    if (d1 <= radius && d2 <= radius && d3 <= radius && d4 <= radius)
    {
        return true;
    }

    return false;
}
