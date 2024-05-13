#include <iostream>
#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"

int main()
{
    Point x = {0, 0};
    Circle circle = Circle(x, 10, "yellow");
    circle.print();
}