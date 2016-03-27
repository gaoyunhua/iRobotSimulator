
#ifndef SIMULATOR_NAIVEALGORITHM_H
#define SIMULATOR_NAIVEALGORITHM_H


#include "AbstractAlgorithm.h"

class NaiveAlgorithm : AbstractAlgorithm
{

public:
    void setSensor(const AbstractSensor &sensor);
    void setConfiguration(map<string, int> config);
    Direction step();
};


#endif //SIMULATOR_NAIVEALGORITHM_H
