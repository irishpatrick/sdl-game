#include "BoundingBox.hpp"
#include <iostream>

namespace engine
{
    std::string BoundingBox::str()
	{
		std::stringstream ss;
		ss << "BoundingBox { x: " << x << ", y: " << y << ", w: " << w << ", h" << h << std::endl;
		return ss.str();
	}

    bool BoundingBox::isInside(BoundingBox& box)
    {
        return (
			x < box.x + box.w &&
			x + w > box.x &&
			y < box.y + box.h &&
			y + h > box.y);
    }
}
