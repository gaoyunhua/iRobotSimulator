
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
    Cleaner(AbstractAlgorithm& _algorithm, AbstractSensor* _sensor, House* _house, Point& _robotLocation , map<string,int>& _config, string _algoName) :
            algorithm(_algorithm), sensor(_sensor), house(_house), robotLocation(_robotLocation), configuration(_config), algorithmName(_algoName){}

    void clean();
    void Step();
    void robotAtDock(int rechargeRate, Point &newRobotLocation, int &steps, int &batteryLevel);
    void performStep(int &steps, int &dirtCleaned, int &batteryLevel);

    bool isDone() { return didFinishCleaning || didStopSimulation; }
    CleanerResult GetResult() const;
    CleanerResult stopSimulation();
    void aboutToFinish(int stepsTillFinish){ algorithm.aboutToFinish(stepsTillFinish); }
    bool isRobotAtDock() { return robotLocation.equals(house->findDocking()); }
    bool getDidFinishCleaning() { return didFinishCleaning; }

    string getHouseName() const { return house->name; }
    int getHouseMaxSteps() { return house->maxSteps; }
    void setPosition(int _pos) { position = _pos; }
    string algorithmName;
    int steps;

private:
    void printHouse(int iRob, int jRob);
    int dirtCleaned, sumOfDirt, maxSteps, batteryLevel, rechargeRate, position;
    bool didStopSimulation, didFinishCleaning;

};


#endif //SIMULATOR_CLEANER_H
