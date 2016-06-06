#include "HouseMap2.h"


HouseMap2::HouseMap2(Location Dock) : rightmost_x(0), leftmost_x(0), top_y(0), bottom_y(0), matrix(nullptr)
, matrix_mode(false), borders_discovered(false)
{
	houseMapLocation[Dock] = 'D';
}


HouseMap2::~HouseMap2()
{
}

int HouseMap2::getHeight() const
{
	return top_y - bottom_y + 1;
}

int HouseMap2::getWidth() const
{
	return rightmost_x - leftmost_x + 1;
}

int HouseMap2::getSize() const
{
	return getWidth() * getHeight();
}

void HouseMap2::UpdateMap(const SensorInformation& sensation, Location cell)
{
	addThisCellToMap(sensation, cell);
	addNeighborCellsToMap(sensation, cell);
}

//add information about the current cell - add 'W' for wall, 'N' otherwise
void HouseMap2::addThisCellToMap(const SensorInformation& sensation, Location cell)
{
	if ((*this)[cell] != 'D')
		(*this)[cell] = '0' + max(sensation.dirtLevel, 0);
//	char ch = (*this)[cell];
}

//add information about the surrounding cells - add 'W' for wall, 'N' otherwise
void HouseMap2::addNeighborCellsToMap(const SensorInformation& sensation, Location loc)
{
	//check all 4 surrounding cells
	for (int dir = 0; dir < 4; dir++)
	{
		Location neighbor = loc + Direction(dir);

		if (IsOutOfBorder(neighbor))
			expandBorders(neighbor);

		if ((*this)[neighbor] == '?')
		{
			if (sensation.isWall[dir] == 0)
				(*this)[neighbor] = 'N';
			else
				(*this)[neighbor] = 'W';
		}
	}
}

void HouseMap2::InsertToMap(const Location& loc)
{
	//(*this)[loc] = '?';
}

//works on map
void HouseMap2::fillCol(int col, int bottom, int top)
{
	for (int row = bottom; row <= top; row++)
	{
		houseMapLocation[Location(col, row)] = '?';
	}
}

//works on map
void HouseMap2::fillRow(int row, int leftmost, int rightmost)
{
	for (int col = leftmost; col <= rightmost; col++)
	{
		houseMapLocation[Location(col, row)] = '?';
	}
}

//updates the new borders, and fills the new row/col with '?'
//works on map
void HouseMap2::expandBorders(Location loc)
{
	if (loc.x < leftmost_x)
	{
		leftmost_x = loc.x;
		matrix_mode? MatrixGetWider(leftmost_x) : fillCol(leftmost_x, bottom_y, top_y);
	}
	else if (loc.x > rightmost_x)
	{
		rightmost_x = loc.x;
		matrix_mode ? MatrixGetWider(rightmost_x) : fillCol(rightmost_x, bottom_y, top_y);
	}
	if (loc.y < bottom_y)
	{
		bottom_y = loc.y;
		matrix_mode? MatrixGetLonger(bottom_y) : fillRow(bottom_y, leftmost_x, rightmost_x);
	}
	else if (loc.y > top_y)
	{
		top_y = loc.y;
		matrix_mode ? MatrixGetLonger(top_y) : fillRow(top_y, leftmost_x, rightmost_x);
	}

	if (!matrix_mode && houseMapLocation.size() > 500)
	{
		matrix = MapToMatrice();
		matrix_mode = true;
	}
}

//checks if this location is going to expand our previous borders
bool HouseMap2::IsOutOfBorder(Location loc) const
{
	return (loc.x < leftmost_x || loc.x > rightmost_x || loc.y < bottom_y || loc.y > top_y);
}


//simply copy the values from the map to a matrice, mark undiscovered cells as ?
char** HouseMap2::MapToMatrice()
{
	char** matrice = new char*[getHeight()];

	for (int row = 0; row < getHeight(); row++)
	{
		matrice[row] = new char[getWidth()];
		for (int col = 0; col < getWidth(); col++)
		{
			Location loc = ConvertToLocation(col, row);
			matrice[row][col] = houseMapLocation.at(loc);
		}
	}
	return matrice;
}

