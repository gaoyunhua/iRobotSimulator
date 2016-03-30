
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
    const map<string, int> configuration;

public:
    Cleaner(AbstractAlgorithm& _algorithm, Sensor& _sensor, House& _house, map<string,int> _config) :
            algorithm(_algorithm), sensor(_sensor), house(_house), configuration(_config){}

    CleanerResult clean();
    CleanerResult stopSimulation();

    void TryReturnToDockFromPoint(Point point);

    void robotAtDock(int rechargeRate, const Point &newRobotLocation, int &steps, int &batteryLevel, Point &robotLocation) const;

    void performStep(const Point &newRobotLocation, int &steps, int &dirtCleaned, int &batteryLevel, Point &robotLocation) const;
};


#endif //SIMULATOR_CLEANER_H
