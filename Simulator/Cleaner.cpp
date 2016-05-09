
#include "Cleaner.h"

void Cleaner::clean()
{
    steps = 0;
    dirtCleaned = 0;
    sumOfDirt = house->amountOfDirt();
    maxSteps = house->maxSteps;
    batteryLevel = configuration.at("BatteryCapacity");
    rechargeRate = configuration.at("BatteryRechargeRate");
    didStopSimulation = false;

    algorithm.setConfiguration(configuration);
    AbstractSensor& a = *sensor;
    algorithm.setSensor(a);
}

void Cleaner::Step()
{
    printHouse(robotLocation.getX(), robotLocation.getY());
    Direction moveDirection = algorithm.step();

//    if ((int)moveDirection == 4)
//    {
//        didStopSimulation = true;
//        return;
//    }

    Point newRobotLocation = Point::GetPointByDirection(robotLocation, moveDirection);
    cout << "Moving:(" + to_string(robotLocation.getX()) + "," + to_string(robotLocation.getY())  + ")-->(" + to_string(newRobotLocation.getX()) + "," + to_string(newRobotLocation.getY()) + ")" << endl;
    cout << endl;
    if (newRobotLocation.equals(house->findDocking()))
    {
        robotAtDock(rechargeRate, newRobotLocation, steps, batteryLevel);
    }

    if (batteryLevel <= 0)
    {
        return;
    }

    robotLocation.move(moveDirection);
    performStep(steps, dirtCleaned, batteryLevel);
    steps++;
}

CleanerResult Cleaner::GetResult()
{
    if (didStopSimulation)
        return CleanerResult();

    return CleanerResult(steps, sumOfDirt, dirtCleaned, robotLocation.equals(house->findDocking()));
}

void Cleaner::performStep(int &steps, int &dirtCleaned, int &batteryLevel)
{
    dirtCleaned += house->cleanOneUnit(robotLocation);

    int batteryConsumptionPerMove = configuration.at("BatteryConsumptionRate");
    batteryLevel = max(0, batteryLevel - batteryConsumptionPerMove);
}

void Cleaner::robotAtDock(int rechargeRate,Point &newRobotLocation, int &steps, int &batteryLevel)
{
    int capacity = configuration.at("BatteryCapacity");
    batteryLevel = min(capacity, batteryLevel + rechargeRate);
    cout << "Robot At Dock" << endl;
}

CleanerResult Cleaner::stopSimulation()
{
    return CleanerResult();
}

void Cleaner::printHouse(int iRob, int jRob)
{
    for (int i = 0; i < house->rows; ++i)
    {
        for (int j = 0; j < house->columns; ++j)
        {
            if (i == iRob && j == jRob)
                cout << 'R';
            else
                cout << house->house[i][j];
        }
        cout << endl;
    }
    cout << endl;
}