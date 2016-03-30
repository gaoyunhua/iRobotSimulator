
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
//    Point docking = house.findDocking();
//    Point& robotLocation(docking);

    algorithm.setConfiguration(configuration);
//    sensor.robotLocation = robotLocation;
    algorithm.setSensor(sensor);



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
            robotAtDock(rechargeRate, newRobotLocation, steps, batteryLevel);
            continue;
        }

        if (batteryLevel <= 0)
        {
            cout << "Simulation end. Battery died" << endl;
            break;
        }

        robotLocation.move(moveDirection);
        performStep(steps, dirtCleaned, batteryLevel);
        steps++;

        if (dirtCleaned == sumOfDirt)
        {
            cout << "No more Dirt!\n# Steps:" + to_string(steps) << endl;
            TryReturnToDockFromPoint(robotLocation);
            return CleanerResult(steps, sumOfDirt, dirtCleaned, robotLocation.equals(house.findDocking()));
        }
    }

    return CleanerResult(steps, sumOfDirt, dirtCleaned, robotLocation.equals(house.findDocking()));
}

void Cleaner::performStep(int &steps, int &dirtCleaned, int &batteryLevel)
{
    //Update dust cleaned
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





/*
 * configurationMap.insert(pair<string,int>("MaxSteps", 1200));
    configurationMap.insert(pair<string,int>("MaxStepsAfterWinner", 200));
    configurationMap.insert(pair<string,int>("BatteryCapacity", 400));
    configurationMap.insert(pair<string,int>("BatteryConsumptionRate", 1));
    configurationMap.insert(pair<string,int>("BatteryRechargeRate", 20));
 */
