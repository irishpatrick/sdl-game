#pragma once

#include "core_api.hpp"

namespace engine
{

class Point
{
public:
	CORE_API Point();
	CORE_API Point(double, double);

	CORE_API void set(double, double);
	CORE_API bool equals(Point);

    double x;
    double y;
};

}
