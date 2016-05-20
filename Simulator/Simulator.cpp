#include <iomanip>
#include <sstream>
#include "Simulator.h"
#include "FileReader.h"
#include "Cleaner.h"
#include "AlgorithmLoader.h"
#include "_306543083_N.h"
#include "_306543083_G.h"
#include <map>

extern "C" int calc_score(const std::map<std::string, int>& score_params);

void Simulator::Simulate(int argc, const char * argv[])
{
    string configParamPath = ParseConfigParam(argc, argv);
    config = FileReader::ReadConfig(configParamPath);

    string houseParamPath = ParseHouseParam(argc, argv);
    string scoreFuncPath = ParseScoreParam(argc, argv);//"/Users/Roni/Desktop/working/";
    string algosPath = ParseAlgorithmPathParam(argc, argv);
    //TODO:ADD score param rad


    auto readHouses = FileReader::ReadHouses(houseParamPath);
    vector<House*> houses = readHouses.first;
    errorHouses = readHouses.second;

    if (!houses.size())
    {
        cout << "All house files in target folder " + houseParamPath + " cannot be opened or are invalid:" << endl;
        for (auto& errorHouse : errorHouses)
        {
            cout << errorHouse.first + ": " + errorHouse.second << endl;
        }
        exit(0);
    }

//    AlgorithmLoader& loader = AlgorithmLoader::getInstance();
//    loader.loadAlgorithm("/Users/Roni/Desktop/working/lib_306543083_G.so.dylib", "_306543083_G");
//    loader.loadAlgorithm("/Users/Roni/Desktop/working/lib_306543083_N.so.dylib", "_306543083_N");
//
//    vector<unique_ptr<AbstractAlgorithm> > algorithms = loader.getAlgorithms();
//    vector<string> algoNames = loader.getAlgorithmNames();


    void* filename = nullptr;
    calcScorePtr = FileReader::ScoreFunction(scoreFuncPath, filename);
    calcScorePtr = calc_score;
    if (calcScorePtr == nullptr)
    {
        calcScorePtr = calc_score;
    }

    int algosCount = 2;


    scoreManager = new ScoreManager();

    for(House* housePtr: houses)
    {
        House& house = *housePtr;
        runSimulationOnHouse(house);
    }

    printResults();

    config.clear();
    delete scoreManager;
}

void Simulator::printResults()
{
//    vector<string> results;
//    int prefixLength = (15 + 10 * (housesCount + 1));
//    string prefix(prefixLength, '-');
//    results.push_back(prefix);
//
//    string header = "|             ";
//    for (int i = 0; i < housesCount; i++)
//    {
//        ostringstream ss;
//        ss << setw( 3 ) << setfill( '0' ) << to_string(i+1);
//
//        header += "|" + ss.str() + "      ";
//    }
//    header += "|AVG      |";
//    results.push_back(header);
//
////    map<string, int> a = scoreManager->scores.at("_306543083_G");
//
//    map<string, map<string, int>>::iterator aitr = scoreManager->scores.begin();
//
//    int numOfHouses = (int) aitr->second.size();
//
//    for (int i = 0; i < numOfHouses; i++)
//    {
//        scoreManager->sc
//        string algoScoreString = i == 0 ? "|306543083_G_ " : "|306543083_N_ ";
//        int algoAvg = 0;
//        for (int algoscore : algosScores[i])
//        {
//            algoAvg += algoscore;
//            ostringstream ss;
//            ss << setw( 9 ) << setfill( ' ' ) << to_string(algoscore);
//            algoScoreString += "|" + ss.str();
//        }
//
//        ostringstream ss;
//        string avg = to_string(((float)(algoAvg)) / housesCount);
//        string sortAvg = avg.substr(0, strcspn(avg.c_str(),".") + 3);
//        ss << setw( 9 ) << setfill( ' ' ) << sortAvg;
//        algoScoreString += "|" + ss.str() + "|";
//        results.push_back(algoScoreString);
//    }
//    results.push_back(prefix);
//
//    //TODO: about to finish
//    //TODO: revise scoring function
//    for (auto& result : results)
//        cout << result << endl;

    scoreManager->printScoreTable();
    for (auto& invalidHouse : errorHouses)
    {
        string msg = invalidHouse.first + (invalidHouse.second.empty() ? "" : ": " + invalidHouse.second);
        cout << msg << endl;
    }
}

void Simulator::runSimulationOnHouse(House& house)
{
    vector<Cleaner> cleaners;

    vector<AbstractAlgorithm*> algorithms;

    AbstractAlgorithm* gAlgorithm = new _306543083_G();
    AbstractAlgorithm* algorithm = new _306543083_N();

    algorithms.push_back(gAlgorithm);
    algorithms.push_back(algorithm);

    for (auto& algo : algorithms)
    {
        Point* robotLocation = new Point(house.findDocking());
        House* houseCopy =  new House(house);
        Sensor* as = new Sensor(*houseCopy, *robotLocation);
        Cleaner cleaner(*algo, as, houseCopy, *robotLocation, config, "_306543083_X");
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
        //TODO:int winnerNumSteps, int loserPosition
        int score  = calcScore(cleaners[i].GetResult(), 0, 0);
        if (score == -1)
        {
            errorHouses.push_back(pair<string,string>("Score formula could not calculate some scores, see -1 in the results table", ""));
        }

        scoreManager->addScore(cleaners[i].algorithmName, cleaners[i].getHouseName(), score);
    }
}

string Simulator::ParseConfigParam(int argc, const char **argv)
{
    string paramPrefix = "-config";
    return ParseParam(paramPrefix, argc, argv);
}

string Simulator::ParseAlgorithmPathParam(int argc, const char **argv)
{
    string paramPrefix = "-algorithm_path";
    return ParseParam(paramPrefix, argc, argv);
}

string Simulator::ParseScoreParam(int argc, const char **argv)
{
    string paramPrefix = "-score";
    return ParseParam(paramPrefix, argc, argv);
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

//updates score_params with values
int Simulator::calcScore(const CleanerResult& simStats, int winnerNumSteps, int loserPosition) const
{
    map<string, int> score_params;

    score_params["actual_position_in_competition"] = simStats.getActualPosition(loserPosition);
    score_params["winner_num_steps"] = winnerNumSteps;
    score_params["this_num_steps"] = simStats.numOfSteps;
    score_params["sum_dirt_in_house"] = simStats.sumDirtInHouse;
    score_params["dirt_collected"] = simStats.sumDirtCollected;
    score_params["is_back_in_docking"] = simStats.isBackInDocking;

    return calcScorePtr(score_params);
}