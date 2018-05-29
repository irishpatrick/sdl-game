#pragma once

#include "core_api.hpp"

namespace engine {

class Point
{
public:
	CORE_API Point();
	CORE_API Point(float, float);

	CORE_API void Set(float, float);

    float x;
    float y;
};

}
