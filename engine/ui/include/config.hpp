#pragma once

#include "ui_api.hpp"
#include <engine.hpp>

namespace ui {

    class Config {
	public:
		UI_API static engine::ImageFont* getFont();
		UI_API static void initFont(engine::Texture*, float);
        UI_API static void setDefaultColor(uint8_t, uint8_t, uint8_t);
		UI_API static void setActiveColor(uint8_t, uint8_t, uint8_t);
		UI_API static engine::Color& getActiveColor();
		UI_API static engine::Color& getDefaultColor();

	private:
		UI_API static engine::ImageFont font;
		UI_API static engine::Color activeColor;
		UI_API static engine::Color defaultColor;
    };

}
