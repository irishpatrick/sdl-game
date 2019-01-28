#include "BoundingBox.hpp"
#include <iostream>

namespace engine
{
	BoundingBox::BoundingBox()
	{
		x = 0.0f;
		y = 0.0f;
		w = 0.0f;
		h = 0.0f;
	}

	BoundingBox::~BoundingBox()
	{

	}

	std::string BoundingBox::str()
	{
		std::stringstream ss;
		ss << "BoundingBox { x: " << x << ", y: " << y << ", w: " << w << ", h" << h << std::endl;
		return ss.str();
	}
}
