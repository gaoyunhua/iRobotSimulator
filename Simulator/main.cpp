
#include "Simulator.h"
#include "AlgorithmLoader.h"

int main(int argc, const char * argv[]) {

    AlgorithmLoader::getInstance();

    Simulator simulator;
    simulator.Simulate(argc, argv);
    return 0;
}