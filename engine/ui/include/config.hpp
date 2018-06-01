#pragma once

#include "ui_api.hpp"
#include "color.hpp"
#include <engine.hpp>

namespace ui {

    class Config {
	public:
		UI_API static engine::ImageFont* getFont();

	private:
		UI_API static engine::ImageFont* font;
		UI_API static Color activeColor;
		UI_API static Color defaultColor;
    };

}