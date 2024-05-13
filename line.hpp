#pragma once 

#include "figure.hpp"
#include "point.hpp"

class Line : public Figure
{
    public:
    Line(Point, Point, const char*);
    void print() const;

    private:
    Point start;
    Point end;
};