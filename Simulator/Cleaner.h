
#ifndef SIMULATOR_CLEANER_H
#define SIMULATOR_CLEANER_H


#include "AbstractAlgorithm.h"
#include "House.h"

class Cleaner
{
    AbstractAlgorithm& algorithm;
    AbstractSensor& sensor;
    House& house;
    map<string, int> configuration;

public:
    Cleaner(AbstractAlgorithm& _algorithm, AbstractSensor& _sensor, House& _house, map<string,int> _config) :
            algorithm(_algorithm), sensor(_sensor), house(_house), configuration(_config){}

    void clean();
};


#endif //SIMULATOR_CLEANER_H
