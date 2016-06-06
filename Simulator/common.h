/***************************************************************************************/
/*Authors:                                                                             */
/*karinavesker (312908205)                                                             */
/*itaifriedman (301354288)                                                             */
/***************************************************************************************/

#ifndef _COMMON
#define _COMMON

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include "Location.h"
#include "Direction.h"
#include "SensorInformation.h"

using namespace std;
typedef unsigned int uint;


//----------Configuration parameters defines----------
#define BATTERY_CAP "BatteryCapacity"
#define MAX_STEPS_AFTER_WINNER "MaxStepsAfterWinner"
#define BATTERY_CONSUME_RATE "BatteryConsumptionRate"
#define BATTERY_RECHARGE_RATE "BatteryRechargeRate"
//----------------------------------------------------


//useful macros
#define MAX_VAL(a,b) ((a) > (b))? (a) : (b)
#define MIN_VAL(a,b) ((a) < (b))? (a) : (b)


#define NUM_OF_DIRECTIONS 5
#define RIGHT Direction::East
#define UP Direction::North
#define LEFT Direction::West
#define DOWN Direction::South
#define HERE Direction::Stay


//Printer for Direction enum
std::ostream& operator<<(std::ostream& out, const Direction value);

//------------Global functions------------
class Common{
public:
	static Direction oppositeDirection(const Direction& dir);
	static Direction counterClockwiseDirection(const Direction& dir);
	
	//Constants
	static const int MAX_INT = 0x7FFFFFFF;
};


#endif	//_COMMON