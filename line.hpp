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
    bool within(std::string) const;

private:
    Point start;
    Point end;
};