#include <fstream>
#include <map>
#include "FileReader.h"

map<string,int> FileReader::ReadConfig(string fileName)
{
    map<string,int> configurationMap;
    configurationMap.clear();

//    if (fileName.empty())
//        return configurationMap;

    /*read values*/
    configurationMap.insert(pair<string,int>("MaxSteps", 1200));
    configurationMap.insert(pair<string,int>("MaxStepsAfterWinner", 200));
    configurationMap.insert(pair<string,int>("BatteryCapacity", 400));
    configurationMap.insert(pair<string,int>("BatteryConsumptionRate", 1));
    configurationMap.insert(pair<string,int>("BatteryRechargeRate", 20));

    return configurationMap;
};

char** FileReader::ReadHouse(string fileName)
{
    char** house = new char*[20];
    return house;

}