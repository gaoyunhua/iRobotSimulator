
#ifndef __HOUSEMAP2__H_
#define __HOUSEMAP2__H_

#include "Location.h"
#include <map>
#include <vector>
#include "SensorInformation.h"
#include <set>
#include <queue>
#include "common.h"
#include <algorithm>
#include "Debugger.h"

enum MAP_CHAR { MAP_CHAR_D, MAP_CHAR_N_CLOSEST, MAP_CHAR_N_BORDER, MAP_CHAR_Q, MAP_CHAR_Q_BORDER, MAP_CHAR_DIRT };

class HouseMap2
{
	int rightmost_x, leftmost_x;
	int top_y, bottom_y;
	map<Location, char> houseMapLocation;
	char** matrix;
	bool matrix_mode;		//is it a map or matrix
	bool borders_discovered;


public:
	//HouseMap();
	HouseMap2(Location Dock);
	~HouseMap2();
	int getHeight() const;
	int getWidth() const;
	int getSize() const;
	void fillCol(int col, int bottom, int top);
	void fillRow(int row, int leftmost, int rightmost);
	void expandBorders(Location loc);
	bool IsOutOfBorder(Location loc) const;
	char ** MapToMatrice();
	void MatrixGetWider(int new_x);
	void MatrixGetLonger(int new_y);
	Location ConvertToLocation(int x, int y) const;
	Location ConvertLocationToMatrixCompatible(Location loc) const;
	bool IsDestinationFound(Location loc, MAP_CHAR ch);
	bool bfs(Location robot, vector<Location> &shortestPathToDest, MAP_CHAR ch);
	bool IsReachableBorder(Location loc);
	bool IsNeighborInSet(const Location& loc, const set<Location>& set) const;
	bool IsBordersDiscovered();
	bool IsCellOnBorder(Location pos) const;
	bool IsNeighbor(const Location & loc1, const Location & loc2) const;
	void printMe(const Location& loc);
	void UpdateMap(const SensorInformation& sensation, Location cell);
	void addThisCellToMap(const SensorInformation& sensation, Location cell);
	void addNeighborCellsToMap(const SensorInformation& sensation, Location loc);

	void InsertToMap(const Location& loc);

	char& operator[](const Location loc) {
		if (matrix_mode)
			return matrix[loc.y - bottom_y][loc.x - leftmost_x];
		return houseMapLocation[loc];
	}
};

#endif