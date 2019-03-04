#pragma once

#include "core_api.hpp"
#include <string>
#include <sstream>

namespace engine
{

    class BoundingBox
	{
    public:
        CORE_API BoundingBox(float ax = 0.0f, float ay = 0.0f, float aw = 0.0f, float ah = 0.0f): x(ax), y(ay), w(aw), h(ah) {}
        CORE_API ~BoundingBox() {}

        CORE_API bool isInside(BoundingBox&);
		CORE_API std::string str();

        float x;
        float y;
        float w;
        float h;
    };
}
