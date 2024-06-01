#pragma once

#include "figure.hpp"
#include "point.hpp"

class Rect : public Figure
{
public:
    Rect(Point, double, double, std::string);
    void print() const;
    std::string toSVG() const;
    void translate(double, double);
    bool withinRect(double, double, double, double) const;
    bool withinCircle(double, double, double) const;
    std::string getType() const;
    Point getVertex() const;
    double getWidth() const;
    double getHeight() const;
    std::string getColour() const;

private:
    Point vertex;
    double width;
    double height;
};