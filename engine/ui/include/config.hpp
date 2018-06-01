#pragma once

#include "ui_api.hpp"
#include "color.hpp"
#include <engine.hpp>

namespace ui {

    class Config {
	public:
		UI_API static engine::ImageFont* getFont();
        UI_API static void setDefaultColor(uint8_t);

	private:
		UI_API static engine::ImageFont* font;
		UI_API static Color activeColor;
		UI_API static Color defaultColor;
    };

}
