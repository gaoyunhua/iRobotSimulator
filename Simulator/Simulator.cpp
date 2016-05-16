#include <iomanip>
#include <sstream>
#include "Simulator.h"
#include "FileReader.h"
#include "Cleaner.h"
#include "AlgorithmLoader.h"
//#include "_306543083_N.h"
//#include "_306543083_G.h"

void Simulator::Simulate(int argc, const char * argv[])
{
    map<string,int> config;

    string configParamPath = ParseConfigParam(argc, argv);
    config = FileReader::ReadConfig(configParamPath);

    string houseParamPath = ParseHouseParam(argc, argv);
    auto readHouses = FileReader::ReadHouses(houseParamPath);
    vector<House*> houses = readHouses.first;
    vector<pair<string,string> > errorHouses = readHouses.second;

    if (!houses.size())
    {
        cout << "All house files in target folder " + houseParamPath + " cannot be opened or are invalid:" << endl;
        for (auto& errorHouse : errorHouses)
        {
            cout << errorHouse.first + ": " + errorHouse.second << endl;
        }
        exit(0);
    }

    AlgorithmLoader& loader = AlgorithmLoader::getInstance();
    loader.loadAlgorithm("/Users/Roni/Desktop/working/lib_306543083_G.so.dylib", "_306543083_G");
    loader.loadAlgorithm("/Users/Roni/Desktop/working/lib_306543083_N.so.dylib", "_306543083_N");

    vector<unique_ptr<AbstractAlgorithm> > algorithms = loader.getAlgorithms();
    vector<string> algoNames = loader.getAlgorithmNames();

    vector<vector<int> > algosScores(algoNames.size(), vector<int>(0));

    int k = 0;
    for(House* housePtr: houses)
    {
        House& house = *housePtr;

//        vector<AbstractAlgorithm*> algorithms;

//        AbstractAlgorithm* gAlgorithm = new _306543083_G();
//        AbstractAlgorithm* algorithm = new _306543083_N();

//        algorithms.push_back(gAlgorithm);
//        algorithms.push_back(algorithm);

        vector<Cleaner> cleaners;

        for (auto& algo : algorithms)
        {
            Point* robotLocation = new Point(house.findDocking());
            House* houseCopy =  new House(house);
            Sensor* as = new Sensor(*houseCopy, *robotLocation);
            Cleaner cleaner(*algo, as, houseCopy, *robotLocation, config);
            cleaner.clean();
            cleaners.push_back(cleaner);
        }

        for (int steps = 0; steps < house.maxSteps; steps++)
        {
            for (int i = 0 ; i < cleaners.size(); i++)
            {
                cleaners[i].Step();
            }
        }

        for (int i = 0; i < cleaners.size(); i++)
        {
            algosScores[i].push_back(Score(cleaners[i].GetResult()));
        }
    }

    vector<string> results;
    unsigned long prefixLength = (15 + 10 * (houses.size() + 1));
    string prefix(prefixLength, '-');
    results.push_back(prefix);

    string header = "|             ";
    for (int i = 0; i < houses.size(); i++)
    {
        ostringstream ss;
        ss << setw( 3 ) << setfill( '0' ) << to_string(i+1);

        header += "|" + ss.str() + "      ";
    }
    header += "|AVG      |";
    results.push_back(header);

    for (int i = 0; i < algosScores.size(); i++)
    {
        string algoScoreString = i == 0 ? "|306543083_G_ " : "|306543083_N_ ";
        int algoAvg = 0;
        for (int algoscore : algosScores[i])
        {
            algoAvg += algoscore;
            ostringstream ss;
            ss << setw( 9 ) << setfill( ' ' ) << to_string(algoscore);
            algoScoreString += "|" + ss.str();
        }

        ostringstream ss;
        string avg = to_string(((float)(algoAvg)) / houses.size());
        string sortAvg = avg.substr(0, strcspn(avg.c_str(),".") + 3);
        ss << setw( 9 ) << setfill( ' ' ) << sortAvg;
        algoScoreString += "|" + ss.str() + "|";
        results.push_back(algoScoreString);
    }
    results.push_back(prefix);

    //TODO: about to finish
    //TODO: revise scoring function
    for (auto& result : results)
        cout << result << endl;

    for (auto& invalidHouse : errorHouses)
    {
        cout << invalidHouse.first + ": " + invalidHouse.second << endl;
    }

    config.clear();
}

string Simulator::ParseConfigParam(int argc, const char **argv)
{
    string ConfigParamPrefix = "-config";
    return ParseParam(ConfigParamPrefix, argc, argv);
}

string Simulator::ParseHouseParam(int argc, const char **argv)
{
    string paramPrefix = "-house_path";
    return ParseParam(paramPrefix, argc, argv);
}

string Simulator::ParseParam(string paramPrefix, int argc, const char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        string param = argv[i];
        if (param.compare(paramPrefix) == 0)
        {
            if ((i+1) <= argc)
            {
                return argv[i+1];
            }
        }
    }
    return "";
}

int Simulator::Score(CleanerResult cleanerResult)
{
    return max(0,
            2000 - ((cleanerResult.sumDirtInHouse - cleanerResult.sumDirtCollected) * 3) +
                    (cleanerResult.isBackInDocking ? 50 : -200));

}