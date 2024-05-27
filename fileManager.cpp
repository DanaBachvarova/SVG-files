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

    for (size_t i = 0; i < figuresInFile.size(); i++)
    {
        file << figuresInFile[i]->toSVG() << std::endl;
    }

    file << "</svg>" << std::endl;

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
    std::cout << "Supported commands:" << std::endl
              << "open <file>    " << "     - opens file by path" << std::endl
              << "close          " << "     - closes loaded file" << std::endl
              << "save           " << "     - saves changes" << std::endl
              << "saveas         " << "     - saves changes in another file" << std::endl
              << "help           " << "     - shows supported commands" << std::endl
              << "exit           " << "     - terminates the program" << std::endl
              << "print          " << "     - prints all figures" << std::endl
              << "create         " << "     - creates and adds new figure to the file" << std::endl
              << "erase <n>      " << "     - removes the figure with index n" << std::endl
              << "translate [<n>]" << "     - translates all figures or the figure with index n" << std::endl
              << "within <option>" << "     - shows all figures located within a figure" << std::endl;
}

void FileManager::exit()
{
    if (fileLoaded)
    {
        fileContents.clear();
        fileLoaded = false;

        for (auto figure : figuresInFile)
        {
            delete figure;
        }

        figuresInFile.clear();
    }

    std::cout << "Exit\n";
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
    std::cout << "Successfully erased " << figuresInFile[index - 1]->getType() << " (" << index << ")!\n";
    figuresInFile.erase(figuresInFile.begin() + index - 1);
}

void FileManager::translateAll(double vertical, double horizontal)
{
    for (auto figure : figuresInFile)
    {
        figure->translate(vertical, horizontal);
    }

    std::cout << "Translated all figures!\n";
}

void FileManager::translateByIndex(size_t index, double vertical, double horizontal)
{
    figuresInFile[index - 1]->translate(vertical, horizontal);

    std::cout << "Translated figure (" << index << ")!\n";
}

void FileManager::print() const
{
    for (auto figure : figuresInFile)
    {
        figure->print();
    }
}

void FileManager::create(std::vector<std::string> tokens)
{
    if (tokens[1] == "rectangle")
    {
        if (tokens.size() != 7)
        {
            std::cout << "Invalid figure!\n";
            return;
        }

        double vx = std::stod(tokens[2]);
        double vy = std::stod(tokens[3]);
        double width = std::stod(tokens[4]);
        double height = std::stod(tokens[5]);

        figuresInFile.push_back(new Rect(Point{vx, vy}, width, height, tokens[6]));
        std::cout << "Successfully created rectangle (" << figuresInFile.size() + 1 << ")!\n";
    }
    else if (tokens[1] == "circle")
    {
        if (tokens.size() != 6)
        {
            std::cout << "Invalid figure!\n";
            return;
        }

        double cx = std::stod(tokens[2]);
        double cy = std::stod(tokens[3]);
        double radius = std::stod(tokens[4]);

        figuresInFile.push_back(new Circle(Point{cx, cy}, radius, tokens[5]));
        std::cout << "Successfully created circle!\n";
    }
    else if (tokens[1] == "line")
    {
        if (tokens.size() != 7)
        {
            std::cout << "Invalid figure!\n";
            return;
        }

        double sx = std::stod(tokens[2]);
        double sy = std::stod(tokens[3]);
        double ex = std::stod(tokens[4]);
        double ey = std::stod(tokens[5]);

        figuresInFile.push_back(new Line(Point{sx, sy}, Point{ex, ey}, tokens[6]));
        std::cout << "Successfully created line!\n";
    }
    else
    {
        throw std::invalid_argument("Invalid figure type: " + tokens[1]);
    }
}

void FileManager::withinRect(double vx, double vy, double width, double height)
{
    bool empty = true;
    for (auto figure : figuresInFile)
    {
        if (figure->withinRect(vx, vy, width, height))
        {
            figure->print();
            empty = false;
        }
    }

    if (empty)
    {
        std::cout << "No figures are located within rectangle " << vx << " " << vy << " " << width << " " << height << std::endl;
    }
}

void FileManager::withinCircle(double cx, double cy, double r)
{
    bool empty = true;
    for (auto figure : figuresInFile)
    {
        if (figure->withinCircle(cx, cy, r))
        {
            figure->print();
            empty = false;
        }
    }

    if (empty)
    {
        std::cout << "No figures are located within circle " << cx << " " << cy << " " << r << std::endl;
    }
}

bool FileManager::getFileLoaded()
{
    return fileLoaded;
}

size_t FileManager::getFiguresInFileSize()
{
    return figuresInFile.size();
}
