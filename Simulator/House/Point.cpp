
#include "Point.h"

void Point::move(Direction d)
{
    const static function<void(Point&)> do_move[] = {
            [](Point&p){++p.x;}, // East
            [](Point&p){--p.x;}, // West
            [](Point&p){++p.y;}, // South
            [](Point&p){--p.y;}  // North
    };
    do_move[(int)d](*this);
}

void Point::move(Point& p)
{
    x = p.x;
    y = p.y;
}

Point Point::GetPointByDirection(const Point& point, Direction d)
{
    Point localPoint = Point(point);
    const static function<void(Point&)> do_move[] = {
            [](Point& p){ ++p.x; }, // East
            [](Point& p){ --p.x; }, // West
            [](Point& p){ ++p.y; }, // South
            [](Point& p){ --p.y; }  // North
    };
    do_move[(int)d](localPoint);
    return localPoint;
}

Point::Point(const Point &point)
{
    x = point.x;
    y = point.y;
}
