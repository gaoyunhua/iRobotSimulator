
#ifndef SIMULATOR_FILEREADER_H
#define SIMULATOR_FILEREADER_H

#include <map>
#include <string>
#include "FileReader.h"
#include "House.h"

using namespace std;

class FileReader
{

private:
    static map<string, int> DefaultConfig();

public:
    static map<string,int> ReadConfig(string fileName);
    static House ReadHouse();

    static ifstream getFileStream(string fileName);
};


#endif //SIMULATOR_FILEREADER_H
