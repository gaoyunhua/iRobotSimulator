
#ifndef SIMULATOR_SENSOR_H
#define SIMULATOR_SENSOR_H


#include "AbstractSensor.h"

class Sensor : AbstractSensor
{
    virtual SensorInformation sense();
};


#endif //SIMULATOR_SENSOR_H
