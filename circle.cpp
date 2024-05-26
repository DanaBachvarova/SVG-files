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

bool Circle::within(const std::string &userInput) const
{
    return false;
}

std::string Circle::toSVG() const
{
    std::string result = "<circle cx=\"" + std::to_string(center.x) + "\" cy=\"" + std::to_string(center.y) + "\" r=\"" + std::to_string(radius) + "\" fill=\"" + colour + "\" />";

    return result;
}

void Circle::translate(std::string &input)
{
    size_t posVertical = input.find("vertical=");
    size_t startVertical = posVertical + 9;
    size_t endVertical = input.find(" ", startVertical);
    double vertical = std::stod(input.substr(startVertical, endVertical - startVertical));

    size_t posHorizontal = input.find("horizontal=");
    size_t startHorizontal = posHorizontal + 11;
    double horizontal = std::stod(input.substr(startHorizontal));

    center.x = center.x + horizontal;
    center.y = center.y + vertical;
}

bool Circle::within(std::string &input) const
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
    }
    else if (tokens[1] == "circle")
    {
    }
    else
    {
        throw std::invalid_argument("Invalid region type: " + tokens[1]);
    }
}