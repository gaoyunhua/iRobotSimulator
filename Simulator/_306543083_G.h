
#ifndef ___306543083_G__H_
#define ___306543083_G__H_

#include <vector>
#include <cstdlib>
#include "Algorithm.h"
#include <iostream>
#include <fstream>
#include <sstream>

class _306543083_G: public Algorithm
{
    const AbstractSensor* sensor;

private:
    vector<Direction> stepsList;
    int stepsLeft;
    int steps;

    void saveStep(Direction d);

public:
    _306543083_G();
    virtual void setSensor(const AbstractSensor& sensor);
    virtual Direction step();
    virtual void setConfiguration(map<string, int> config);
    virtual void aboutToFinish(int stepsTillFinishing);
    virtual Direction getDirection(const SensorInformation &locationInfo);
    virtual ~_306543083_G();
};

#endif