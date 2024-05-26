#pragma once

#include "figure.hpp"
#include "point.hpp"

class Line : public Figure
{
public:
    Line(Point, Point, std::string);
    void print() const;
    bool within(std::string) const;
    std::string toSVG() const;
    void translate(std::string &input);
    bool withinRect(double, double, double, double) const;
    bool withinCircle(double, double, double) const;

private:
    Point start;
    Point end;
};