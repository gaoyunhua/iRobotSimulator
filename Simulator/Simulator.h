
#ifndef SIMULATOR_SIMULATOR_H
#define SIMULATOR_SIMULATOR_H

#include <string>
#import "CleanerResult.h"
#include "FileReader.h"
#include "ScoreManager.h"
#include <map>


using namespace std;

class Simulator
{
public:
    void Simulate(int argc, const char * argv[]);
    void runSimulationOnHouse(House& house);
    string ParseConfigParam(int argc, const char **argv);
    string ParseHouseParam(int argc, const char **argv);
    string ParseScoreParam(int argc, const char **argv);
    string ParseAlgorithmPathParam(int argc, const char **argv);
    string ParseParam(string paramPrefix, int argc, const char* argv[]);

private:
    vector<pair<string,string> > errorHouses;
    score_func* calcScorePtr;
    map<string,int> config;
    int calcScore(const CleanerResult &simStats, int winnerNumSteps, int loserPosition) const;
    void printResults();

    ScoreManager* scoreManager;
};


#endif
