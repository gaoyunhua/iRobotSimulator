//
// Created by Roni Poyas on 26/03/2016.
// Copyright (c) 2016 ___FULLUSERNAME___. All rights reserved.
//

#ifndef SIMULATOR_POINT_H
#define SIMULATOR_POINT_H

class Point {
    int x, y;
public:
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point distance(const Point& other)const {
        return Point(x - other.x, y - other.y);
    }
    int getX()const {return x;}
    int getY()const {return y;}
};

#endif //SIMULATOR_POINT_H
