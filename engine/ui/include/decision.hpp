#pragma once

#include "ui_api.hpp"
#include <cstdint>
#include <engine.hpp>

namespace ui {

class Decision {
public:
	UI_API Decision();
	UI_API ~Decision();

	UI_API void update();
	UI_API void draw(engine::Context*);
	UI_API inline bool isVisible() { return visible; }
    UI_API inline void setSelection(uint8_t s) { selected = s; }

    float x;
    float y;

    static const uint8_t YES = 1;
    static const uint8_t NO = 0;

private:
	bool visible;
    engine::ImageFont font;
    uint32_t width;
    uint32_t height;
    uint8_t selected;
};

}
