#pragma once

#include "core_api.hpp"
#include <string>
#include <sstream>

namespace engine
{

    class BoundingBox
	{

    public:
        CORE_API BoundingBox();
        CORE_API ~BoundingBox();

		CORE_API std::string str();

        float x;
        float y;
        float w;
        float h;
    };
}
