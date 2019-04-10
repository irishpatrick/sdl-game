#pragma once

#include <engine.hpp>

class Slider : public engine::Sprite
{
public:
    Slider();
    ~Slider();

    void init();
    void update(float);
    void draw(engine::Context&);
    void setDragCallback(void(*)(void));

private:
    int ox;
    int oy;
    void (*dragCallback)(void);
}