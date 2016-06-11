/***************************************************************************************/
/*Authors:                                                                             */
/*karinavesker (312908205)                                                             */
/*itaifriedman (301354288)                                                             */
/***************************************************************************************/

#include "Location.h"


void Location::printMe(ostream& out = cout)const{
	out << '(' << x << ", " << y << ')';
}

Location Location::operator+(const Direction& dir) const{
	int dx = 0, dy = 0;

	switch (dir){
	case Direction::Stay:
		break;
	case Direction::East:
		dx = 1;
		break;
	case Direction::West:
		dx = -1;
		break;
	case Direction::North:
		dy = -1;
		break;
	case Direction::South:
		dy = 1;
		break;
	}
	return Location(this->x + dx, this->y + dy);
}

Direction Location::operator-(const Location& loc) const{
	int dx = this->x - loc.x, dy = this->y - loc.y;

	if (dx > 0)
		return RIGHT;
	if (dx < 0)
		return LEFT;
	if (dy > 0)
		return DOWN;
	if (dy < 0)
		return UP;

	return HERE;
}

bool Location::IsNeighbor(const Location& loc2) const
{
	if (abs(this->x - loc2.x) == 1 && (this->y == loc2.y))
		return true;
	if (abs(this->y - loc2.y) == 1 && (this->x == loc2.x))
		return true;
	return false;
}




bool Location::operator == (const Location& other) const{
	return ((this->x == other.x) && (this->y == other.y));
}
