
#include "_306543083_N.h"
#include <cstdlib>
#include <string>
#include "AlgorithmRegistration.h"

using namespace std;

unique_ptr<AbstractAlgorithm> _306543083_N::make_unique()
{
    return unique_ptr<_306543083_N>(new _306543083_N());
}

void _306543083_N::setSensor(const AbstractSensor& _sensor)
{
    sensor = &_sensor;
}

Direction _306543083_N::step()
{
    SensorInformation locationInfo = sensor->sense();
    steps++;
    stepsLeft--;
    if (stepsLeft > 0)
    {
        if (!stepsList.size())
            return Direction::Stay;

        Direction d = stepsList.back();
        stepsList.pop_back();
        if (d == Direction::Stay)
        {
            while (d == Direction::Stay && stepsList.size() > 0)
            {
                d = stepsList.back();
                stepsList.pop_back();
            }
        }

        if (d == Direction::Stay)
            return d;
        if (d == Direction::East)
            return Direction::West;
        if (d == Direction::West)
            return Direction::East;
        if (d == Direction::North)
            return Direction::South;
        return Direction::North;
    }

    return getDirection(locationInfo);
}

Direction _306543083_N::getDirection(const SensorInformation &locationInfo)
{

//Direction {East, West, South, North, Stay};
    Direction d;
    if (locationInfo.dirtLevel > 0)
        d = Direction::Stay;
    else if (!locationInfo.isWall[3] && stepsList.back() != Direction::South)
        d = Direction::North;
    else if (!locationInfo.isWall[1] && stepsList.back() != Direction::East)
        d =  Direction::West;
    else if (!locationInfo.isWall[2] && stepsList.back() != Direction::North)
        d = Direction::South;
    else if (!locationInfo.isWall[0] && stepsList.back() != Direction::West)
        d = Direction::East;
    else
        d = Direction::Stay;

    saveStep(d);
    return d;
}

void _306543083_N::setConfiguration(map<string, int> _config)
{
    stepsLeft = 0;
    steps = 0;
    stepsList.push_back(Direction::Stay);
}

void _306543083_N::aboutToFinish(int stepsTillFinishing)
{
    stepsLeft = stepsTillFinishing;
}

void _306543083_N::saveStep(Direction d)
{
    stepsList.push_back(d);
}

REGISTER_ALGORITHM(_306543083_N)