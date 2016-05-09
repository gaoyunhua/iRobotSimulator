#include <vector>
#include "SensorInformation.h"
#include "Direction.h"
#include "AbstractAlgorithm.h"

class _306543083_G: public AbstractAlgorithm
{
    const AbstractSensor* sensor;

private:
    vector<Direction> stepsList;
    int stepsLeft;
    int steps;

    void saveStep(Direction d);

public:
    virtual void setSensor(const AbstractSensor& sensor);
    virtual Direction step();
    virtual void setConfiguration(map<string, int> config);
    virtual void aboutToFinish(int stepsTillFinishing);
    virtual Direction getDirection(const SensorInformation &locationInfo);
    virtual ~_306543083_G() {}
};
