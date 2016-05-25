#include <iomanip>
#include <sstream>
#include "Simulator.h"
#include "FileReader.h"
#include "Cleaner.h"
#include "AlgorithmLoader.h"
//#include "_306543083_N.h"
//#include "_306543083_G.h"
#include <map>
#include <list>
#include "Debugger.h"

extern "C" int calc_score(const std::map<std::string, int>& score_params);

void Simulator::Simulate(int argc, const char * argv[])
{
    ReadParams(argc, argv);
    int algosCount = 2;

    scoreManager = new ScoreManager();

    for(House* housePtr: houses)
    {
        House& house = *housePtr;
        runSimulationOnHouse(house);
    }

    printResults();
}

void Simulator::printResults()
{
    scoreManager->printScoreTable();
    for (auto& invalidHouse : errorHouses)
    {
        string msg = invalidHouse.first + (invalidHouse.second.empty() ? "" : ": " + invalidHouse.second);
        cout << msg << endl;
    }
}

vector<pair<string, AbstractAlgorithm*> > Simulator::loadAlgorithms()
{
    vector<pair<string, AbstractAlgorithm* > >algorithms;
//    AbstractAlgorithm* gAlgorithm = new _306543083_G();
//    AbstractAlgorithm* algorithm = new _306543083_N();
//    algorithms.push_back(pair<string, AbstractAlgorithm*> ("_306543083_G", gAlgorithm));
//    algorithms.push_back(pair<string, AbstractAlgorithm*> ("_306543083_N", algorithm));
//
//    return algorithms;

    AlgorithmLoader::getInstance().loadAlgorithm("/Users/Roni/Desktop/working/lib_306543083_G.so.dylib", "_306543083_G");
    AlgorithmLoader::getInstance().loadAlgorithm("/Users/Roni/Desktop/working/lib_306543083_N.so.dylib", "_306543083_N");

    vector<unique_ptr<AbstractAlgorithm> > algorithmPointers = AlgorithmLoader::getInstance().getAlgorithms();
    vector<string> algoNames = AlgorithmLoader::getInstance().getAlgorithmNames();

    if (algorithmPointers.size() == 0)
    {
        cout << "No algorithms loaded";
        exit(0);
    }

    for (int i = 0; i < algorithmPointers.size(); i++)
    {
        AbstractAlgorithm* a = algorithmPointers[i].get();
        algorithms.push_back(pair<string, AbstractAlgorithm* >(algoNames[i], a));
    }

    return algorithms;
}

void Simulator::runSimulationOnHouse(House& house)
{
    vector<Cleaner> cleaners;
    vector<pair<string, AbstractAlgorithm*> >algorithms = loadAlgorithms();
    for (auto& algo : algorithms)
    {
        Point* robotLocation = new Point(house.findDocking());
        House* houseCopy =  new House(house);
        Sensor* as = new Sensor(*houseCopy, *robotLocation);
        Cleaner cleaner(*(algo.second), as, houseCopy, *robotLocation, config, algo.first);
        cleaner.clean();
        cleaners.push_back(cleaner);
    }

    runCompetitionOnHouse(house, cleaners);
}

void Simulator::runCompetitionOnHouse(House& house, vector<Cleaner>& cleaners)
{
    bool allDone = false;
    bool someoneDone = false;
    int winnerNumSteps = 0;
    int simulationSteps = 0;
    int stepLeftInSimulation = cleaners[0].getHouseMaxSteps() - 1;
    list< map<Cleaner, int> > positions;
    int currPosition = 1;

    while (!allDone && simulationSteps <= stepLeftInSimulation){
        //loop ends only when all sims are done
        allDone = true;
        int simsDoneInStep = 0;
        for (auto& cleaner : cleaners){
            cleaner.Step();

            //if sim is not done yet
            if (!(cleaner.isDone())){
                allDone = false;	//if at least one sim hasn't finished -> allDone = false
                //sim->makeStep();
            }

            else{	//this simulation is done
                PRINT_DEBUG("sim for algorithm: " << cleaner.algorithmName << " done");
                //if the simulation finished in this round and house is clean
                if ( cleaner.getDidFinishCleaning() && cleaner.isRobotAtDock() ){
                    PRINT_DEBUG("algorithm: " << cleaner.algorithmName << " finishing for first time");
                    //this is the first simulation to finish
                    if (!someoneDone){
                        PRINT_DEBUG("first winner!! on step: " << cleaner.steps);
                        someoneDone = true;
                        winnerNumSteps = cleaner.steps;

                        //signal all sims first algo has finished
                        for (auto& remainingCleaner : cleaners){
                            //this sim has already done a step in this round
                            if (remainingCleaner.steps > simulationSteps)
                                remainingCleaner.aboutToFinish(config["MaxStepsAfterWinner"] - 1);
                            else
                                remainingCleaner.aboutToFinish(config["MaxStepsAfterWinner"]);
                        }

                        //update simulation stoping condition
                        stepLeftInSimulation = simulationSteps + config["MaxStepsAfterWinner"];
                    }
                    simsDoneInStep++;
                    cleaner.setPosition(currPosition);
                }
            }
        }
        currPosition += simsDoneInStep;
        simulationSteps++;
    }

    //if no one finished cleaning the house
    if (!someoneDone)
        winnerNumSteps = simulationSteps;

    calculateCleanerResult(cleaners, winnerNumSteps, currPosition);
}

void Simulator::calculateCleanerResult(const vector<Cleaner> &cleaners, int winnerNumSteps, int loserPosition)
{
    for (int i = 0; i < cleaners.size(); i++)
    {
        //TODO:int winnerNumSteps, int loserPosition
        int score  = calcScore(cleaners[i].GetResult(), 0, 0);
        if (score == -1)
        {
            errorHouses.push_back(
                    pair<string,string>("Score formula could not calculate some scores, see -1 in the results table", ""));
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

void Simulator::ReadParams(int argc, const char * argv[])
{
    string configParamPath = ParseConfigParam(argc, argv);
    config = FileReader::ReadConfig(configParamPath);

    string houseParamPath = ParseHouseParam(argc, argv);
    string scoreFuncPath = ParseScoreParam(argc, argv);//"/Users/Roni/Desktop/working/";
    string algosPath = ParseAlgorithmPathParam(argc, argv);

    auto readHouses = FileReader::ReadHouses(houseParamPath);
    houses = readHouses.first;
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

    void* filename = nullptr;
    calcScorePtr = FileReader::ScoreFunction(scoreFuncPath, filename);
    calcScorePtr = calc_score;
    if (calcScorePtr == nullptr)
    {
        calcScorePtr = calc_score;
    }
}

Simulator::~Simulator()
{
//    config.clear();
    config.clear();
    delete scoreManager;
//    delete houses;
//    delete errorHouses;
//    delete(calcScorePtr);
}



