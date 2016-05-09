
#ifndef SIMULATOR_NAIVEALGORITHM_H
#define SIMULATOR_NAIVEALGORITHM_H

#include <vector>
#include "AbstractAlgorithm.h"
#include "House.h"
#include "AbstractSensor.h"

class NaiveAlgorithm : public AbstractAlgorithm
{
    const AbstractSensor* sensor;

private:
    vector<Direction> stepsList;
    void saveStep(Direction d);
    int stepsLeft;
    int steps;

public:
    virtual void setSensor(const AbstractSensor& sensor);
    virtual Direction step();
    virtual void setConfiguration(map<string, int> config);
    virtual void aboutToFinish(int stepsTillFinishing);
    virtual Direction getDirection(const SensorInformation &locationInfo);
    virtual ~NaiveAlgorithm() {}
};


#endif //SIMULATOR_NAIVEALGORITHM_H
