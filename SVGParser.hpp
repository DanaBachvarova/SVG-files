#pragma once
#include "figure.hpp" 
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

class SVGParser
{
public:
    static SVGParser& getInstance();
    void splitInput(const std::string &);
    std::vector<std::string> getTokens();
    std::vector<Figure*> getFiguresFromFile(std::ifstream&);
    Figure* getFigureFromStr(std::string);
    const std::vector<std::string> getTokens() const;

private:
    SVGParser();
    SVGParser(SVGParser const&) = delete;
    void operator=(SVGParser const&) = delete;

    std::vector<std::string> tokens;
};