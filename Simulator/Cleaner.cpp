
#include "Cleaner.h"
#include "Debugger.h"

void Cleaner::clean()
{
    steps = 0;
    dirtCleaned = 0;
    sumOfDirt = house->amountOfDirt();
    maxSteps = house->maxSteps;
    batteryLevel = configuration.at("BatteryCapacity");
    rechargeRate = configuration.at("BatteryRechargeRate");
    didStopSimulation = false;
    didFinishCleaning = false;

    algorithm->setConfiguration(configuration);
    AbstractSensor& a = *sensor;
    algorithm->setSensor(a);
}

void Cleaner::Step()
{
//    printHouse(robotLocation.getX(), robotLocation.getY());

    if (batteryLevel <= 0)
    {
        PRINT_DEBUG("Battery dead");
        return;
    }

    Direction moveDirection = algorithm->step(prevStep);

    Point newRobotLocation = Point::GetPointByDirection(robotLocation, moveDirection);
//    PRINT_DEBUG(
//            "Moving:(" +
//                    to_string(robotLocation.getX()) +
//                    "," + to_string(robotLocation.getY())  +
//                    ")-->(" + to_string(newRobotLocation.getX()) +
//                    "," + to_string(newRobotLocation.getY()) + ")");

    if (newRobotLocation.equals(house->findDocking()))
    {
        robotAtDock(rechargeRate, newRobotLocation, steps, batteryLevel);
    }

    if (house->isWall(newRobotLocation))
    {
        PRINT_DEBUG("Robot crashed into a wall!");
        didStopSimulation = true;
    }

    robotLocation.move(moveDirection);
    performStep(steps, dirtCleaned, batteryLevel);
    prevStep = moveDirection;
    steps++;
}

CleanerResult Cleaner::GetResult() const
{
    if (didStopSimulation)
        return CleanerResult();

    return CleanerResult(steps, sumOfDirt, dirtCleaned, robotLocation.equals(house->findDocking()), position);
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
//    PRINT_DEBUG("Robot At Dock");
}

CleanerResult Cleaner::stopSimulation()
{
    return CleanerResult();
}

void Cleaner::printHouse(int iRob, int jRob)
{
    if (!DEBUG)
        return;

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