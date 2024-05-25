#pragma once 

#include "figure.hpp"
#include "point.hpp"

class Line : public Figure
{
    public:
    Line(Point, Point, std::string);
    void print() const;

    private:
    Point start;
    Point end;
};