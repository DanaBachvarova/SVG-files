#include "line.hpp"
#include "point.hpp"
#include "figure.hpp"
#include <iostream>

Line::Line(Point start, Point end, std::string colour) : start(start), end(end), Figure(colour)
{
}

void Line::print() const
{
    std::cout<<"line "<<start.x<<" "<<start.y<<" "<<end.x<<" "<<end.y<<" "<<colour<<std::endl;
}