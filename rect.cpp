#include "rect.hpp"
#include "point.hpp"
#include "figure.hpp"
#include <iostream>

Rect::Rect(Point vertex, double width, double height, std::string colour) : vertex(vertex), width(width), height(height), Figure(colour) {}

void Rect::print() const
{
    std::cout << "rect " << vertex.x << " " << vertex.y << " " << width << " " << height << " " << colour << std::endl;
}