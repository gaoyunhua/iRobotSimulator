
#ifndef _GENERAL_ALGORITHM
#define _GENERAL_ALGORITHM

#include "common.h"
#include "AlgorithmRegistration.h"
#include "AbstractAlgorithm.h"
#include "Debugger.h"
#include "my_make_unique.h"
#include "HouseMap2.h"
#include "Battery.h"
#include <vector>

enum ALGO_STATE_ENUM
{
	LOOK_FOR_CLOSEST_N,
	LOOK_FOR_BORDER_N,
	CLEANING,
	GO_TO_RECHARGE,
	RECHARGING,
	LOOK_FOR_DIRT,
	UNDEFINED
};


class GeneralAlgorithm : public AbstractAlgorithm
{
public:
	GeneralAlgorithm() : AbstractAlgorithm(), sensor(NULL){}
	virtual ~GeneralAlgorithm(){}
		
	//funcs for implementing interface
	void setSensor(const AbstractSensor& sensor) override;
//	virtual Direction step() override{ return Direction::Stay; }	//dummy
	//virtual void aboutToFinish(int stepsTillFinishing) {}	//dummy
	void setConfiguration(map<string, int> config) override { this->config = config; }

protected:
	//const AbstractSensor* sensor;

	struct SensorInformation useSensor() const{ 
		//PRINT_DEBUG("using sensor. sensor addr: " << (void*)sensor);
		return sensor->sense();
	}
	int getConfigParam(const string& str) const{ return config.at(str); }
	Direction getDefDirection() const{ return DEF_DIRECTION; }
	void avoidWall(const SensorInformation& sensed, Direction& dir) const;
	//make every algorithm have an init function
	//virtual void init() = 0;

private:
	const AbstractSensor* sensor = nullptr;
	map<string, int> config;	//Simulation config parameters
	static const Direction DEF_DIRECTION = Direction::East;
};


#endif	//_GENERAL_ALGORITHM