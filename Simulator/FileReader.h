
#ifndef SIMULATOR_FILEREADER_H
#define SIMULATOR_FILEREADER_H

#include <map>
#include <string>
#include <vector>
#include "FileReader.h"
#import "House.h"

using namespace std;

class ReadHouses;

class FileReader
{

private:
    static map<string, int> DefaultConfig();
    static pair<int, string> GetFilePath(string dirPath, string fileName);
    static void PrintStringVector(const vector<string>& vec);
    static House* input(string filePath);
    static void fixHouse(House* h);
    static string isValidHouse(House* h);

public:
    static map<string,int> ReadConfig(string dirPath);
    static pair<vector<House*>,vector<pair<string,string> > > ReadHouses(string dirPath);
};


#endif //SIMULATOR_FILEREADER_H
