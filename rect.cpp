#include "rect.hpp"
#include "point.hpp"

Rect::Rect(Point _vertex, double _width, double _height, const char *_colour) : vertex(_vertex), width(_width), height(_height), Figure(_colour)
{
}

void Rect::print() const
{
    std::cout<<"rect "<<vertex.x<<" "<<vertex.y<<" "<<width<<" "<<height<<" "<<colour<<std::endl; 
}