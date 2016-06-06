
#include "GeneralAlgorithm.h"

void GeneralAlgorithm::setSensor(const AbstractSensor& sensor){
	this->sensor = &sensor;
	//PRINT_DEBUG("Sensor was set to the algorithm");
	//init();
}

//get a direction which is n ot a wall
void GeneralAlgorithm::avoidWall(const SensorInformation& sensed, Direction& dir) const{
	if (dir == Direction::Stay)
		dir = Direction::East;

	while (sensed.isWall[(int)dir]){	//make sure the robot does not run into wall
		PRINT_DEBUG("trying to walk into wall");
		dir = (Direction)(((int)dir + 3) % NUM_OF_DIRECTIONS);
		if (dir == Direction::Stay)
			return;
	}
}

