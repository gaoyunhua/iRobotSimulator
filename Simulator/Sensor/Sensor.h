
#ifndef SIMULATOR_SENSOR_H
#define SIMULATOR_SENSOR_H


#include "AbstractSensor.h"
#include "House.h"

class Sensor : public AbstractSensor
{
    House& house;

public:
    SensorInformation sense();
    ~Sensor();
    void setHouse(House& _house);
};


#endif //SIMULATOR_SENSOR_H
