#include "Color.hpp"

namespace engine {

	Color::Color(uint8_t r, uint8_t g, uint8_t b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	Color::~Color() {

	}

	uint8_t Color::getChannel(uint8_t flag) {
		switch (flag) {

		case RED:
			return r;

		case GREEN:
			return g;

		case BLUE:
			return b;

		default:
			std::cout << "ui::Color::getChannel(" << flag << ") bad flag" << std::endl;
			return 0;
		}
	}

}
