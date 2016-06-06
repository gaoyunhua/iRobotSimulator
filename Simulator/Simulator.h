
#ifndef SIMULATOR_SIMULATOR_H
#define SIMULATOR_SIMULATOR_H

#include <string>
#include "CleanerResult.h"
#include "FileReader.h"
#include "ScoreManager.h"
#include "Cleaner.h"
#include <map>
#include "AlgorithmRegistrar.h"
#include <vector>
#include <list>
#include "Debugger.h"
#include "AbstractAlgorithm.h"
#include "my_make_unique.h"
#include <thread>
#include <atomic>
#include <functional>
#include <iomanip>
#include <sstream>


using namespace std;

class Simulator
{
public:
    void Simulate(int argc, const char * argv[]);
    void loadAlgorithms();
    list<pair<string, unique_ptr<AbstractAlgorithm> > > getLoadedAlgorithms();

    string ParseConfigParam(int argc, const char **argv);
    string ParseHouseParam(int argc, const char **argv);
    string ParseScoreParam(int argc, const char **argv);
    int ParseThreadsParam(int argc, const char **argv);
    string ParseAlgorithmPathParam(int argc, const char **argv);
    string ParseParam(string paramPrefix, int argc, const char* argv[]);
    void runSingleSubSimulationThread(atomic_size_t *house_shared_counter);
    ~Simulator();

private:
    void ReadParams(int argc, const char * argv[]);
    vector<House*> houses;
    vector<string> algorithmFiles;
    vector<pair<string,string> > errorHouses;
    score_func* calcScorePtr;
    map<string,int> config;
    int threads;
    int calcScore(const CleanerResult &cleanerResult, int winnerNumSteps, int loserPosition) const;
    void printResults(bool withScoreTable);
    string algorithmsPath;
    ScoreManager* scoreManager;
    void runCompetitionOnHouse(int houseIndex);

    void runSimulation(int threadsCount);


};


#endif
