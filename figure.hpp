#pragma once

#include <iostream>
#include <cstring>
#include "point.hpp"

class Figure
{
public:
    virtual void print() const = 0;

    Figure(std::string);
    virtual ~Figure();
    std::string getColour() const;

protected:
    std::string colour;
};