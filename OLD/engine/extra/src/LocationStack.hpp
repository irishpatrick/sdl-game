#pragma once

#include "core_api.hpp"
#include <cstdio>
#include <vector>
#include "Point.hpp"

namespace engine
{

class LocationStack
{
public:
	CORE_API LocationStack();
	CORE_API ~LocationStack();

	CORE_API void push(Point);
	CORE_API Point& pop();
	CORE_API bool isEmpty();
	CORE_API void clear();

private:
    std::vector<Point> stack;
};

}
