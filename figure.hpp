#pragma once

#include <iostream>
#include <cstring>
#include "point.hpp"

class Figure
{
    public:
    
    virtual void print() const = 0;

    Figure(const char*);

    virtual ~Figure()
    {
        delete[] colour;
    }

    const char* getColour() const
    {
        return colour;
    }

    protected:

    const char* colour;
};