#include "attribute.hpp"

SVGAttribute::SVGAttribute(std::string name, std::string value) : name(name), value(value) {}

std::string SVGAttribute::getName()
{
    return name;
}

std::string SVGAttribute::getValue()
{
    return value;
}
