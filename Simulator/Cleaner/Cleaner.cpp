
#include "Cleaner.h"

CleanerResult Cleaner::clean()
{
    int steps = 0;
    int dirtCleaned = 0;
    int sumOfDirt = house.amountOfDirt();

    int maxSteps = configuration.at("MaxSteps");
    int batteryLevel = configuration.at("BatteryCapacity");

    int rechargeRate = configuration.at("BatteryRechargeRate");

    algorithm.setConfiguration(configuration);
    algorithm.setSensor(sensor);

    while (steps <= maxSteps)
    {
        Direction moveDirection = algorithm.step();
        if ((int)moveDirection == 4)
        {
            return stopSimulation();
        }

        Point newRobotLocation = Point::GetPointByDirection(robotLocation, moveDirection);
        if (newRobotLocation.equals(house.findDocking()))
        {
            robotAtDock(rechargeRate, newRobotLocation, steps, batteryLevel);
            continue;
        }

        if (batteryLevel <= 0)
        {
            break;
        }

        robotLocation.move(moveDirection);
        performStep(steps, dirtCleaned, batteryLevel);
        steps++;

        if (dirtCleaned == sumOfDirt)
        {
            TryReturnToDockFromPoint(robotLocation);
            return CleanerResult(steps, sumOfDirt, dirtCleaned, robotLocation.equals(house.findDocking()));
        }
    }

    return CleanerResult(steps, sumOfDirt, dirtCleaned, robotLocation.equals(house.findDocking()));
}

void Cleaner::performStep(int &steps, int &dirtCleaned, int &batteryLevel)
{
    dirtCleaned += house.cleanOneUnit(robotLocation);

    int batteryConsumptionPerMove = configuration.at("BatteryConsumptionRate");
    batteryLevel = max(0, batteryLevel - batteryConsumptionPerMove);
}

void Cleaner::robotAtDock(int rechargeRate,Point &newRobotLocation, int &steps, int &batteryLevel)
{
    int capacity = configuration.at("BatteryCapacity");
    batteryLevel = min(capacity, batteryLevel + rechargeRate);
    steps++;
    robotLocation.move(newRobotLocation);
}

CleanerResult Cleaner::stopSimulation()
{
    return CleanerResult();
}

void Cleaner::TryReturnToDockFromPoint(Point point)
{
}