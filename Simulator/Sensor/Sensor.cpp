
#include "Sensor.h"

SensorInformation Sensor::sense() const
{
    SensorInformation sensorInformation;
    for (int i = 0; i < 4; i++)
    {
        Point directionPoint = Point::GetPointByDirection(robotLocation, (Direction)i);
        sensorInformation.isWall[i] = house.isWall(directionPoint);
    }

    sensorInformation.dirtLevel = house.dirtLevel(robotLocation);
    return sensorInformation;
}

Sensor::~Sensor()
{
}
