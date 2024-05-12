#include <iostream>
#include "circle.cpp"
#include "rect.cpp"
#include "line.cpp"

int main()
{
    Point x = {0, 0};
    Point y = {1, 1};
    Line line = Line(x, y, "blue");
    line.print();
}