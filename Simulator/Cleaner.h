
#ifndef SIMULATOR_CLEANER_H
#define SIMULATOR_CLEANER_H


#include "AbstractAlgorithm.h"
#include "House.h"
#include "Sensor.h"
#include "CleanerResult.h"
#include "Point.h"

class Cleaner
{
    AbstractAlgorithm& algorithm;
    AbstractSensor* sensor;
    House* house;
    const map<string, int>& configuration;
    Point& robotLocation;

public:
    Cleaner(AbstractAlgorithm& _algorithm, AbstractSensor* _sensor, House* _house, Point& _robotLocation , map<string,int>& _config) :
            algorithm(_algorithm), sensor(_sensor), house(_house), robotLocation(_robotLocation), configuration(_config){}

    void clean();
    void Step();
    CleanerResult GetResult();
    CleanerResult stopSimulation();

    void robotAtDock(int rechargeRate, Point &newRobotLocation, int &steps, int &batteryLevel);

    void performStep(int &steps, int &dirtCleaned, int &batteryLevel);

private:
    void printHouse(int iRob, int jRob);
    int steps, dirtCleaned, sumOfDirt, maxSteps, batteryLevel, rechargeRate;
    bool didStopSimulation;

};


#endif //SIMULATOR_CLEANER_H
