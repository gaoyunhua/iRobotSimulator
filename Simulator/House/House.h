
#ifndef SIMULATOR_HOUSE_H
#define SIMULATOR_HOUSE_H

#import <iostream>
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

    char point(Point point);
    void setPoint(Point point, char value);

    bool isWall(Point point);
    int dirtLevel(Point point);
    int cleanOneUnit(Point& point);
    Point findDocking();
    int amountOfDirt();

    enum ItemType {DOCKING = 'D', WALL = 'W', ROBOT = 'R'};
    Point find(ItemType itemType);

    bool isPointValid(Point p);

    void print()
    {
        cout << endl;
        cout << "          1         2         3         4         5         6         7         " << endl;
        cout << "01234567890123456789012345678901234567890123456789012345678901234567890123456789" << endl;
        for(size_t row = 0; row < rows; ++row) {
            cout << house[row] << " " << row << endl;
        }
    }
};


#endif //SIMULATOR_HOUSE_H
