#pragma once

#include <iostream>
#include <cstring>
#include "point.hpp"

class Figure
{
public:
    virtual void print() const = 0;

    Figure(std::string);
    std::string getColour() const;
    virtual std::string toSVG() const = 0;
    virtual void translate(double, double) = 0;
    virtual bool withinRect(double, double, double, double) const = 0;
    virtual bool withinCircle(double, double, double) const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getColour() const = 0;

protected:
    std::string colour;
};