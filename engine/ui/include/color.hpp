#pragma once

#include "ui_api.hpp"
#include <cstdint>
#include <iostream>

namespace ui {

	class Color {
	public:
		UI_API Color(): r(0), g(0), b(0) {}
		UI_API Color(uint8_t, uint8_t, uint8_t);
		UI_API ~Color();

		UI_API uint8_t getChannel(uint8_t);

		UI_API static const uint8_t RED = 0;
		UI_API static const uint8_t GREEN = 1;
		UI_API static const uint8_t BLUE = 2;

	private:
		uint8_t r, g, b;
	};

}