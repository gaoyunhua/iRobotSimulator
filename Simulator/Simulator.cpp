#include <iomanip>
#include <sstream>
#include "Simulator.h"
#include "Cleaner.h"
#include "AlgorithmRegistrar.h"
#include <vector>
#include <list>
#include "Debugger.h"
#include "AbstractAlgorithm.h"
#include "my_make_unique.h"
#include <thread>
#include <atomic>
#include <functional>

extern "C" int calc_score(const std::map<std::string, int>& score_params);

void Simulator::Simulate(int argc, const char * argv[])
{
    PRINT_DEBUG("Reading Params");
    ReadParams(argc, argv);
    scoreManager = new ScoreManager();
    runSimulation(threads);
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

void Simulator::runCompetitionOnHouse(int houseIndex)
{
    House& house = *houses[houseIndex];
    vector<unique_ptr<Cleaner>> cleaners;
    list<pair<string, unique_ptr<AbstractAlgorithm> > >algorithms = loadAlgorithms();

    PRINT_DEBUG("Done fetching Algos");
    for (auto& algo : algorithms)
    {
        Point* robotLocation = new Point(house.findDocking());
        House* houseCopy =  new House(house);
        Sensor* as = new Sensor(*houseCopy, *robotLocation);
        PRINT_DEBUG("Building Cleaner");

        cleaners.push_back(make_unique<Cleaner>(algo.second, as, houseCopy, *robotLocation, config, algo.first));
        PRINT_DEBUG("Storing cleaner");
    }

    for (auto& c : cleaners) {
        c->clean();
        PRINT_DEBUG("Cleaner Ready");
    }


    bool allDone = false;
    bool someoneDone = false;
    int winnerNumSteps = 0;
    int simulationSteps = 0;
    int stepLeftInSimulation = cleaners[0]->getHouseMaxSteps() - 1;
    list< map<Cleaner, int> > positions;
    int currPosition = 1;

    while (!allDone && simulationSteps <= stepLeftInSimulation){
        //loop ends only when all sims are done
        allDone = true;
        int simsDoneInStep = 0;
        for (auto& cleaner : cleaners){
            cleaner->Step();

            //if sim is not done yet
            if (!(cleaner->isDone())){
                allDone = false;	//if at least one sim hasn't finished -> allDone = false
                //sim->makeStep();
            }

            else{	//this simulation is done
                PRINT_DEBUG("sim for algorithm: " << cleaner->algorithmName << " done");
                //if the simulation finished in this round and house is clean
                if ( cleaner->getDidFinishCleaning() && cleaner->isRobotAtDock() ){
                    PRINT_DEBUG("algorithm: " << cleaner->algorithmName << " finishing for first time");
                    //this is the first simulation to finish
                    if (!someoneDone){
                        PRINT_DEBUG("first winner!! on step: " << cleaner->steps);
                        someoneDone = true;
                        winnerNumSteps = cleaner->steps;

                        //signal all sims first algo has finished
                        for (auto& remainingCleaner : cleaners){
                            //this sim has already done a step in this round
                            if (remainingCleaner->steps > simulationSteps)
                                remainingCleaner->aboutToFinish(config["MaxStepsAfterWinner"] - 1);
                            else
                                remainingCleaner->aboutToFinish(config["MaxStepsAfterWinner"]);
                        }

                        //update simulation stoping condition
                        stepLeftInSimulation = simulationSteps + config["MaxStepsAfterWinner"];
                    }
                    simsDoneInStep++;
                    cleaner->setPosition(currPosition);
                }
            }
        }
        currPosition += simsDoneInStep;
        simulationSteps++;
    }

    //if no one finished cleaning the house
    if (!someoneDone)
        winnerNumSteps = simulationSteps;

//    calculateCleanerResult(cleaners, winnerNumSteps, currPosition);

    for (int i = 0; i < (int)cleaners.size(); i++)
    {
        //TODO:loserPosition
        int score  = calcScore(cleaners[i]->GetResult(), winnerNumSteps,0);
        if (score == -1)
        {
            errorHouses.push_back(
                    pair<string,string>("Score formula could not calculate some scores, see -1 in the results table", ""));
        }

        scoreManager->addScore(cleaners[i]->algorithmName, cleaners[i]->getHouseName(), score);
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

int Simulator::ParseThreadsParam(int argc, const char **argv)
{
    string paramPrefix = "-threads";
    string threadsParam = ParseParam(paramPrefix, argc, argv);
    if (threadsParam.empty())
        return 1;
    return atoi(threadsParam);
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
    algorithmsPath = ParseAlgorithmPathParam(argc, argv);
//    algorithmFiles = FileReader::ReadAlgorithms(algorithmsPath);
    threads = ParseThreadsParam(argc, argv);

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
    config.clear();
    delete scoreManager;
}

list<pair<string, unique_ptr<AbstractAlgorithm> > > Simulator::loadAlgorithms()
{
    PRINT_DEBUG("Loading Algorithms");
    list<pair<string, unique_ptr<AbstractAlgorithm> > >algorithms;
    AlgorithmRegistrar& registrar = AlgorithmRegistrar::getInstance();

    for (auto algoName : algorithmFiles)
    {
        size_t startIndex = algoName.rfind('/');
        string pref = algoName.substr(startIndex+1, 13);
        //TODO:Remove Debug load
//        registrar.loadDebugAlgorithm(algoName, pref);
        //if (REGISTERed)
//        errorHouses.push_back(
//                pair<string,string>("Algorithm Load Failed", ""));
    }

    //TODO:Remove
    registrar.loadDebugAlgorithm("", "");

    PRINT_DEBUG("Getting Algos");
    list<unique_ptr<AbstractAlgorithm> > algorithmPointers = registrar.getAlgorithms();
    PRINT_DEBUG("Got " + to_string(algorithmPointers.size()));

    vector<string> algoNames = registrar.getAlgorithmNames();

    if (algorithmPointers.size() == 0)
    {
        cout << "All algorithm files in target folder " + algorithmsPath +  "cannot be opened or are invalid:" << endl;
        exit(0);
    }

    int i = 0;
    for (auto& a : algorithmPointers)
    {
        PRINT_DEBUG("Storing Algo Pointer");
        algorithms.push_back(pair<string,unique_ptr<AbstractAlgorithm>>(algoNames[i], std::move(a)));
        i++;
    }
    PRINT_DEBUG("Done");
    return algorithms;
}

void Simulator::runSingleSubSimulationThread(atomic_size_t* house_shared_counter)
{
    for(size_t index = (*house_shared_counter)++; index < houses.size(); index = (*house_shared_counter)++)
    {
        if (DEBUG)
        {
            cout << "Thread:" << this_thread::get_id() << " running on House:" << index << endl;
        }
        runCompetitionOnHouse((int) index);
    }
}

void Simulator::runSimulation(int threadsCount)
{
    int actualThreadsCount = threadsCount;
    int houseCount = (int) houses.size();
    if (houseCount < threadsCount)
    {
        actualThreadsCount = houseCount;
    }
    if (actualThreadsCount == 1)
    {
        for (vector<House*>::iterator it = houses.begin(); it != houses.end(); ++it)
        {
            runCompetitionOnHouse((int) (it - houses.begin()));
        }
    }
    else
    {
        atomic_size_t workingHouseIndex{0};
        PRINT_DEBUG("Running on " + to_string(actualThreadsCount) + " threads");

        vector<unique_ptr<thread>> threads((unsigned long) actualThreadsCount);
        for(auto& thread_ptr : threads)
        {
            thread_ptr = make_unique<thread>(&Simulator::runSingleSubSimulationThread, this, &workingHouseIndex);
        }

        for(auto& thread_ptr : threads)
        {
            thread_ptr->join();
        }
    }
}
