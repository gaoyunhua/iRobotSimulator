#include <iostream>
#include "House.h"

using namespace std;

House::House(int houseRows, int houseColumns)
{
    rows = houseRows;
    columns = houseColumns;
    house = new char*[houseRows];
    for (int i = 0; i < rows; i++)
    {
        house[i] = new char[columns];
    }
}

House::House(const House& aHouse)
{
    House h = House::House(aHouse.rows, aHouse.columns);
    rows = h.rows;
    columns = h.columns;
    house = h.house;
    docking = h.docking;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            house[i][j] = aHouse.house[i][j];
    }
}

House::~House()
{
    for (int i=0; i < rows; i++)
        delete [] house[i];
    delete [] house;
}

Point House::findDocking()
{
    if (docking.getX() != -1 && docking.getY() != -1)
        return docking;
    return House::find(ItemType::DOCKING);

}

Point House::find(ItemType itemType)
{
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < columns; col++)
        {
            if(house[row][col] == itemType)
            {
                return Point(col, row);
            }
        }
    }
    return Point(-1, -1);
}

void House::SetRobot(Point point)
{
    robot = point;
}

void House::MoveRobot(Direction direction)
{
    robot.move(direction);
}

Point House::findRobot()
{
    if (robot.getX() != -1 && robot.getY() != -1)
        return robot;

    return House::find(ItemType::ROBOT);
}
