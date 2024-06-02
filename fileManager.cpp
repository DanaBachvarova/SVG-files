#include "fileManager.hpp"
#include "SVGParser.hpp"
#include "figure.hpp"
#include "circle.hpp"
#include "line.hpp"
#include "rect.hpp"
#include "commandsManager.hpp"

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

FileManager::FileManager() : fileLoaded(false), savedChanges(true) {}

bool FileManager::getFileLoaded()
{
    return fileLoaded;
}

size_t FileManager::getFiguresInFileSize()
{
    return figuresInFile.size();
}

std::vector<std::string> FileManager::getContents() const
{
    return fileContents;
}

std::vector<Figure *> FileManager::getFiguresInFile() const
{
    return figuresInFile;
}

/**
 * Opens a file and loads its contents into memory.
 * If the file does not exist, a new file will be created.
 *
 * @param path The path of the file to be opened.
 * @return True if the file was successfully opened or created, false otherwise.
 */
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

/**
 * @brief Closes the currently open file.
 *
 * If a file is currently loaded, this function clears the file contents, deletes all figures in the file,
 * and sets the fileLoaded flag to false. It also prints a success message indicating the file has been closed.
 * If no file is currently open, it prints a message indicating that no file is open.
 */
void FileManager::closeFile()
{
    if (fileLoaded)
    {
        if (!savedChanges)
        {
            std::cout << "There are unsaved changes. Do you want to save them? (yes/no)" << std::endl;
            std::string answer;
            std::cout << "> ";

            std::cin >> answer;
            std::cin.ignore();

            if (answer == "yes")
            {
                saveFile();
            }

            savedChanges = true;
        }

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

bool FileManager::saveFile()
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
    savedChanges = true;

    return true;
}

bool FileManager::saveFileAs(const std::string &newPath)
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

    file << "<svg>" << std::endl;

    for (size_t i; i < figuresInFile.size(); i++)
    {
        file << figuresInFile[i]->toSVG() << std::endl;
    }

    file << "</svg>" << std::endl;

    file.close();
    std::cout << "Successfully saved file " << newPath << std::endl;
    savedChanges = true;

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
        if (!savedChanges)
        {
            std::cout << "There are unsaved changes. Do you want to save them? (yes/no)" << std::endl;
            std::string answer;
            std::cout << "> ";

            std::cin >> answer;

            if (answer == "yes")
            {
                saveFile();
            }
        }

        savedChanges = true;

        fileContents.clear();
        fileLoaded = false;

        for (auto figure : figuresInFile)
        {
            delete figure;
        }

        figuresInFile.clear();
    }

    std::cout << "Exiting...\n";
}

void FileManager::erase(std::size_t index)
{
    figuresInFile.erase(figuresInFile.begin() + index - 1);
    std::cout << "Successfully erased " << figuresInFile[index - 1]->getType() << " (" << index << ")!\n";
    savedChanges = false;
}

void FileManager::translateAll(double vertical, double horizontal)
{
    for (auto figure : figuresInFile)
    {
        figure->translate(vertical, horizontal);
    }

    std::cout << "Translated all figures!\n";
    savedChanges = false;
}

void FileManager::translateByIndex(size_t index, double vertical, double horizontal)
{
    figuresInFile[index - 1]->translate(vertical, horizontal);

    std::cout << "Translated figure (" << index << ")!\n";
    savedChanges = false;
}

void FileManager::print() const
{
    for (size_t i = 0; i < figuresInFile.size(); i++)
    {
        std::cout << "(" << i + 1 << ") ";
        figuresInFile[i]->print();
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

        if (width <= 0 || height <= 0)
        {
            std::cout << "Width and height cannot be negative!\n";
            return;
        }

        figuresInFile.push_back(new Rect(Point{vx, vy}, width, height, tokens[6]));
        std::cout << "Successfully created rectangle (" << figuresInFile.size() << ")!\n";
        savedChanges = false;
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

        if (radius <= 0)
        {
            std::cout << "Radius cannot be negative!\n";
            return;
        }

        figuresInFile.push_back(new Circle(Point{cx, cy}, radius, tokens[5]));
        std::cout << "Successfully created circle (" << figuresInFile.size() << ")!\n";
        savedChanges = false;
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
        std::cout << "Successfully created line (" << figuresInFile.size() << ")!\n";
        savedChanges = false;
    }
    else
    {
        std::cout << "Invalid figure type!\n";
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
