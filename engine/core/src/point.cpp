#include "point.hpp"

namespace engine {

Point::Point(): Point(0,0)
{

}

Point::Point(float a, float b)
{
    x = a;
    y = b;
}

void Point::Set(float a, float b)
{
    x = a;
    y = b;
}

}
