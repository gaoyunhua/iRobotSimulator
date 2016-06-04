
#ifndef SIMULATOR_NAIVEALGORITHM_H
#define SIMULATOR_NAIVEALGORITHM_H

#include <vector>
#include "AbstractAlgorithm.h"
#include "AbstractSensor.h"
#include "AlgorithmRegistration.h"
#include "my_make_unique.h"

class _306543083_N : public AbstractAlgorithm
{
    const AbstractSensor* sensor;

private:
    vector<Direction> stepsList;
    void saveStep(Direction d);
    int stepsLeft;
    int steps;

public:
    _306543083_N();
    void setSensor(const AbstractSensor& sensor);
    Direction step();
    void setConfiguration(map<string, int> config);
    void aboutToFinish(int stepsTillFinishing);
    Direction getDirection(const SensorInformation &locationInfo);
    ~_306543083_N() {}
};


#endif //SIMULATOR_NAIVEALGORITHM_H
