
#include "_312908205_A.h"


_312908205_A::_312908205_A() : GeneralAlgorithm(), Dock(0, 0), offset(0, 0)
, houseMap(Dock), battery(100, 1, 10), stepsLeft(Common::MAX_INT), algo_state()
, last_suggested_dir(Direction::Stay), approximate_distance(0), steps_till_next_check(0),
about_to_finish(false), stepsTillFinishing(Common::MAX_INT)
{
	shortestPathToDest.clear();
	shortestPathToDock.clear();
	battery_caution_limit = (float) (battery.capacity * BATTERY_FACTOR);
}


Direction _312908205_A::step(Direction lastStep)
{
	SensorInformation sensing = useSensor();
	Direction chosen_dir = Direction::Stay;
	offset = offset + lastStep;
	//update battery level

	if (offset == Dock && battery.level < 10)
		offset = offset;
	houseMap.UpdateMap(sensing, offset);

	//PRINT_DEBUG("_312908205_A:step");
	if (DEBUG){
		debug_counter++;
		if (debug_counter % 100 == 0){
			houseMap.printMe(offset);
			cout << debug_counter << endl;
		}
/*
		if (debug_counter > 2260)
		{
		houseMap.printMe(offset);
		PRINT_DEBUG("algo_state" << algo_state);
		}
*/
	}


	//checkBatteryLevel(battery);
	algo_state = checkState(battery, offset);

	
	if (algo_state > 5)
		algo_state = getNextDestination(offset);

	switch (algo_state)
	{
	case LOOK_FOR_CLOSEST_N:
	case LOOK_FOR_BORDER_N:
	case LOOK_FOR_DIRT:
		if (sensing.dirtLevel > 0)
			chosen_dir = Direction::Stay;
		else	
		{
			if (shortestPathToDest.size() == 0){
				cout << "algo state is: " << algo_state << " offset is: " << offset.x << " " << offset.y << endl; //karina delete
				algo_state = checkState(battery, offset);
				cout << "algo state is: " << algo_state << " offset is: " << offset.x << " " << offset.y << endl; //karina delete
			}
			chosen_dir = getDirByPath(offset, lastStep, last_suggested_dir, shortestPathToDest);
		}
		break;
	case GO_TO_RECHARGE:
		if (shortestPathToDock.size() == 0){
			cout << "algo state is: " << algo_state << " offset is: " << offset.x << " " << offset.y << endl; //karina delete
			//algo_state = checkState(battery, offset);
			cout << houseMap.bfs(offset, shortestPathToDock, MAP_CHAR_D) << endl;
			cout << "algo state is: " << algo_state << " offset is: " << offset.x << " " << offset.y << endl; //karina delete
		}
		chosen_dir = getDirByPath(offset, lastStep, last_suggested_dir, shortestPathToDock);
		if (DEBUG)
		{
			if (stepsLeft - approximate_distance > debug_max_caution_distance)
				debug_max_caution_distance = max(debug_max_caution_distance, stepsLeft - approximate_distance);
		}
		break;
	case RECHARGING:
	case CLEANING:
		chosen_dir = Direction::Stay;
		break;
	case UNDEFINED:
		break;
	}

	UpdateBatteryLevel(offset);
	//stepsLeft--;
	stepsTillFinishing--;
	stepsLeft = min(stepsTillFinishing, battery.level);
	steps_till_next_check--;
	last_suggested_dir = chosen_dir;
	return chosen_dir;
	return Direction::West;
}

void _312908205_A::UpdateBatteryLevel(const Location& offset)
{
	if (offset == Dock)
		chargeBattery();
	else
		battery.level -= battery.consume_rate;	//consume battery
}

//TODO: implement
Direction _312908205_A::getDirByPath(const Location& offset, Direction lastStep, Direction last_suggested_dir, vector<Location>& PathToDest)
{
	//return UP;
	if (offset == PathToDest.back())
		PathToDest.pop_back();
	if (offset.IsNeighbor(PathToDest.back()))
		return PathToDest.back() - offset;
	if (lastStep != last_suggested_dir)
		return Common::oppositeDirection(lastStep);
	//houseMap.bfs(offset, PathToDest, )
	throw "getDirByPath has nothing to return";
}


int _312908205_A::checkdustLevel(const SensorInformation& sensing)
{
	return sensing.dirtLevel;
}


