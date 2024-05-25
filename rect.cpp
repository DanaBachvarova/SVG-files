#include "rect.hpp"
#include "point.hpp"
#include "figure.hpp"
#include <iostream>

Rect::Rect(Point vertex, double width, double height, std::string colour) : vertex(vertex), width(width), height(height), Figure(colour) {}

void Rect::print() const
{
    std::cout << "rect " << vertex.x << " " << vertex.y << " " << width << " " << height << " " << colour << std::endl;
}

std::string Rect::toSVG() const
{
    std::string result = "<rect x=\"" + std::to_string(vertex.x) + "\" y=\"" + std::to_string(vertex.y) + "\" width=\"" + std::to_string(width) + "\" height=\"" + std::to_string(height) + "\" fill=\"" + colour + "\" />";

    return result;
}
