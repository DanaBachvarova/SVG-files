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
    bool saveFile();
    bool saveFileAs(const std::string&);
    void displayHelp() const;
    void exit();
    std::vector<std::string> getContents() const;
    std::vector<Figure*> getFiguresInFile() const;
    void erase(std::size_t);
    void translateAll(double, double);
    void translateByIndex(size_t, double, double);
    void print() const;
    void create(std::vector<std::string>);
    void withinRect(double, double, double, double);
    void withinCircle(double, double, double);
    bool getFileLoaded();
    size_t getFiguresInFileSize();
    void setSavedChanges(bool);

private:
    std::string filePath;
    bool fileLoaded;
    std::vector<std::string> fileContents;
    std::vector<Figure*> figuresInFile;
    bool savedChanges;
    
    FileManager();
    FileManager(FileManager const&) = delete;
    void operator=(FileManager const&) = delete;
};