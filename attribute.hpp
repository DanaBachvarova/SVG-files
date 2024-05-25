#pragma once

#include <cstring>
#include <string>

class SVGAttribute
{
public:
    SVGAttribute(std::string, std::string);
    std::string getName();
    std::string getValue();
    std::string toSVG() const;

private:
    std::string name;
    std::string value;
};