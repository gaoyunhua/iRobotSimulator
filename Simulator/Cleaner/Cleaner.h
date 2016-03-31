
#ifndef SIMULATOR_CLEANER_H
#define SIMULATOR_CLEANER_H


#include "AbstractAlgorithm.h"
#include "House.h"
#include "Sensor.h"
#include "CleanerResult.h"

class Cleaner
{
    AbstractAlgorithm& algorithm;
    Sensor& sensor;
    House& house;
    const map<string, int>& configuration;
    Point& robotLocation;

public:
    Cleaner(AbstractAlgorithm& _algorithm, Sensor& _sensor, House& _house, Point& _robotLocation , map<string,int>& _config) :
            algorithm(_algorithm), sensor(_sensor), house(_house), robotLocation(_robotLocation), configuration(_config){}

    CleanerResult clean();
    CleanerResult stopSimulation();

    void TryReturnToDockFromPoint(Point point);

    void robotAtDock(int rechargeRate, Point &newRobotLocation, int &steps, int &batteryLevel);

    void performStep(int &steps, int &dirtCleaned, int &batteryLevel);
};


#endif //SIMULATOR_CLEANER_H
