#pragma once

#include "core_api.hpp"
#include <cstdint>
#include <iostream>

namespace engine {

	class Color {
	public:
		CORE_API Color() : r(0), g(0), b(0) {}
		CORE_API Color(uint8_t, uint8_t, uint8_t);
		CORE_API ~Color();

		CORE_API uint8_t getChannel(uint8_t);
		CORE_API inline void set(uint8_t r, uint8_t g, uint8_t b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}

		CORE_API static const uint8_t RED = 0;
		CORE_API static const uint8_t GREEN = 1;
		CORE_API static const uint8_t BLUE = 2;

	private:
		uint8_t r, g, b;
	};

}