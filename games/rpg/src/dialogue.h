#pragma once

#include <engine.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

class Dialogue {

public:
    Dialogue();
    ~Dialogue();

    void initFont(engine::Texture*);
    inline void setWidth(uint32_t a, uint32_t b) {
        width = a;
        height = b;
    }
    inline bool isVisible() {
        return visible;
    }
    void push(const std::string&);
    void pop();
    void render(engine::Context*);

    float x;
    float y;

private:
    bool visible;
    engine::ImageFont font;
    std::vector<std::string> stack;
    uint32_t width;
    uint32_t height;
};
