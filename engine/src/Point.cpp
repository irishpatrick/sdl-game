#include "Point.hpp"

namespace engine
{
	Point::Point(): Point(0.0,0.0)
	{

	}

	Point::Point(double a, double b)
	{
		x = a;
		y = b;
	}

	void Point::set(double a, double b)
	{
		x = a;
		y = b;
	}

	bool Point::equals(Point p)
	{
		return (x == p.x) && (y == p.y);
	}
}
