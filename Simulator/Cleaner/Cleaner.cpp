
#include "Cleaner.h"

CleanerResult Cleaner::clean()
{
    //Robot starts at Docking point.
    //Start Cleaning
    int steps = 0;
    int dirtCleaned = 0;
    int sumOfDirt = house.amountOfDirt();

    int maxSteps = configuration.at("MaxSteps");
    int batteryLevel = configuration.at("BatteryCapacity");

    int rechargeRate = configuration.at("BatteryRechargeRate");

    algorithm.setConfiguration(configuration);
//    sensor.setHouse(house);
    algorithm.setSensor(sensor);

    Point robotLocation = house.findDocking();

    while (steps < maxSteps)
    {
        Direction moveDirection = algorithm.step();
        if (moveDirection == Direction::Error)
        {
            cout << "Simulation break early. About to commit erroneous move" << endl;
            return stopSimulation();
        }

        Point newRobotLocation = Point::GetPointByDirection(robotLocation, moveDirection);
        if (newRobotLocation.equals(house.findDocking()))
        {
            robotAtDock(rechargeRate, newRobotLocation, steps, batteryLevel, robotLocation);
            continue;
        }

        if (batteryLevel <= 0)
        {
            cout << "Simulation end. Battery died" << endl;
            break;
        }

        performStep(newRobotLocation, steps, dirtCleaned, batteryLevel, robotLocation);
        steps++;

        if (dirtCleaned == sumOfDirt)
        {
            TryReturnToDockFromPoint(robotLocation);
            return CleanerResult(steps, sumOfDirt, dirtCleaned, robotLocation.equals(house.findDocking()));
        }
    }

    return CleanerResult(steps, sumOfDirt, dirtCleaned, robotLocation.equals(house.findDocking()));
}

void Cleaner::performStep(const Point &newRobotLocation, int &steps, int &dirtCleaned, int &batteryLevel, Point &robotLocation) const
{
    robotLocation = newRobotLocation;

    //Update dust cleaned
    dirtCleaned += house.cleanOneUnit(robotLocation);

    int batteryConsumptionPerMove = configuration.at("BatteryConsumptionRate");
    batteryLevel = max(0, batteryLevel - batteryConsumptionPerMove);
}

void Cleaner::robotAtDock(int rechargeRate, const Point &newRobotLocation, int &steps, int &batteryLevel, Point &robotLocation) const
{
    int capacity = configuration.at("BatteryCapacity");
    batteryLevel = min(capacity, batteryLevel + rechargeRate);
    steps++;
    robotLocation = newRobotLocation;
}

CleanerResult Cleaner::stopSimulation()
{
    return CleanerResult();
}

void Cleaner::TryReturnToDockFromPoint(Point point)
{
}





/*
 * configurationMap.insert(pair<string,int>("MaxSteps", 1200));
    configurationMap.insert(pair<string,int>("MaxStepsAfterWinner", 200));
    configurationMap.insert(pair<string,int>("BatteryCapacity", 400));
    configurationMap.insert(pair<string,int>("BatteryConsumptionRate", 1));
    configurationMap.insert(pair<string,int>("BatteryRechargeRate", 20));
 */
