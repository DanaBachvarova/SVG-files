#pragma once

#include <iostream>
#include <cstring>
#include "point.hpp"

class Figure
{
    public:
    
    virtual void print() const = 0;

    virtual ~Figure()
    {
        delete[] colour;
    }

    const char* getColour() const
    {
        return colour;
    }

    private:

    const char* colour;
};