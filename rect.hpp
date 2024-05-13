#pragma once

#include "figure.hpp"
#include "point.hpp"

class Rect : public Figure
{
    public:
    Rect(Point, double, double, const char*);
    void print() const;

    private:
    Point vertex;
    double width;
    double height;
};