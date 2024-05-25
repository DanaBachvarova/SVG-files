#pragma once

#include "figure.hpp"
#include "point.hpp"

class Rect : public Figure
{
    public:
    Rect(Point, double, double, std::string);
    void print() const;

    private:
    Point vertex;
    double width;
    double height;
};