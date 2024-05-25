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
    //virtual bool within(std::string) const = 0;
    virtual std::string toSVG() const = 0;

protected:
    std::string colour;
};