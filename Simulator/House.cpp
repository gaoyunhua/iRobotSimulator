#include <iostream>
#include <stdexcept>
#include "House.h"
#include <unistd.h>
#include <algorithm>

using namespace std;

static const int CleanRatePerUnit = 1;

House::House(int _rows, int _columns, char** _house)
{
    rows = _rows;
    columns = _columns;
    if (rows <= 0 || columns <= 0)
        return;

    house = new char*[_rows];
    for (int i = 0; i < _rows; i++)
    {
        house[i] = new char[_columns];
    }

    for (int i = 0; i < _rows; i++)
        for (int j = 0; j < _columns; j++)
            house[i][j] = _house[i][j];
}

House::House(int houseRows, int houseColumns)
{
    rows = houseRows;
    columns = houseColumns;
    if (rows <= 0 || columns <= 0)
        return;

    house = new char*[houseRows];
    for (int i = 0; i < rows; i++)
    {
        house[i] = new char[columns];
    }
}

House::House(const House& aHouse)
{
    rows = aHouse.rows;
    columns = aHouse.columns;
    if (rows <= 0 || columns <= 0)
        return;

    house = new char*[rows];
    for (int i = 0; i < rows; i++)
    {
        house[i] = new char[columns];
    }

    docking = aHouse.docking;
    name = aHouse.name;
    maxSteps = aHouse.maxSteps;

    if (rows <= 0 || columns <= 0)
        return;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            house[i][j] = aHouse.house[i][j];
}

House House::operator=(House & h) {
    return House(h);
}

House::~House()
{
    if (rows <= 0)
        return;

    for (int i=0; i < rows; i++)
        delete [] house[i];
    delete [] house;
}

bool House::isWall(Point point) const
{
    if (!isPointValid(point))
        return true;

    char item = house[point.getX()][point.getY()];
    return item == House::WALL;
}

bool House::isPointValid(Point point) const
{
    if (point.getX() < 0 || point.getY() < 0 || point.getX() >= rows || point.getY() >= columns)
        return false;

    return true;
}

int House::dirtLevel(Point point) const
{
    char spot = this->point(point);
    if (spot < 49 || spot > 57) // spot < '0' + 1 || spot > '9' => not dust
        return 0;

    return house[point.getX()][point.getY()] - ((char)49);
}

Point House::findDocking()
{
    if (docking.getX() != -1 && docking.getY() != -1)
        return docking;
    return House::find('D');

}

Point House::find(char itemType)
{
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < columns; col++)
        {
            if(house[row][col] == itemType)
            {
                return Point(row, col);
            }
        }
    }
    return Point(-1, -1);
}

int House::cleanOneUnit(Point& point)
{
    char spot = this->point(point);

    if (spot == 'W')
    {
        string message = "Robot crashed into a wall";
        throw invalid_argument(message);
    }

    if (spot < 49 || spot > 57) // spot < '0' + 1 || spot > '9'
        return 0;

    char unitValue = (char) max(0, (spot - CleanRatePerUnit));
    this->setPoint(point, unitValue);

    return spot - unitValue;
}

char House::point(Point point) const
{
    return house[point.getX()][point.getY()];
}

void House::setPoint(Point point, char value)
{
    house[point.getX()][point.getY()] = value;
}

int House::amountOfDirt()
{
    int sumOfDirt = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            sumOfDirt += this->dirtLevel(Point(i, j));
        }
    }

    return sumOfDirt;
}




