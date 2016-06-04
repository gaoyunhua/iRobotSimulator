
#ifndef SIMULATOR_FILEREADER_H
#define SIMULATOR_FILEREADER_H

#include <map>
#include <string>
#include <vector>
#include "FileReader.h"
#include "House.h"

using namespace std;

typedef int score_func(const map<string, int>&);

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
    static string concatenateAbsolutePath(const string& dirPath, const string& fileName);

public:
    static map<string,int> ReadConfig(string dirPath);
    static pair<vector<House*>,vector<pair<string,string> > > ReadHouses(string dirPath);
    static vector<string> ReadAlgorithms(string dirPath);
    static score_func* ScoreFunction(string& path, void*& filename);

    static vector<string> GetFilesFromDir(string dir, string suffix);
};


#endif //SIMULATOR_FILEREADER_H
