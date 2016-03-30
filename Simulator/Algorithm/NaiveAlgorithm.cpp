
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
    int randomIndex = randomInt % 3;
    int initialRandomIndex = randomIndex - 1;

    while (randomIndex != initialRandomIndex)
    {
        if (!locationInfo.isWall[randomIndex])
            break;
        randomIndex = (randomIndex + 1) % 3;
    }

    if (randomIndex == -1 || locationInfo.isWall[randomIndex])
        return Direction::Error;

    return (Direction) randomIndex;
}

void NaiveAlgorithm::setConfiguration(map<string, int> _config)
{
}

void NaiveAlgorithm::aboutToFinish(int stepsTillFinishing)
{
}
