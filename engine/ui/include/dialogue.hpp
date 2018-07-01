#pragma once

#include "ui_api.hpp"
#include "config.hpp"

#include <engine.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

namespace ui {

class Dialogue {

public:
    UI_API Dialogue();
    UI_API ~Dialogue();

    //UI_API void initFont(engine::Texture*);
    UI_API inline void setWidth(uint32_t a, uint32_t b) {
        width = a;
        height = b;
    }

    UI_API inline bool isVisible() {
        return visible;
    }

    UI_API inline engine::ImageFont& getFont() {
        //return font;
        return *Config::getFont();
    }

    UI_API void push(const std::string&);
    UI_API void pop();
    UI_API void render(engine::Context*);

    float x;
    float y;

private:
    bool visible;
    //engine::ImageFont font;
    std::vector<std::string> stack;
    uint32_t width;
    uint32_t height;
};

}
