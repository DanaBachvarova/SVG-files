#pragma once

#include "figure.hpp"
#include "point.hpp"

class Circle : public Figure
{
    public:
    Circle(Point, double, std::string);
    void print() const;
    bool within(const std::string&) const;

    private:
    Point center;
    double radius;
};