
#ifndef SIMULATOR_FILEREADER_H
#define SIMULATOR_FILEREADER_H

#include <map>
#include <string>
#include <vector>
#include "FileReader.h"
#import "House.h"

using namespace std;

class FileReader
{

private:
    static map<string, int> DefaultConfig();
    static pair<int, string> GetFilePath(string dirPath, string fileName);
    static void PrintStringVector(const vector<string>& vec);

public:
    static map<string,int> ReadConfig(string dirPath);
    static House ReadHouse();
};


#endif //SIMULATOR_FILEREADER_H
