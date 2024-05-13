#include "line.hpp"
#include "point.hpp"

Line::Line(Point _start, Point _end, const char* _colour) : start(_start), end(_end), Figure(_colour)
{
}

void Line::print() const
{
    std::cout<<"line "<<start.x<<" "<<start.y<<" "<<end.x<<" "<<end.y<<" "<<colour<<std::endl;
}