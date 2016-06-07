#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include <cstring>
#include "FileReader.h"
#include "FileLister.h"
#include <dlfcn.h>
#include "Debugger.h"

using namespace std;

static const string usageMessage = "Usage: simulator [-config <config path>] [-house_path <house path>] [-algorithm_path <algorithm path>]";

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

    if (propertyCounter < (int)configurationMap.size()) {
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

map<string, int> FileReader::DefaultConfig()
{
    map<string, int> configurationMap;
    configurationMap.clear();
    configurationMap["MaxStepsAfterWinner"] = -1;
    configurationMap["BatteryCapacity"] = -1;
    configurationMap["BatteryConsumptionRate"] = -1;
    configurationMap["BatteryRechargeRate"] = -1;
    return configurationMap;
}

pair<vector<House*>,vector<pair<string,string> > > FileReader::ReadHouses(string dirPath)
{
    string fixedDirPath = dirPath;
    if (dirPath.empty())
    {
        fixedDirPath = "./houses/";
    }

    HousesLister housesLister = HousesLister(fixedDirPath);
    vector<string> houseFileNames = housesLister.getFilesList();

    if (!houseFileNames.size())
    {
        cout << usageMessage << endl;
        exit(0);
    }

    vector<House*> houses;
    vector<pair<string,string> > errorHouses;
    for(auto& houseFileName : houseFileNames)
    {
        pair<int,string> filePathPair = FileReader::GetFilePath("", houseFileName);
        if (filePathPair.first == -1) {
            if (filePathPair.second.empty())
            {
                errorHouses.push_back(pair<string,string>(houseFileName, "unknown error reading house file"));
            }
            else
            {
                errorHouses.push_back(pair<string,string>(houseFileName, filePathPair.second));
            }
        }
        else
        {
            House *h = FileReader::input(filePathPair.second);
            string houseError = FileReader::isValidHouse(h);
            if (houseError.empty())
                houses.push_back(h);
            else
            {
                errorHouses.push_back(pair<string,string>(houseFileName, houseError));
            }
        }
    }

    return pair<vector<House*>,vector<pair<string,string> > >(houses, errorHouses);
}


vector<string> FileReader::ReadAlgorithms(string dirPath)
{
    string fixedDirPath = dirPath;
    if (dirPath.empty())
    {
        fixedDirPath = "./";
    }

    AlgorithmsLister algorithmsLister = AlgorithmsLister(fixedDirPath);
    vector<string> algoFileNames = algorithmsLister.getFilesList();

    if (!algoFileNames.size())
    {
        cout << usageMessage << endl;
        exit(0);
    }

    return algoFileNames;
}

House* FileReader::input(string filePath)
{
    ifstream fin(filePath);

    string name, steps, dummy;
    int rows, cols;

    fin >> name;
    getline(fin, dummy);
    fin >> steps;
    getline(fin, dummy);
    fin >> rows;
    fin >> cols;
    fin.ignore();

    House* house;
    if (rows > 0 && cols > 0)
    {
        char** hh = new char*[rows];
        for (int i = 0; i < rows; i++)
        {
            hh[i] = new char[cols];
        }

        string rowString = "";
        getline(fin, rowString);
        for (int i = 0; i < rows; i++)
        {
            rowString = "";
            getline(fin, rowString);
            strncpy(hh[i], rowString.c_str(), (size_t)cols);
        }

        house = new House(rows, cols, hh);

        for (int i = 0; i < rows; i++)
            delete [] hh[i];
        delete [] hh;

        house->name = name;
        house->maxSteps = atoi(steps.c_str());

        FileReader::fixHouse(house);
        return house;
    }

    house = new House(rows, cols);
    return house;
}

void FileReader::fixHouse(House* h)
{
    for (int i = 0; i < h->rows; i++)
    {
        for (int j = 0; j < h->columns; j++)
        {
            if (i == 0 || i == h->rows-1)
            {
                h->house[i][j] = 'W';
                continue;
            }

            if (j == 0 || j == h->columns-1)
            {
                h->house[i][j] = 'W';
//                continue;
            }

//            if (h->house[i][j] == '')
//            {
//                h->house[i][j] = ' ';
//            }
        }
    }
}

string FileReader::isValidHouse(House* h)
{
    //line OR col OR maxSteps number le zero
    if (h->rows <= 0)
        return "line number 3 in house file shall be a positive number, found: "+ to_string(h->rows);
    if (h->columns <= 0)
        return "line number 4 in house file shall be a positive number, found: "+ to_string(h->columns);
    if (h->maxSteps <= 0)
        return "line number 2 in house file shall be a positive number, found: "+ to_string(h->maxSteps);

    //# of docks
    int numOfDocks = 0;
    for (int i = 0; i < h->rows; i++)
        for (int j = 0; j < h->columns; j++)
            if (h->house[i][j] == 'D')
                numOfDocks++;

    if (numOfDocks == 0)
        return "missing docking station";
    if (numOfDocks > 1)
        return "too many docking stations";

    return "";
}

score_func* FileReader::ScoreFunction(string& path, void*& filename)
{
    if (path.empty())
		return nullptr;
	//get all .so files
	PRINT_DEBUG("Starting to load score formula");
	vector<string> scoreFiles;
	//FilesHandler::getFilesWithSuffix(path, ".so", algorithmFiles);
		scoreFiles = FileReader::GetFilesFromDir(path, "libscore_formula.so.dylib");


	//if no .so found, search in home dir
	if (scoreFiles.size() == 0){
		cout << usageMessage << endl;
		cout << "cannot find score_formula.so file in " << path << endl;
//		return SetDefaultScoreFormula(GET_WORKING_DIR(), filename);
		return nullptr;
	}

	//load handles for dynamic libs
	PRINT_DEBUG("number of score_formula.so files found: " << scoreFiles.size());

	filename = dlopen(scoreFiles.front().c_str(), RTLD_NOW);
	if (filename == nullptr)
	{
		cout << "score_formula.so exists in " << path << " but cannot be opened or is not a valid.so" << endl;
		return nullptr;
	}

//    int (*f)() = 0;
//    int *o;
//    memcpy(&o, &f, sizeof(int*));

    void* dlsim = dlsym(filename, "calc_score");
    score_func* calcScorePtr;
    memcpy(&calcScorePtr, &dlsim, sizeof(score_func *));
//	score_func* calcScorePtr = (score_func*)
	const char* dlsym_error = dlerror();
	if (dlsym_error != nullptr)  //error in dlsym
	{
		cout << "score_formula.so is a valid .so but it does not have a valid score formula " << endl;
		return nullptr;
	}
	return calcScorePtr;
}

vector<string> FileReader::GetFilesFromDir(string dirPath, string suffix)
{
    DIR *dir;
    struct dirent *ent;

    string path = dirPath;
    if (path.empty())
        path = "./";
    else if (path.back() != '/')
        path.push_back('/');

    vector<string> filesListToLoad;
    if ((dir = opendir(path.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (!strcmp(ent->d_name, ".")) continue;
            if (!strcmp(ent->d_name, "..")) continue;

            if (strstr(ent->d_name, suffix.c_str()))
            {
                //cout << "found matching file!!" << endl;
                filesListToLoad.push_back(FileReader::concatenateAbsolutePath(path, ent->d_name));
            }

            //if (endsWith(ent->d_name, suffix)){
//                cout << "found matching file!!" << endl;
//                filesListToLoad.push_back(concatenateAbsolutePath(path, ent->d_name));
//            }
        }
        closedir(dir);
    }

    else
    {
        cout << "Error: could not open directory: " <<  path << endl;
        return filesListToLoad;
    }

    sort(filesListToLoad.begin(), filesListToLoad.end());
    return filesListToLoad;
}

string FileReader::concatenateAbsolutePath(const string& dirPath, const string& fileName)
{
    if (dirPath.empty())
        return fileName;
    if (dirPath.back() == '/')
        return dirPath + fileName;
    return dirPath + "/" + fileName;
}



