#pragma once

#include "figure.hpp"
#include "point.hpp"

class Circle : public Figure
{
public:
    Circle(Point, double, std::string);
    void print() const;
    bool within(const std::string &) const;
    std::string toSVG() const;
    void translate(double, double);
    bool withinRect(double, double, double, double) const;
    bool withinCircle(double, double, double) const;

private:
    Point center;
    double radius;
};