//gets the shortest path to dock, and sets the next time to recheck the distance
//function is called each time refresh rate reaches 0, 
//or when about_to_finish, or when battery level reaches caution_limit
int _312908205_A::updatePathToDock()
{
	houseMap.bfs(offset, shortestPathToDock, MAP_CHAR_D);
	int distance = shortestPathToDock.size();

	//distance + steps_till_next_check < stepsLeft - steps_till_next_check
	steps_till_next_check = max(static_cast<int>(0.4 * (stepsLeft - distance)), 0);

	//approximate_distance = distance;
	return distance;
}

//check if it's time to go back, maybe it's to charge or to finish
//function is called if not recharging, and not going to
bool _312908205_A::IsGoBackToDock(const Battery& battery)
{
	//check if battery is under caution_limit
	//check what's the approximate distance to dock
	//check if battery's enough to go back
	if (battery.level < battery_caution_limit || steps_till_next_check <= 0 || approximate_distance >= DISTANCE_FACTOR * stepsLeft)
		approximate_distance = updatePathToDock();
		
	if (approximate_distance >= DISTANCE_FACTOR * stepsLeft && (stepsLeft - approximate_distance < MAX_SPARE_STEPS))
		return true;
	

	return false;
}

//get the state which sets this step's behavior
ALGO_STATE_ENUM _312908205_A::checkState(const Battery& battery, const Location& offset)
{
	if (algo_state == RECHARGING)
	{
		//battery not full yet
		if (battery.level < battery.capacity)
			return RECHARGING;
		
		//else
		return getNextDestination(offset);
	}
	if (algo_state == GO_TO_RECHARGE)
	{
		//didn't reach docking yet
		if (!(offset == Dock))
			return GO_TO_RECHARGE;
		
		shortestPathToDock.clear();
		return RECHARGING;
	}
	// not recharging and not going to
	if (IsGoBackToDock(battery))
	{
		shortestPathToDest.clear();

		if (offset == Dock)
			return RECHARGING;

		return GO_TO_RECHARGE;
	}
	
	if (algo_state == LOOK_FOR_BORDER_N || algo_state == LOOK_FOR_CLOSEST_N)
	{
		/*TODO: check if this cell is the destination,
		  TODO: if not, continue to dest*/
		
		//reached 'N' on border
		if ((shortestPathToDest.size() != 0 && shortestPathToDest.front() == offset) || shortestPathToDest.size() == 0)
		{
			shortestPathToDest.clear();
			return getNextDestination(offset);
		}
		else if (shortestPathToDest.size() != 0)
			return algo_state;

	}
	if (algo_state == LOOK_FOR_DIRT)
	{
		if ((shortestPathToDest.size() != 0 && shortestPathToDest.front() == offset) || shortestPathToDest.size() == 0)
		{
			shortestPathToDest.clear();
			if (houseMap.bfs(offset, shortestPathToDest, MAP_CHAR_DIRT))
				return LOOK_FOR_DIRT;

			houseMap.bfs(offset, shortestPathToDock, MAP_CHAR_D);
			return GO_TO_RECHARGE;
		}
		return  LOOK_FOR_DIRT;
	}

	return ALGO_STATE_ENUM::UNDEFINED;
	return getNextDestination(offset);
}

ALGO_STATE_ENUM _312908205_A::getNextDestination(const Location& offset)
{
	bool exists;

	if (!houseMap.IsBordersDiscovered() && houseMap.getSize() < 500)
	{
		exists = houseMap.bfs(offset, shortestPathToDest, MAP_CHAR_N_BORDER);
		if (exists)
			return LOOK_FOR_BORDER_N;		
	}

	exists = houseMap.bfs(offset, shortestPathToDest, MAP_CHAR_N_CLOSEST);
	if (exists && shortestPathToDest.size() <= stepsLeft - shortestPathToDest.size() - MAX_SPARE_STEPS)
	{
		return LOOK_FOR_CLOSEST_N;
	}

	exists = houseMap.bfs(offset, shortestPathToDest, MAP_CHAR_DIRT);
	if (exists)
		return LOOK_FOR_DIRT;

	houseMap.bfs(offset, shortestPathToDock, MAP_CHAR_D);
	if (shortestPathToDock.size() != 0)
		return GO_TO_RECHARGE;
	houseMap.printMe(offset);
	return RECHARGING;
}