void HouseMap2::MatrixGetWider(int new_x)
{
	char** matrice = new char*[getHeight()];

	for (int row = 0; row < getHeight(); row++)
	{
		matrice[row] = new char[getWidth()];
		if (new_x == leftmost_x)
		{
			matrice[row][0] = '?';
			memcpy(&(matrice[row][1]), matrix[row], getWidth() - 1);
		}
		else if (new_x == rightmost_x)
		{
			memcpy(matrice[row], matrix[row], getWidth() - 1);
			matrice[row][getWidth() - 1] = '?';
		}
		else
			return;
	}

	delete[] matrix;
	matrix = matrice;
}

void HouseMap2::MatrixGetLonger(int new_y)
{
	char** matrice = new char*[getHeight()];
	int offset;

	if (new_y == top_y)
		offset = 0;
	else if (new_y == bottom_y)
		offset = -1;
	else
		return;

	char *temp_row = new char[getWidth()];
	fill(temp_row, temp_row + getWidth(), '?');
	
	for (int row = 0; row < getHeight(); row++)
	{
		matrice[row] = new char[getWidth()];
		if (row == (new_y - bottom_y))
			memcpy(matrice[row], temp_row, getWidth());
		else
			memcpy(matrice[row], matrix[row + offset], getWidth());		
	}

	delete[] temp_row;
	delete[] matrix;
	matrix = matrice;
}


Location HouseMap2::ConvertToLocation(int x, int y) const
{
	return Location(x + leftmost_x, y + bottom_y);
}

Location HouseMap2::ConvertLocationToMatrixCompatible(Location loc) const
{
	return Location(loc.x - leftmost_x, loc.y - bottom_y);
}
bool HouseMap2::IsDestinationFound(Location loc, MAP_CHAR ch)
{
	switch (ch)
	{
		//used for searching the closest unknown cell
	case MAP_CHAR_N_CLOSEST:
		if ((*this)[loc] == 'N')
			return true;
		break;
	case MAP_CHAR_N_BORDER:
		if (IsCellOnBorder(loc) && (*this)[loc] == 'N')
			return true;
		break;
	case MAP_CHAR_Q:
		if ((*this)[loc] != '?')
			return true;
		break;
	case MAP_CHAR_Q_BORDER:
		if (IsCellOnBorder(loc) && (*this)[loc] == '?')
			return true;
		break;
	case MAP_CHAR_DIRT:
		if (isdigit((*this)[loc]) && ((*this)[loc] != '0'))
			return true;
		break;
		//default is search for docking
	default:
		if ((*this)[loc] == 'D')
			return true;
		break;

	}
	return false;
}

//TODO: check there's no confusion of rows and cols with x and y
//working with locations - format (x, y), values include negatives
bool HouseMap2::bfs(Location robot, vector<Location> &shortestPathToDest, MAP_CHAR ch)
{
	queue<Location> Q;
	map<Location, Location> parent;
	Q.push(robot);
	parent[robot] = robot;
	Location destination = robot;
	while (!Q.empty())
	{
		Location point = Q.front();
		Q.pop();
		if (IsDestinationFound(point, ch)) //destination found
		{
			destination = point;
			break;
		}
		/*
		if (matrix[point.first][point.second] == 'D') //docking found
		{
		destination = point;
		break;
		}*/
		//add neighbors to queue
		vector<Location> neighbors;
		neighbors.push_back(Location(point.x - 1, point.y));
		neighbors.push_back(Location(point.x, point.y - 1));
		neighbors.push_back(Location(point.x + 1, point.y));
		neighbors.push_back(Location(point.x, point.y + 1));
		for (auto& neighbor : neighbors)
		{
			int col = neighbor.x;
			int row = neighbor.y;
			Location loc(col, row);

			if (IsOutOfBorder(loc) || (*this)[loc] == 'W')
				continue; // don't add neighbor to queue - outside of house's bounderis or is a wall
			if (ch != MAP_CHAR_Q && (*this)[loc] == '?')
				continue; // don't add neighbor to queue - is undiscovered cell, might be a wall

			if (parent.find(neighbor) == parent.end()) //add neighbor to queue only if it wasn't visited yet...
			{
				parent[neighbor] = point;
				Q.push(neighbor);
			}
		}
	}
	if (!IsDestinationFound(destination, ch))
		return false;

	//no need to construct a path, used only to check
	if (ch == MAP_CHAR_Q)
		return true;

	//reconstruct path from robot to destination
	Location point = destination;
	shortestPathToDest.clear();
	while (!(point == robot))
	{
		shortestPathToDest.push_back(point);
		point = parent[point];
	}
	//shortestPathToDest.push_back(robot);
	//std::reverse(shortestPathToDest.begin(), shortestPathToDest.end());

	return true;
}

