
#ifndef SIMULATOR_SENSOR_H
#define SIMULATOR_SENSOR_H


#include "AbstractSensor.h"
#include "House.h"

class Sensor : public AbstractSensor
{
    House& house;
    Point& robotLocation;

public:
    Sensor(House& _house, Point& _robotLocation) : house(_house), robotLocation(_robotLocation){}
    SensorInformation sense() const;
    ~Sensor();
};


#endif //SIMULATOR_SENSOR_H
