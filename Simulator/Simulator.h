
#ifndef SIMULATOR_SIMULATOR_H
#define SIMULATOR_SIMULATOR_H


#include "CleanerResult.h"

class Simulator
{
public:
    void Simulate(int argc, const char * argv[]);
    int score(CleanerResult cleanerResult);
};


#endif //SIMULATOR_SIMULATOR_H
