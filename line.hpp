#pragma once

#include "figure.hpp"
#include "point.hpp"

class Line : public Figure
{
public:
    Line(Point, Point, std::string);
    void print() const;
    std::string toSVG() const;
    void translate(double, double);
    bool withinRect(double, double, double, double) const;
    bool withinCircle(double, double, double) const;
    std::string getType() const;
    Point getStart() const;
    Point getEnd() const;
    std::string getColour() const;

private:
    Point start;
    Point end;
};