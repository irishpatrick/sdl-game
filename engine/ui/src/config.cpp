#include "config.hpp"

namespace ui {
	engine::ImageFont* Config::font = nullptr;
	Color Config::activeColor = Color();
	Color Config::defaultColor = Color();
    
	engine::ImageFont* Config::getFont() {
		return font;
	}

}