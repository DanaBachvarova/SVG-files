#pragma once

#include "figure.hpp"
#include "point.hpp"

class Circle : public Figure
{
    public:
    Circle(Point, double, const char*);
    void print() const;

    private:
    Point center;
    double radius;
    const char* colour;
};