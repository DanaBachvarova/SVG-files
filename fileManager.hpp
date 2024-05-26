#pragma once

#include "figure.hpp"
#include <iostream>
#include <string>
#include <vector>

class FileManager
{
public:
    static FileManager& getInstance();

    bool openFile(const std::string&);
    void closeFile();
    bool saveFile() const;
    bool saveFileAs(const std::string&) const;
    void displayHelp() const;
    std::vector<std::string> getContents() const;
    std::vector<Figure*> getFiguresInFile() const;
    void erase(std::size_t);
    void translateAll(double, double);
    void print() const;
    Figure* create(std::string&);

    

private:
    std::string filePath;
    bool fileLoaded;
    std::vector<std::string> fileContents;
    std::vector<Figure*> figuresInFile;
    
    
    FileManager();
    FileManager(FileManager const&) = delete;
    void operator=(FileManager const&) = delete;
};