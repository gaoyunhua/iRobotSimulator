

#ifndef __DALIALGORITHM__H_
#define __DALIALGORITHM__H_

#include "GeneralAlgorithm.h"

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

#define BATTERY_FACTOR 0.53
#define DISTANCE_FACTOR 0.75
#define MAX_SPARE_STEPS 13

class _312908205_C : public GeneralAlgorithm
{
	Location Dock;
	Location offset;
	HouseMap2 houseMap;
	Battery battery;
	int stepsLeft;
	ALGO_STATE_ENUM algo_state;
	Direction last_suggested_dir;
	vector<Location> shortestPathToDest;
	vector<Location> shortestPathToDock;
	float battery_caution_limit;
	int approximate_distance;
	int steps_till_next_check;
	bool about_to_finish;
	int debug_counter = 0;
	int debug_max_caution_distance = 0;

	//from Itay:
	//Location Dock;
	//Location offset;	//keep track of robot's location wrt docking station
	int stepsTillFinishing;

public:
	_312908205_C();

	//void setSensor(const AbstractSensor& sensor) override { this->sensor = &sensor; }

	void setConfiguration(map<string, int> config) override
	{
		battery = Battery(config[BATTERY_CAP], config[BATTERY_CONSUME_RATE], config[BATTERY_RECHARGE_RATE]);
		//currentPos = origin = Position(0, 0);
		stepsLeft = min(stepsTillFinishing, battery.level);
	}

	void chargeBattery(){
		battery.level = min(battery.capacity, battery.level + battery.recharge_rate);
	}

	bool IsGoBackToDock(const Battery& battery);
	ALGO_STATE_ENUM checkState(const Battery& battery, const Location& offset);
	virtual Direction step(Direction lastStep) override ;
	void UpdateBatteryLevel(const Location& offset);
	int checkdustLevel(const SensorInformation& sensing);

	Direction getDirByPath(const Location& offset, Direction lastStep, Direction last_suggested_dir, vector<Location>& PathToDest);

	int updatePathToDock();

	void aboutToFinish(int stepsTillFinishing) override
	{
		stepsLeft = min(stepsTillFinishing, battery.level);
		about_to_finish = true;
		updatePathToDock();
	}

private:
	//Direction lookForWallState(const SensorInformation& sensation);

//	void UpdateAlgorithmStatus(Direction lastStep){};

	ALGO_STATE_ENUM updatePath(const Location& offset);

	ALGO_STATE_ENUM getNextDestination(const Location& offset);

//	Direction AlignToWall(){};

	//void UpdateMap(const SensorInformation& sensation);
	//void addThisCellToMap(const SensorInformation& sensation);
	//void addNeighborCellsToMap(const SensorInformation& sensation);
	bool IsTouchingWall(SensorInformation sensation) const;

//	static Direction getWallOnTheRightDir(const SensorInformation & sensation){};
};

#endif
