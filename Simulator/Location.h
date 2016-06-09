
#ifndef _LOCATION
#define _LOCATION

#include <iostream>
#include "Direction.h"
#include "common.h"

using namespace std;

struct Location{
	Location() : Location(0, 0){}
	Location(int _x, int _y) : x(_x), y(_y){}
	Location(const Location& loc) : x(loc.x), y(loc.y){}	//copy constructor

	void printMe(ostream& out)const;

	//Operators
	Location operator+(const Direction& dir) const;
	Direction operator-(const Location& loc) const;

	void operator=(const Location& loc){
		this->x = loc.x;
		this->y = loc.y;
	}

	bool operator==(const Location& other) const;
	friend ostream& operator<<(ostream& out, const Location& p) { p.printMe(out); return out; }
	friend bool operator<(const Location& p1, const Location& p2) {
		if (p1.y == p2.y) return p1.x < p2.x;
		return p1.y < p2.y;
	}

	bool IsNeighbor(const Location& loc2) const;

	//Members
	int x;
	int y;
};


#endif	//_LOCATION
