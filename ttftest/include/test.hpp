#pragma once

#include <iostream>
#include <engine.hpp>
#include <SDL2/SDL_ttf.h>

class Test {
public:
    Test();
    ~Test();

    void init();
    void update();
    void draw(engine::Context&);
};
