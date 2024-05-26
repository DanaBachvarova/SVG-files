#include "SVGParser.hpp"
#include "figure.hpp"
#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"
#include "attribute.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <string>

SVGParser &SVGParser::getInstance()
{
    static SVGParser instance;
    return instance;
}

SVGParser::SVGParser() {}

void SVGParser::splitInput(const std::string &userInput)
{
    std::istringstream iss(userInput);
    tokens.clear();
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }
}

std::vector<std::string> SVGParser::getTokens()
{
    return tokens;
}

std::vector<Figure *> SVGParser::getFiguresFromFile(std::ifstream &file)
{
    std::vector<Figure *> figures;
    bool foundFigures = false;
    for (std::string line; std::getline(file, line);)
    {
        if (std::strstr(line.c_str(), "</svg>"))
        {
            foundFigures = false;
        }

        if (foundFigures)
        {
            char *figureStr = std::strchr(line.c_str(), '<') + 1;
            char *figureStrEnd = std::strstr(figureStr, "/>");
            *figureStrEnd = '\0';
            std::string figureString(figureStr);
            //std::cout << figureString << std::endl;
            figures.push_back(getFigureFromStr(figureStr));
        }

        if (std::strstr(line.c_str(), "<svg>"))
        {
            foundFigures = true;
        }
    }

    return figures;
}

Figure *SVGParser::getFigureFromStr(std::string figureStr)
{
    std::vector<SVGAttribute> attributes;

    std::istringstream iss(figureStr);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, ' '))
    {
        if (!token.empty())
        {
            tokens.push_back(token);
        }
    }

    std::string figureType = tokens[0];

    for (int i = 1; i < tokens.size(); i++)
    {
        int pos = tokens[i].find('=');

        std::string attrName = tokens[i].substr(0, pos);
        std::string attrValue = tokens[i].substr(pos + 1);
        attrValue = attrValue.substr(1, attrValue.size() - 2);

        attributes.emplace_back(attrName, attrValue);
    }

    if (figureType == "rect")
    {
        double x = std::stod(attributes[0].getValue());
        double y = std::stod(attributes[1].getValue());
        double width = std::stod(attributes[2].getValue());
        double height = std::stod(attributes[3].getValue());

        return new Rect(Point{x,y}, width, height, attributes[4].getValue());
    }
    else if (figureType == "circle")
    {
        double cx = std::stod(attributes[0].getValue());
        double cy = std::stod(attributes[1].getValue());
        double radius = std::stod(attributes[2].getValue());

        return new Circle(Point{cx, cy}, radius, attributes[3].getValue());
    }
    else if (figureType == "line")
    {
        double sx = std::stod(attributes[0].getValue());
        double sy = std::stod(attributes[1].getValue());
        double ex = std::stod(attributes[2].getValue());
        double ey = std::stod(attributes[3].getValue());

        return new Line(Point{sx, sy}, Point{ex, ey}, attributes[4].getValue());
    }
    else
    {
        return nullptr;
    }
}
