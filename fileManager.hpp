#include <iostream>
#include <cstring>
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

private:
    std::string filePath;
    bool fileLoaded;
    std::vector<std::string> fileContents;
    
    FileManager();
    FileManager(FileManager const&) = delete;
    void operator=(FileManager const&) = delete;
};