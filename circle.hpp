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
    void translate(std::string &input);
    bool within(std::string&) const;

private:
    Point center;
    double radius;
};