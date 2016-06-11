
#include "Cleaner.h"
#include "Debugger.h"
#include <algorithm>
#include <string>

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
    didCrash = false;
    imageCounter = 0;

    algorithm->setConfiguration(configuration);
    AbstractSensor& a = *sensor;
    algorithm->setSensor(a);
    
    if(isVideo)
	    montage(algorithmName, getHouseName(), robotLocation);
}

void Cleaner::Step()
{
    if (getDidFinishCleaning())
        return;

    if (batteryLevel <= 0)
    {
        PRINT_DEBUG("Battery dead");
        didStopSimulation = true;
        return;
    }

    Direction moveDirection = algorithm->step(prevStep);

    Point newRobotLocation = Point::GetPointByDirection(robotLocation, moveDirection);

    if (newRobotLocation.equals(house->findDocking()))
    {
        robotAtDock(rechargeRate, newRobotLocation, steps, batteryLevel);
    }

    if (house->isWall(newRobotLocation))
    {
        PRINT_DEBUG("\n\nRobot will crash into a wall!!\n\n");
        didCrash = true;
        return;
    }

    performStep(steps, dirtCleaned, batteryLevel);
    robotLocation.move(moveDirection);
    prevStep = moveDirection;
    steps++;

    if(isVideo)
	    montage(algorithmName, getHouseName(), robotLocation);
}

CleanerResult Cleaner::GetResult() const
{
    if (didCrash)
        return CleanerResult();

    return CleanerResult(steps, sumOfDirt, dirtCleaned, robotLocation.equals(house->findDocking()), position, getDidFinishCleaning());
}

void Cleaner::performStep(int &steps, int &dirtCleaned, int &batteryLevel)
{
    dirtCleaned += house->cleanOneUnit(robotLocation);

    int batteryConsumptionPerMove = configuration.at("BatteryConsumptionRate");
    batteryLevel = max(0, batteryLevel - batteryConsumptionPerMove);
    if (dirtCleaned == sumOfDirt)
    {
        didFinishCleaning = true;
    }
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

void createDirectoryIfNotExists(const std::string& dirPath)
{
    string cmd = "mkdir -p " + dirPath;
    int ret = system(cmd.c_str());
    if (ret == -1)
    {
        //handle error
    }
}

void Cleaner::montage(const string& algoName, const string& houseName, const Point& robotLocation)
{
    vector<string> tiles;
    for (int row = 0; row < house->rows; ++row)
    {
        for (int col = 0; col < house->columns; ++col)
        {
            if (row == robotLocation.getX() && col == robotLocation.getY())
                tiles.push_back("avatars/R");
            else if (house->point(Point(row,col)) == ' ')
                tiles.push_back("avatars/0");
            else
                tiles.push_back(string() + "avatars/" + house->point(Point(row,col)));
        }
    }
    string imagesDirPath = "./simulations/" + algoName + "_" + houseName;
    createDirectoryIfNotExists(imagesDirPath);
    string counterStr = to_string(imageCounter++);
    string composedImage = imagesDirPath + "/image" + string(5 - counterStr.length(), '0') + counterStr + ".jpg";
    Montage::compose(tiles, house->columns, house->rows, composedImage);
}