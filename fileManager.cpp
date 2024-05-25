#include "fileManager.hpp"
#include "SVGParser.hpp"
#include "figure.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <cstddef>

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

    for (size_t i = 0; i < fileContents.size(); i++)
    {
        file << fileContents[i] << std::endl;
    }

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

    for (size_t i; i < fileContents.size(); i++)
    {
        file << fileContents[i] << std::endl;
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
