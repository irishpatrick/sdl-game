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
}
