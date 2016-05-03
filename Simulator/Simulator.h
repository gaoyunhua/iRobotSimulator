
#ifndef SIMULATOR_SIMULATOR_H
#define SIMULATOR_SIMULATOR_H

#include <string>
#import "CleanerResult.h"

using namespace std;

class Simulator
{
public:
    void Simulate(int argc, const char * argv[]);
    int Score(CleanerResult cleanerResult);
    string ParseConfigParam(int argc, const char **argv);
    string ParseHouseParam(int argc, const char **argv);
    string ParseParam(string paramPrefix, int argc, const char* argv[]);
};


#endif
