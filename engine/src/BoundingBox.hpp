#pragma once

#include "core_api.hpp"
#include <string>
#include <sstream>
#include "Point.hpp"

namespace engine
{

    class BoundingBox
	{
    public:
        CORE_API BoundingBox(float ax = 0.0f, float ay = 0.0f, float aw = 0.0f, float ah = 0.0f): x(ax), y(ay), w(aw), h(ah) {}
        CORE_API ~BoundingBox() {}

        CORE_API void xywh(float, float, float, float);
        CORE_API void corners(float, float, float, float);
        CORE_API bool isInside(BoundingBox&);
		CORE_API std::string str();
        CORE_API Point center();

        float x;
        float y;
        float w;
        float h;
    };
}
