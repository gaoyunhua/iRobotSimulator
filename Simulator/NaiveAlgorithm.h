
#ifndef SIMULATOR_NAIVEALGORITHM_H
#define SIMULATOR_NAIVEALGORITHM_H

#include "AbstractAlgorithm.h"
#include "House.h"
#include "Sensor.h"
#include "AbstractSensor.h"

class NaiveAlgorithm : public AbstractAlgorithm
{
    AbstractSensor& sensor;

public:
    NaiveAlgorithm(AbstractSensor& _sensor) : sensor(_sensor){}

    virtual void setSensor(const AbstractSensor& sensor);
    virtual Direction step();
    virtual void setConfiguration(map<string, int> config);
    virtual void aboutToFinish(int stepsTillFinishing);
    virtual Direction getDirection(const SensorInformation &locationInfo) const;
    virtual ~NaiveAlgorithm() {}
};


#endif //SIMULATOR_NAIVEALGORITHM_H
