#include "point.hpp"

namespace engine {

	Point::Point(): Point(0.0f,0.0f) {

	}

	Point::Point(float a, float b) {
		x = a;
		y = b;
	}

	void Point::set(float a, float b) {
		x = a;
		y = b;
	}

}
