
#include "_306543083_G.h"
#include "AlgorithmRegistration.h"
#include <cstdlib>
#include <string>

REGISTER_ALGORITHM (_306543083_G)
{
    return _306543083_G.uniq
}

using namespace std;

void _306543083_G::setSensor(const AbstractSensor& _sensor)
{
    sensor = &_sensor;
}

Direction _306543083_G::step()
{
    //enum class Direction {East, West, South, North, Stay};
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

Direction _306543083_G::getDirection(const SensorInformation &locationInfo)
{

//Direction {East, West, South, North, Stay};
    Direction d;
    Direction previousDirection = stepsList.size() > 0 ? stepsList.back() : Direction::West;
    if (locationInfo.dirtLevel > 0)
    {
        d = Direction::Stay;
    }
    else if (!locationInfo.isWall[(int)previousDirection])
    {
        d = previousDirection;
    }
    else if (!locationInfo.isWall[3] && previousDirection != Direction::South) {
        d = Direction::North;
    }
    else if (!locationInfo.isWall[1] && previousDirection != Direction::East) {
        d = Direction::West;
    }
    else if (!locationInfo.isWall[2] && previousDirection != Direction::North) {
        d = Direction::South;
    }
    else if (!locationInfo.isWall[0] && previousDirection != Direction::West) {
        d = Direction::East;
    }
    else
        d = Direction::Stay;


    saveStep(d);
    return d;
}

void _306543083_G::setConfiguration(map<string, int> _config)
{
    stepsLeft = 0;
    steps = 0;
//    stepsList.push_back(Direction::Stay);
}

void _306543083_G::aboutToFinish(int stepsTillFinishing)
{
    stepsLeft = stepsTillFinishing;
}

void _306543083_G::saveStep(Direction d)
{
    stepsList.push_back(d);
}
