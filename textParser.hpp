#pragma once
#include <iostream>
#include <cstring>
#include <vector>

class TextParser
{
public:
    static TextParser& getInstance();
    std::vector<std::string> splitInput(const std::string &);

private:
    TextParser();
    TextParser(TextParser const&) = delete;
    void operator=(TextParser const&) = delete;
};