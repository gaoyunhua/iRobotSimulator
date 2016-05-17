
#ifndef SIMULATOR_SIMULATOR_H
#define SIMULATOR_SIMULATOR_H

#include <string>
#import "CleanerResult.h"
#include "FileReader.h"



using namespace std;

class Simulator
{
public:
    void Simulate(int argc, const char * argv[]);
    void runSimulationOnHouse(House& house);
//    int Score(CleanerResult cleanerResult);
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
};


#endif
