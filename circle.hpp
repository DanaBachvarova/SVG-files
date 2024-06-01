#pragma once

#include "figure.hpp"
#include "point.hpp"

class Circle : public Figure
{
public:
    Circle(Point, double, std::string);
    void print() const;
    std::string toSVG() const;
    void translate(double, double);
    bool withinRect(double, double, double, double) const;
    bool withinCircle(double, double, double) const;
    std::string getType() const;
    Point getCenter() const;
    double getRadius() const;
    std::string getColour() const;

private:
    Point center;
    double radius;
};