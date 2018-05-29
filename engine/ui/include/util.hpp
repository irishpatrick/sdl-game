#pragma once

#include "ui_api.hpp"
#include <cstdint>
#include <engine.hpp>

namespace ui {

	class Util {
	public:
		static UI_API void setBorderColor(uint8_t, uint8_t, uint8_t, uint8_t);
		static UI_API void setWindowColor(uint8_t, uint8_t, uint8_t, uint8_t);
		static UI_API void drawWindow(engine::Context*, float, float, uint32_t, uint32_t);

	private:
		static uint8_t fr, fg, fb;
		static uint8_t br, bg, bb;
	};

}
