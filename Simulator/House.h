
#ifndef SIMULATOR_HOUSE_H
#define SIMULATOR_HOUSE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include "Point.h"
#include "Montage.h"
#include "Encoder.h"
//#include "common.h"

using namespace std;

class House
{

    Point docking = Point(-1, -1);

public:
    int rows;
    int columns;
    char** house;
    string desc;
    string name;
    int maxSteps;

    House(int houseRows, int houseColumns, char** _house);
    House(int rows, int columns);
    House(const House& aHouse);
    House operator=(House& h);
    ~House();

    enum ItemType {DOCKING = 'D', WALL = 'W'};

    char point(Point point) const;
    void setPoint(Point point, char value);
    Point findDocking();
    Point find(char itemType);
    bool isPointValid(Point p) const;

	bool isWall(Point point) const;
    int dirtLevel(Point point) const;
    int cleanOneUnit(Point& point);
    int amountOfDirt();
};


#endif //SIMULATOR_HOUSE_H
