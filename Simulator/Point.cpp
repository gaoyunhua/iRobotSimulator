
#include "Point.h"

void Point::move(Direction d)
{

    switch ((int)d)
    {
        case 0:
        {
            y++;
            break;
        }
        case 1:
        {
            y--;
            break;
        }
        case 2:
        {
            x++;
            break;
        }
        case 3:
        {
            x--;
            break;
        }
        default:
            break;

    }
}

void Point::move(Point& p)
{
    x = p.x;
    y = p.y;
}

Point Point::GetPointByDirection(const Point& point, Direction d)
{
    Point localPoint = Point(point);
    int directionInt = (int)d;
    switch (directionInt)
    {
        case 0:
        {
            localPoint.y++;
            break;
        }
        case 1:
        {
            localPoint.y--;
            break;
        }
        case 2:
        {
            localPoint.x++;
            break;
        }
        case 3:
        {
            localPoint.x--;
            break;
        }
        default:
            break;

    }
    return localPoint;
}

Point::Point(const Point &point)
{
    x = point.x;
    y = point.y;
}
