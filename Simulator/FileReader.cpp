#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include "FileReader.h"
#include "FileLister.h"

using namespace std;

/*
 * Returns a pair representing the File Read state.
 * int key = status code
 * key = 0 --> valid
 * key = -1 --> invalid
 * if key is valid, value represent the requested value
 * if key is invalid, value represents the error message if available
 */
pair<int, string> FileReader::GetFilePath(string dirPath, string fileName) {
    string filePath = dirPath.empty() ?
                      fileName :
                      dirPath.back() == '/' ?
                      dirPath + fileName :
                      dirPath + "/" + fileName;

    string finalPath;
    fstream file(filePath.c_str());
    if (file.good()) {
        return pair<int, string>(0, filePath);
    }
    else {
        finalPath = filePath[0] == '/' ? ".." + filePath : "../" + filePath;
        fstream relativeFile(finalPath.c_str());
        if (!relativeFile) {
            return pair<int, string>(-1, "");
        }
        if (!relativeFile.good()) {
            relativeFile.close();
            return pair<int, string>(-1, fileName + " exists in " + filePath + " but cannot be opened");
        }
        relativeFile.close();
    }
    file.close();
    return pair<int, string>(0, finalPath);
}

map<string, int> FileReader::ReadConfig(string dirPath) {
    pair<int, string> filePathPair = GetFilePath(dirPath, "config.ini");

    if (filePathPair.first == -1) {
        if (filePathPair.second.empty()) {
            string usageMessage = "Usage: simulator [-config <config path>] [-house_path <house path>] [-algorithm_path <algorithm path>]";
            cout << usageMessage << endl;
            exit(0);
        }
        else {
            cout << filePathPair.second << endl;
            exit(0);
        }
    }

    map<string, int> configurationMap = DefaultConfig();
    string line;
    int value, propertyCounter = 0;

    ifstream input(filePathPair.second.c_str());
    while (input >> line) {
        string delimiter = "=";
        string key = line.substr(0, line.find(delimiter));
        string stringValue = line.substr(line.find(delimiter) + 1, line.length() - key.length() - 1);
        value = atoi(stringValue.c_str());
        if (configurationMap.count(key)) {
            configurationMap[key] = value;
            propertyCounter++;
        }
    }

    if (propertyCounter < configurationMap.size()) {
        vector<string> missingParams;
        for (auto &keyValue : configurationMap) {
            if (keyValue.second == -1)
                missingParams.push_back(keyValue.first);
        }

        cout << "config.ini missing " + to_string(missingParams.size()) + " parameter(s): " << endl;
        PrintStringVector(missingParams);
        exit(0);
    }

    return configurationMap;
}

void FileReader::PrintStringVector(const vector<string> &vec) {
    for (vector<string>::const_iterator itr = vec.begin();
         itr != vec.end();
         ++itr) {
        cout << *itr;
        if (itr + 1 != vec.end()) {
            cout << ", ";
        }
    }
    cout << endl;
}

map<string, int> FileReader::DefaultConfig() {
    map<string, int> configurationMap =
            {{"MaxSteps",               -1},
             {"MaxStepsAfterWinner",    -1},
             {"BatteryCapacity",        -1},
             {"BatteryConsumptionRate", -1},
             {"BatteryRechargeRate",    -1}};
    return configurationMap;
}

House FileReader::ReadHouse() {
    enum {
        rows = 19, cols = 80
    };
    char houseStructure[rows][cols + 1] = {
            //             1         2         3         4         5         6         7
            //   01234567890123456789012345678901234567890123456789012345678901234567890123456789
            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
            "W  99  8D5             1234321                                                 W", // 1
            "W  99      WWWWWWW     1234321                     W                       1   W", // 2
            "W              W                                   W   555                 2   W", // 3
            "W              W                                   W   555                 3   W", // 4
            "W              W           WWWWWWWWWWWWWWWWWWWWWWWWW                       4   W", // 5
            "W              W                                                           5   W", // 6
            "W              W                                                           6   W", // 7
            "W                          WWWWWWWWWWWWWWWWWWWWWW  WWWWWWW                 7   W", // 8
            "W         1         2         3         4         5W 999 W  6         7        W", // 9
            "W              W           444                     W 999 W                 9   W", // 10
            "W              W           444                     W 999 W                 8   W", // 11
            "W              W                                   W     W                 7   W", // 12
            "W              W                                   WW   WW                 6   W", // 13
            "W              W                                    W   W                  5   W", // 14
            "W              W                                                           4   W", // 15
            "W              W                                                           3   W", // 16
            "W              W                                                               W", // 17
            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" // 18
    };

    char **house = new char *[rows];
    for (int i = 0; i < rows; i++) {
        house[i] = new char[cols];
        for (int j = 0; j < cols; j++)
            house[i][j] = houseStructure[i][j];
    }

    House completeHouse = House(19, 81, house);
    return completeHouse;
}


House* FileReader::ReadHouses(string dirPath)
{
    string fixedDirPath = dirPath;
    if (dirPath.empty())
    {
        fixedDirPath = "./houses/";
    }

    HousesLister housesLister = HousesLister(fixedDirPath);
    vector<string> houseFileNames = housesLister.getFilesList();

    for(auto& a : houseFileNames)
        cout << a << endl;
    //TODO: read several houses
    House* h = FileReader::input(houseFileNames[0]);
    return h;
}

House* FileReader::input(string filePath)
{
    cout << "Reading house from file: " + filePath + " into class House" << endl;
    ifstream fin(filePath);

    string name, desc;
    int rows, cols;

    getline(fin, name);
    getline(fin, desc);
    fin >> rows;
    fin >> cols;
    fin.ignore();

//    House house = House(rows, cols);

    char** hh = new char*[rows];
    for (int i = 0; i < rows; i++)
    {
        hh[i] = new char[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        char* row = hh[i];
        string a = (string)row;
        getline(fin, a);
        strncpy(row, a.c_str(), cols);
    }
    House* a = new House(rows, cols, hh);
    return a;
}