ALGO_STATE_ENUM _312908205_A::updatePath(const Location& offset)
{
	//reached 'N' on border
	if (shortestPathToDest.size() != 0 && shortestPathToDest.front() == offset)
			shortestPathToDest.clear();

	//haven't reached destination yet
	else if (shortestPathToDest.size() != 0)
		return LOOK_FOR_BORDER_N;

	if (!houseMap.IsBordersDiscovered())
	{
		//try to find 'N' on border
		bool exists = houseMap.bfs(offset, shortestPathToDest, MAP_CHAR_N_BORDER);
		if (!exists)
			exists = houseMap.bfs(offset, shortestPathToDest, MAP_CHAR_N_CLOSEST);
		if (!exists)
			exists = houseMap.bfs(offset, shortestPathToDest, MAP_CHAR_DIRT);
		if (!exists)
			return GO_TO_RECHARGE;

		
		return LOOK_FOR_BORDER_N;

	}
	return LOOK_FOR_BORDER_N;

}

/*
Direction _312908205_A::lookForWallState(const SensorInformation& sensation)
{
	Direction goTo;

	//if wall already found, switch state
	if (IsTouchingWall(sensation))
	{
		algo_state = STICK_TO_WALL;
		goTo = getWallOnTheRightDir(sensation);
		return goTo;
	}

	//if not touching any wall
	for (int dir = 0; dir < 4; dir++)
	{
		//prefer to visit an unknown cell
		if (houseMapLocation.at(offset + Direction(dir)) == 'N')
		{
			goTo = Direction(dir);
			return goTo;
		}
	}

	//if all cells are known
	return RIGHT;
}
*/
/*
void _312908205_A::UpdateMap(const SensorInformation& sensation)
{
	addThisCellToMap(sensation);
	addNeighborCellsToMap(sensation);
}

//add information about the current cell - add 'W' for wall, 'N' otherwise
void _312908205_A::addThisCellToMap(const SensorInformation& sensation)
{
	if (houseMapLocation.at(offset) != 'D')
		houseMapLocation[offset] = MAX_VAL(sensation.dirtLevel - 1, 0) + '0';
}

//add information about the surrounding cells - add 'W' for wall, 'N' otherwise
void _312908205_A::addNeighborCellsToMap(const SensorInformation& sensation)
{
	//check all 4 surrounding cells
	for (int dir = 0; dir < 4; dir++)
	{
		Location neighbor = offset + Direction(dir);
		bool notInMap = houseMapLocation.count(neighbor) == 0;
		if (notInMap && HouseMap::IsOutOfBorder(neighbor))
			HouseMap::expandBorders(neighbor);
		if (notInMap || (!notInMap && houseMapLocation.at(neighbor) == '?'))
		{
			if (sensation.isWall[dir] == 0)
				houseMapLocation[neighbor] = 'N';
			else
				houseMapLocation[neighbor] = 'W';
		}
	}
}
*/
//check if one of the surrounding cells is a wall
bool _312908205_A::IsTouchingWall(SensorInformation sensation) const
{
	//SensorInformation sensation = sensor->sense();
	if (sensation.isWall[int(Direction::East)] || sensation.isWall[int(Direction::North)] ||
		sensation.isWall[int(Direction::South)] || sensation.isWall[int(Direction::West)])
	{
		PRINT_DEBUG("_312908205_A:IsTouchingWall: returning true");
		return true;
	}
	else
	{
		PRINT_DEBUG("_312908205_A:IsTouchingWall: returning false");
		return false;
	}
}

//get a direction so the wall is on the right side from you
//TODO: change this it's mistaken
Direction _312908205_A::getWallOnTheRightDir(const SensorInformation& sensation)
{
	Direction goTo = RIGHT;
	int securityCount = 0;
	while (sensation.isWall[int(goTo)] == 1)
	{
		goTo = Common::counterClockwiseDirection(goTo);
		securityCount++;
		if (securityCount > 6)
			PRINT_DEBUG("_312908205_A:getWallOnTheRightDir: stuck ");
	}
	PRINT_DEBUG("_312908205_A:getWallOnTheRightDir: returning " << goTo);
	return goTo;
}

void _312908205_A::UpdateAlgorithmStatus(Direction lastStep)
{
}

//TODO: delete or something
Direction _312908205_A::AlignToWall()
{
	/*SensorInformation sensed = sensor->sense();
	if (sensed.isWall[int(Direction::East)]);*/
	return Direction::West;
}

/*
Direction _312908205_A::GoBackToDock()
{
}

Direction _312908205_A::GoBackToDockOpportunistic()
{
}

Direction _312908205_A::GoBackToDockDirectly()
{
}

Direction _312908205_A::Clean()
{
}

Direction _312908205_A::LastStepsToFinish()
{
}

int _312908205_A::ComputeScore(int row, int col)
{
}

int _312908205_A::FindShortestDistance(int firstRow, int firstCol, int secondRow, int secondCol)
{
}

bool _312908205_A::IsInDocking()
{
}

*/

//REGISTER_ALGORITHM(_312908205_A)
