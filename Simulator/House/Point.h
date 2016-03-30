
#ifndef SIMULATOR_POINT_H
#define SIMULATOR_POINT_H

#include <iostream>
#include <functional>
#include "Direction.h"

using namespace std;


class Point
{
    int x, y;

public:
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point(const Point& point);

    int getX()const {return x;}
    int getY()const {return y;}
    void move(Direction d);
    static Point GetPointByDirection(const Point& point, Direction d);

    bool equals(Point _point) { return this->x == _point.x && this->y == _point.y; }

    //    Point distance(const Point& other)const {
//        return Point(x - other.x, y - other.y);
//    }
//    void setX(int _x) {x = _x;}
//    void setY(int _y) {y = _y;}
    void move(Point &p);
};

#endif //SIMULATOR_POINT_H
