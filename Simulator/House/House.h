
#ifndef SIMULATOR_HOUSE_H
#define SIMULATOR_HOUSE_H

#include <iostream>
#include "Point.h"

using namespace std;

class House
{
    char** house;
    int rows;
    int columns;
    Point docking = Point(-1, -1);

public:
    House(int houseRows, int houseColumns, char** _house);
    House(int rows, int columns);
    House(const House& aHouse);
    ~House();

    enum ItemType {DOCKING = 'D', WALL = 'W'};

    char point(Point point);
    void setPoint(Point point, char value);
    Point findDocking();
    Point find(char itemType);
    bool isPointValid(Point p);

    bool isWall(Point point);
    int dirtLevel(Point point);
    int cleanOneUnit(Point& point);
    int amountOfDirt();
};


#endif //SIMULATOR_HOUSE_H
