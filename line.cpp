#include "line.hpp"
#include "point.hpp"
#include "figure.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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

bool Line::within(std::string &input) const
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
