#pragma once

#include "core_api.hpp"

namespace engine {

class Line
{
public:
	CORE_API Line(float, float, float, float);
	CORE_API ~Line();

	CORE_API float solve(float);

private:
    float m;
    float b;
};

}
