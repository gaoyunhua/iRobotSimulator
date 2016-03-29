
#include "NaiveAlgorithm.h"
using namespace std;

void NaiveAlgorithm::setSensor(const AbstractSensor& _sensor)
{
    sensor = _sensor;
}

void NaiveAlgorithm::setConfiguration(map<string, int> _config)
{
    config = _config;
}

void NaiveAlgorithm::setHouse(House& house)
{
    currentHouse = house;
}

Direction NaiveAlgorithm::step()
{
    SensorInformation locationInfo = sensor.sense();
    return getDirection(locationInfo);
}

Direction NaiveAlgorithm::getDirection(const SensorInformation &locationInfo) const
{
    int randomIndex = rand() % 3;
    int initialRandomIndex = randomIndex - 1;

    while (randomIndex != initialRandomIndex)
    {
        if (!locationInfo.isWall[randomIndex])
            break;
        randomIndex = (randomIndex + 1) % 3;
    }

    if (randomIndex == -1)
        return Direction::Stay;

    return (Direction) randomIndex;
}
