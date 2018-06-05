#include "line.hpp"

namespace engine {

	Line::Line() {
		m = 0;
		b = 0;
	}

	Line::Line(float x1, float y1, float x2, float y2) {
		m = (y2 - y1) / (x2 - x1);
		b = y1 - (m * x1);
	}

	Line::~Line() {

	}

	float Line::solve(float x) {
		return m * x + b;
	}

}
