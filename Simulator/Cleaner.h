
#ifndef SIMULATOR_CLEANER_H
#define SIMULATOR_CLEANER_H


#include "AbstractAlgorithm.h"
#include "House.h"
#include "Sensor.h"
#include "CleanerResult.h"
#include "Point.h"
#include "my_make_unique.h"

class Cleaner
{
    std::unique_ptr<AbstractAlgorithm> algorithm;
    AbstractSensor* sensor;
    House* house;
    const map<string, int>& configuration;
    Point& robotLocation;
    Direction prevStep = Direction::Stay;
    int imageCounter;
public:
    Cleaner(std::unique_ptr<AbstractAlgorithm>& _algorithm, AbstractSensor* _sensor, House* _house, Point& _robotLocation , map<string,int>& _config, string _algoName, bool isVid) :
            algorithm(std::move(_algorithm)), sensor(_sensor), house(_house),configuration(_config), robotLocation(_robotLocation), algorithmName(_algoName), isVideo(isVid){}


    Cleaner(const Cleaner &cleaner) = delete;
    Cleaner& operator=(const Cleaner&) = delete;
    ~Cleaner() { };

    void clean();
    void Step();
    void robotAtDock(int rechargeRate, Point &newRobotLocation, int &steps, int &batteryLevel);
    void performStep(int &steps, int &dirtCleaned, int &batteryLevel);
    bool didStopSimulatiion() { return didStopSimulation; }
    bool isDone() { return didFinishCleaning || didStopSimulation || didCrash; }
    CleanerResult GetResult() const;
    CleanerResult stopSimulation();
    void aboutToFinish(int stepsTillFinish){ algorithm->aboutToFinish(stepsTillFinish); }
    bool isRobotAtDock() const{ return robotLocation.equals(house->findDocking()); }
    bool getDidFinishCleaning() const { return didFinishCleaning && isRobotAtDock(); }

    string getHouseName() const { return house->name; }
    int getHouseMaxSteps() { return house->maxSteps; }
    void setPosition(int _pos) { position = _pos; }
    string algorithmName;
    int steps;

    void montage(const string& algoName, const string& houseName, const Point& robotLocation);

private:
    void printHouse(int iRob, int jRob);
    int dirtCleaned, sumOfDirt, maxSteps, batteryLevel, rechargeRate, position;
    bool didStopSimulation, didFinishCleaning, didCrash;
    bool isVideo;

};


#endif //SIMULATOR_CLEANER_H
