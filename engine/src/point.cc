#include "point.h"

Point::Point(): Point(0,0)
{

}

Point::Point(double a, double b)
{
    x = a;
    y = b;
}

void Point::Set(double a, double b)
{
    x = a;
    y = b;
}
