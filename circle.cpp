#include "circle.hpp"
#include "figure.hpp"
#include "point.hpp"
#include "textParser.hpp"
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
    
}
