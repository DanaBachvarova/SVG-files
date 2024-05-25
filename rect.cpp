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

void Rect::translate(std::string &input)
{
    size_t posVertical = input.find("vertical=");
    size_t startVertical = posVertical + 9;
    size_t endVertical = input.find(" ", startVertical);
    double vertical = std::stod(input.substr(startVertical, endVertical - startVertical));

    size_t posHorizontal = input.find("horizontal=");
    size_t startHorizontal = posHorizontal + 11;
    double horizontal = std::stod(input.substr(startHorizontal));

    vertex.x += horizontal;
    vertex.y += vertical;
}

bool Rect::within(std::string) const
{
    return false;
}
