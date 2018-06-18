#pragma once

#include "core_api.hpp"
#include <string>
#include <sstream>

namespace engine {

    class BoundingBox {

    public:
        CORE_API BoundingBox();
        CORE_API ~BoundingBox();

		CORE_API inline std::string str() {
			std::stringstream ss;
			ss << "BoundingBox { x: " << x << ", y: " << y << ", w: " << w << ", h" << h << std::endl;
			return ss.str();
		}

        float x;
        float y;
        float w;
        float h;
    };
}
