#include <fstream>
#include <map>
#include "FileReader.h"
using namespace std;

map<string,int> FileReader::ReadConfig(string fileName)
{
    string filePath = fileName.empty() ? "config.ini" : fileName;
    map<string,int> configurationMap = DefaultConfig();

    string line;
    int value, propertyCounter = 0;
    
    ifstream input = FileReader::getFileStream(filePath);
    if (!input)
    {
        return configurationMap;
    }
    
    while (input >> line)
    {
        string delimiter = "=";
        string key = line.substr(0, line.find(delimiter));
        string stringValue = line.substr(line.find(delimiter)+1, line.length() - key.length() - 1);
        value = stoi(stringValue);
        if (configurationMap.count(key))
        {
            configurationMap[key] = value;
            propertyCounter++;
        }
        else
        {
            throw invalid_argument("Invalid configuration file, unknown property: " + key);
        }
    }

    if (propertyCounter < configurationMap.size())
        throw invalid_argument("Invalid configuration file, missing properties");

    return configurationMap;
}

ifstream FileReader::getFileStream(string fileName)
{
    ifstream localInput(fileName);
    if (localInput)
        return localInput;

    ifstream input("../" + fileName);
    return input;
}

map<string,int> FileReader::DefaultConfig()
{
    map<string,int> configurationMap;
    configurationMap.clear();

    configurationMap.insert(pair<string,int>("MaxSteps", 0));
    configurationMap.insert(pair<string,int>("MaxStepsAfterWinner", 0));
    configurationMap.insert(pair<string,int>("BatteryCapacity", 0));
    configurationMap.insert(pair<string,int>("BatteryConsumptionRate", 0));
    configurationMap.insert(pair<string,int>("BatteryRechargeRate", 0));

    return configurationMap;
}

House FileReader::ReadHouse()
{
//    enum {rows = 19, cols = 80};
//    char houseStructure[rows][cols + 1] = {
//        //             1         2         3         4         5         6         7
//        //   01234567890123456789012345678901234567890123456789012345678901234567890123456789
//            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
//            "W  99  8D5             1234321                                                 W", // 1
//            "W  99      WWWWWWW     1234321                     W                       1   W", // 2
//            "W              W                                   W   555                 2   W", // 3
//            "W              W                                   W   555                 3   W", // 4
//            "W              W           WWWWWWWWWWWWWWWWWWWWWWWWW                       4   W", // 5
//            "W              W                                                           5   W", // 6
//            "W              W                                                           6   W", // 7
//            "W                          WWWWWWWWWWWWWWWWWWWWWW  WWWWWWW                 7   W", // 8
//            "W         1         2         3         4         5W 999 W  6         7        W", // 9
//            "W              W           444                     W 999 W                 9   W", // 10
//            "W              W           444                     W 999 W                 8   W", // 11
//            "W              W                                   W     W                 7   W", // 12
//            "W              W                                   WW   WW                 6   W", // 13
//            "W              W                                    W   W                  5   W", // 14
//            "W              W                                                           4   W", // 15
//            "W              W                                                           3   W", // 16
//            "W              W                                                               W", // 17
//            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" // 18
//    };

    enum {rows = 19, cols = 31};
    char houseStructure[rows][cols + 1] = {
            //             1         2         3//
            //   0123456789012345678901234567890
            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
            "W  99  8D5             1234321W", // 1
            "W  99      WWWWWWW     1234321W", // 2
            "W              W              W", // 3
            "W              W              W", // 4
            "W              W           WWWW", // 5
            "W              W              W", // 6
            "W              W              W", // 7
            "W                          WWWW", // 8
            "W         1         2         W", // 9
            "W              W           444W", // 10
            "W              W           444W", // 11
            "W              W              W", // 12
            "W              W              W", // 13
            "W              W              W", // 14
            "W              W              W", // 15
            "W              W              W", // 16
            "W              W              W", // 17
            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" // 18
    };

    char** house = new char*[rows];
    for (int i = 0; i < rows; i++)
    {
        house[i] = new char[cols];
        for (int j = 0; j < cols; j++)
            house[i][j] = houseStructure[i][j];
    }

    House completeHouse = House(19, 31, house);
    return completeHouse;
}
