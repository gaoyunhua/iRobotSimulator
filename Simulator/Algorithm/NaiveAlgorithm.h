
#ifndef SIMULATOR_NAIVEALGORITHM_H
#define SIMULATOR_NAIVEALGORITHM_H


#include "AbstractAlgorithm.h"
#include "House.h"
#include "Sensor.h"

class NaiveAlgorithm : public AbstractAlgorithm
{
    House currentHouse;
    AbstractSensor& sensor;
    map<string, int> config;

public:
    void setSensor(const AbstractSensor &sensor);
    void setConfiguration(map<string, int> config);
    Direction step();

    void setHouse(House& house);
    Direction getDirection(const SensorInformation &locationInfo) const;
};


#endif //SIMULATOR_NAIVEALGORITHM_H
