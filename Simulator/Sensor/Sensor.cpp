
#include "Sensor.h"

SensorInformation Sensor::sense()
{
    Point robotLocation = house.findRobot();

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

void Sensor::setHouse(House &_house)
{
    house = _house;
}
