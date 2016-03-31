
#include "Point.h"

void Point::move(Direction d)
{

    switch ((int)d)
    {
        case 0:
        {
            x++;
        }
        case 1:
        {
            x--;
        }
        case 2:
        {
            y++;
        }
        case 3:
        {
            y--;
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
    switch ((int)d)
    {
        case 0:
        {
            localPoint.x++;
        }
        case 1:
        {
            localPoint.x--;
        }
        case 2:
        {
            localPoint.y++;
        }
        case 3:
        {
            localPoint.y--;
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
