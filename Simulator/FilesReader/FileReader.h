
#ifndef SIMULATOR_FILEREADER_H
#define SIMULATOR_FILEREADER_H

#include <map>
#include <string>
#include "FileReader.h"
using namespace std;

class FileReader
{
public:
    static map<string,int> ReadConfig(string fileName);
    static char** ReadHouse(string fileName);
};


#endif //SIMULATOR_FILEREADER_H
