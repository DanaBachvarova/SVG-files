#include "fileManager.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

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
            std::cout<<"Error creating file."<<std::endl;
            return false;
        }

        newFile.close();
        fileContents.clear();
        fileLoaded = true;
        filePath = path;
        std::cout<<"New file created."<<std::endl;
        return true;
    }

    std::string line;
    fileContents.clear();
    
    while (std::getline(file, line)) {
        fileContents.push_back(line);
    }

    file.close();
    fileLoaded = true;
    filePath = path;
    std::cout<<"Successfully opened "<<path<<std::endl;
    return true;
}

