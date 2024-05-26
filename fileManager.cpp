#include "fileManager.hpp"
#include "SVGParser.hpp"
#include "figure.hpp"
#include "circle.hpp"
#include "line.hpp"
#include "rect.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <cstddef>
#include <sstream>

FileManager &FileManager::getInstance()
{
    static FileManager instance;
    return instance;
}

FileManager::FileManager() : fileLoaded(false) {}

bool FileManager::openFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::ofstream newFile(path);
        if (!newFile)
        {
            std::cout << "Error creating new file." << std::endl;
            return false;
        }

        newFile.close();
        fileContents.clear();
        fileLoaded = true;
        filePath = path;
        std::cout << "New file created." << std::endl;
        return true;
    }

    fileContents.clear();

    figuresInFile = SVGParser::getInstance().getFiguresFromFile(file);

    file.close();
    fileLoaded = true;
    filePath = path;
    std::cout << "Successfully opened " << path << std::endl;
    return true;
}

void FileManager::closeFile()
{
    if (fileLoaded)
    {
        fileLoaded = false;
        fileContents.clear();

        for (auto figure : figuresInFile)
        {
            delete figure;
        }

        figuresInFile.clear();

        std::cout << "Successfully closed file " << filePath << std::endl;
    }
    else
    {
        std::cout << "No file is currently open." << std::endl;
    }
}

bool FileManager::saveFile() const
{
    if (!fileLoaded)
    {
        std::cout << "No file is currently open." << std::endl;
        return false;
    }

    std::ofstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "Error saving file." << std::endl;
        return false;
    }

    file << "<svg>" << std::endl;

    std::cout<<figuresInFile.size()<<std::endl;

    for (size_t i = 0; i < figuresInFile.size(); i++)
    {
        file << figuresInFile[i]->toSVG() << std::endl;
        std::cout<<i<<std::endl;
    }

    file << "<svg/>" << std::endl;

    file.close();
    std::cout << "Successfully saved file " << filePath << std::endl;
    return true;
}

bool FileManager::saveFileAs(const std::string &newPath) const
{
    if (!fileLoaded)
    {
        std::cout << "No file is currently open." << std::endl;
        return false;
    }

    std::ofstream file(newPath);
    if (!file.is_open())
    {
        std::cout << "Error saving file." << std::endl;
        return false;
    }

    for (size_t i; i < figuresInFile.size(); i++)
    {
        file << figuresInFile[i]->toSVG() << std::endl;
    }

    file.close();
    std::cout << "Successfully saved file " << newPath << std::endl;
    return true;
}

void FileManager::displayHelp() const
{
    std::cout << "Supported commands" << std::endl
              << "open <file>" << std::endl
              << "close" << std::endl
              << "save" << std::endl
              << "saveas" << std::endl
              << "help" << std::endl
              << "exit" << std::endl;
}

std::vector<std::string> FileManager::getContents() const
{
    return fileContents;
}

std::vector<Figure *> FileManager::getFiguresInFile() const
{
    return figuresInFile;
}

void FileManager::erase(std::size_t index)
{
    figuresInFile.erase(figuresInFile.begin() + index);
    std::cout<<"Successfully erased figure."<<std::endl;
}

void FileManager::translateAll(double vertical, double horizontal)
{
    for (auto figure : figuresInFile)
    {
        figure->translate(vertical, horizontal);
    }
}

void FileManager::print() const
{
    std::vector<Figure *> figures = FileManager::getInstance().getFiguresInFile();

    for (auto figure : figures)
    {
        figure->print();
    }
}

Figure *FileManager::create(std::string &input)
{
    std::istringstream iss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, ' '))
    {
        if (!token.empty())
        {
            tokens.push_back(token);
        }
    }

    if (tokens[1] == "rectangle")
    {
        double vx = std::stod(tokens[2]);
        double vy = std::stod(tokens[3]);
        double width = std::stod(tokens[4]);
        double height = std::stod(tokens[5]);

        return new Rect(Point{vx, vy}, width, height, tokens[6]);
    }
    else if (tokens[1] == "circle")
    {
        double cx = std::stod(tokens[2]);
        double cy = std::stod(tokens[3]);
        double radius = std::stod(tokens[4]);

        return new Circle(Point{cx, cy}, radius, tokens[5]);
    }
    else if (tokens[1] == "line")
    {
        double sx = std::stod(tokens[2]);
        double sy = std::stod(tokens[3]);
        double ex = std::stod(tokens[4]);
        double ey = std::stod(tokens[5]);

        return new Line(Point{sx, sy}, Point{ex, ey}, tokens[6]);
    }
    else
    {
        throw std::invalid_argument("Invalid figure type: " + tokens[1]);
    }
}
