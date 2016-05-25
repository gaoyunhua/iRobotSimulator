
#ifndef SIMULATOR_SIMULATOR_H
#define SIMULATOR_SIMULATOR_H

#include <string>
#import "CleanerResult.h"
#include "FileReader.h"
#include "ScoreManager.h"
#include "Cleaner.h"
#include <map>


using namespace std;

class Simulator
{
public:
    void Simulate(int argc, const char * argv[]);
    void runSimulationOnHouse(House& house);
    vector<pair<string, AbstractAlgorithm* > > loadAlgorithms();
    string ParseConfigParam(int argc, const char **argv);
    string ParseHouseParam(int argc, const char **argv);
    string ParseScoreParam(int argc, const char **argv);
    string ParseAlgorithmPathParam(int argc, const char **argv);
    string ParseParam(string paramPrefix, int argc, const char* argv[]);
    ~Simulator();

private:
    void ReadParams(int argc, const char * argv[]);
    vector<House*> houses;
    vector<pair<string,string> > errorHouses;
    score_func* calcScorePtr;
    map<string,int> config;
    int calcScore(const CleanerResult &simStats, int winnerNumSteps, int loserPosition) const;
    void printResults();

    ScoreManager* scoreManager;

    void runCompetitionOnHouse(House& house, vector<Cleaner>& cleaners);

    void calculateCleanerResult(const vector<Cleaner> &cleaners, int winnerNumSteps, int loserPosition);
};


#endif
