#pragma once

#include "core_api.hpp"
#include "Point.hpp"

namespace engine
{

	class Line
	{
	public:
		CORE_API Line();
		CORE_API Line(double, double, double, double);
		CORE_API ~Line();

		CORE_API double solve(double);
        CORE_API double solveInverse(double);
        CORE_API void fit(Point, Point);

	private:
		double m;
		double b;
	};

}
