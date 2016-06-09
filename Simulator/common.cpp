
#include "common.h"
//#include <sys/stat.h>

////----------Debugger instance----------
//Debugger Debugger::instance;
////-------------------------------------


//Printer for Direction enum
std::ostream& operator<<(std::ostream& out, const Direction value){
	const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
	switch (value){
		PROCESS_VAL(Direction::East);
		PROCESS_VAL(Direction::West);
		PROCESS_VAL(Direction::South);
		PROCESS_VAL(Direction::North);
		PROCESS_VAL(Direction::Stay);
	}
#undef PROCESS_VAL
	return out << s;
}

//------------Global functions------------
Direction Common::oppositeDirection(const Direction& dir){
	switch (dir){
	case(Direction::East) :
		return Direction::West;
	case(Direction::West) :
		return Direction::East;
	case(Direction::South) :
		return Direction::North;
	case(Direction::North) :
		return Direction::South;
	case(Direction::Stay) :
		return Direction::Stay;
	default:
		return Direction::Stay;
	}
}

Direction Common::counterClockwiseDirection(const Direction& dir)
{
	switch (dir){
	case(RIGHT) :
		return UP;
	case(UP) :
		return LEFT;
	case(LEFT) :
		return DOWN;
	case(DOWN) :
		return RIGHT;
	case(Direction::Stay) :
		return Direction::Stay;
	default:
		return Direction::Stay;
	}
}
