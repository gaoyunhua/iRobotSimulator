
#include "AbstractSensor.h"
#include "House.h"
#include "Point.h"

class Sensor : public AbstractSensor
{
    const House& house;
    Point& robotLocation;

public:
    Sensor(const House& _house, Point& _robotLocation) : house(_house), robotLocation(_robotLocation){}
    SensorInformation sense() const;
    ~Sensor();
};
