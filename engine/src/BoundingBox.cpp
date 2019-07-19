#include "BoundingBox.hpp"
#include <iostream>

namespace engine
{
    void BoundingBox::xywh(float x, float y, float w, float h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    void BoundingBox::corners(float x1, float y1, float x2, float y2)
    {
        x = x1;
        y = y1;
        w = x2 - x1;
        y = y2 - y1;
    }

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

    Point BoundingBox::center()
    {
        return Point(x + w / 2, y + h / 2);
    }
}
