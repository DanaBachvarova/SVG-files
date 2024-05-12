#include "circle.hpp"
#include <cmath>
#include "point.hpp"

Circle::Circle(Point _center, double _radius, const char* _colour):center(_center), radius(_radius), colour(_colour)
{
}

void Circle::print() const
{
    std::cout<<"circle "<<center.x<<" "<<center.y<<" "<<radius<<" "<<colour<<std::endl;
}