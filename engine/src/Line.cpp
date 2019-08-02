#include "Line.hpp"

namespace engine {

	Line::Line() {
		m = 0.0f;
		b = 0.0f;
	}

	Line::Line(double x1, double y1, double x2, double y2) {
		m = (y2 - y1) / (x2 - x1);
		b = y1 - (m * x1);
	}

	Line::~Line() {

	}

	double Line::solve(double x) {
		return m * x + b;
	}

    double Line::solveInverse(double y)
    {
        return (y - b) / m;
    }

    void Line::fit(Point q, Point r)
    {
        m = (r.y - q.y) / (r.x - q.x);
        b = q.y - m * q.x;
    }

}
