#include "config.hpp"

namespace ui {
	engine::ImageFont Config::font = engine::ImageFont();
	engine::Color Config::activeColor = engine::Color();
	engine::Color Config::defaultColor = engine::Color();

	engine::Color& Config::getActiveColor() {
		return activeColor;
	}

	engine::Color& Config::getDefaultColor() {
		return defaultColor;
	}
    
	engine::ImageFont* Config::getFont() {
		return &font;
	}

	void Config::initFont(engine::Texture* t, float scale) {
		font.setTexture(t);
		font.setScale(scale);
		font.buildMap();
	}

	void Config::setActiveColor(uint8_t r, uint8_t g, uint8_t b) {
		activeColor.set(r, g, b);
	}

	void Config::setDefaultColor(uint8_t r, uint8_t g, uint8_t b) {
		defaultColor.set(r, g, b);
	}

}