//checks if border cell '?' has a route to non wall cell
bool HouseMap2::IsReachableBorder(Location loc)
{
	// run shortestPath from the current cell with char_map_q
	vector<Location> shortestPathToDocking;
	return bfs(loc, shortestPathToDocking, MAP_CHAR_Q);
}

//check if one of the neighboring cells is already checked as not reachable
bool HouseMap2::IsNeighborInSet(const Location& loc, const set<Location>& checkedCellsSet) const
{
	for (int dir = 0; dir < 4; dir++)
	{
		Location neighbor = loc + Direction(dir);
		if (checkedCellsSet.find(neighbor) != checkedCellsSet.end())
			return true;
	}
	return false;
}

//works on map
bool HouseMap2::IsBordersDiscovered()
{
	if (borders_discovered)
		return true;

	set<Location> checkedCellsSet;

	for (int i = leftmost_x; i <= rightmost_x; i++)
	{
		for (int j = bottom_y; j <= top_y; j++)
		{
			Location houseCell(i, j);
			if (!IsCellOnBorder(houseCell)) continue;

			if ((*this)[houseCell] == 'N') return false;

			if ((*this)[houseCell] == '?')
			{
				//cell is unreachable if neighbor cells are unreachable
				if (IsNeighborInSet(houseCell, checkedCellsSet))
					continue;
				if (IsReachableBorder(houseCell)) return false;

				//this cell is unreachable, add it to the list
				checkedCellsSet.insert(houseCell);
			}
		}
	}

	borders_discovered = true;

	if (!matrix_mode)
	{
		matrix_mode = true;
		matrix = MapToMatrice();
	}
	return true;
}

//in terms of location - with negative values
bool HouseMap2::IsCellOnBorder(Location loc) const
{
	return loc.y == bottom_y || loc.y == top_y || loc.x == leftmost_x || loc.x == rightmost_x;
}

bool HouseMap2::IsNeighbor(const Location& loc1, const Location& loc2) const
{
	if (abs(loc1.x - loc2.x) == 1 && (loc1.y == loc2.y))
		return true;
	if (abs(loc1.y - loc2.y) == 1 && (loc1.x == loc2.x))
		return true;
	return false;
}

void HouseMap2::printMe(const Location& loc) {
	return;
	if (matrix_mode)
	{
		char *temp_row = new char[1 + getWidth()];
		//bool haveLocation = !(loc == Location(0, 0));

		Location matrix_loc = ConvertLocationToMatrixCompatible(loc);

		PRINT_DEBUG("HouseMap2 print me");
		/*cout << '\n' << this->name.c_str() << '\n'
		<< '\n' << "maxSteps: " << this->maxSteps << '\n'
		<< '\n' << "Docking: " << docking << endl;*/
		//if (haveLocation)
		cout << "current Location: " << matrix_loc << endl;

		for (int i = 0; i < getHeight(); i++){
			memcpy(temp_row, matrix[i], getWidth());
			temp_row[getWidth()] = '\0';
			if (i == matrix_loc.y){	//robot's location available 
				//if (haveLocation)
				temp_row[matrix_loc.x] = 'R';	//put robot's symbol on house map
			}
			cout << temp_row << endl;
		}
		cout << endl;
		delete[] temp_row;
	}
	else
	{
		for (int i = bottom_y; i <= top_y; i++)
		{
			for (int j = leftmost_x; j <= rightmost_x; j++)
			{
				Location map_loc = ConvertLocationToMatrixCompatible(loc);
				char ch = (*this)[loc];
				if (map_loc.y == 2 && map_loc.x == 2)
					ch = ch;
				if (loc.y == i && loc.x == j)
					cout << 'R';
				else
					cout << (*this)[Location(j, i)];
			}
			cout << endl;
		}
	}
}
