
#include <cstdlib>
#include "NaiveAlgorithm.h"
using namespace std;

void NaiveAlgorithm::setSensor(const AbstractSensor& _sensor)
{
    sensor = _sensor;
}

Direction NaiveAlgorithm::step()
{
    SensorInformation locationInfo = sensor.sense();
    return getDirection(locationInfo);
}

Direction NaiveAlgorithm::getDirection(const SensorInformation &locationInfo) const
{
    int randomInt = rand();
    int randomIndex = randomInt % 4;
    int initialRandomIndex = randomIndex - 1;

    while (randomIndex != initialRandomIndex)
    {
        if (!locationInfo.isWall[randomIndex])
            break;
        randomIndex = (randomIndex + 1);
        if (randomIndex >=4)
            randomIndex = 0;
    }

    return (Direction) randomIndex;
}

void NaiveAlgorithm::setConfiguration(map<string, int> _config)
{
}

void NaiveAlgorithm::aboutToFinish(int stepsTillFinishing)
{
}
