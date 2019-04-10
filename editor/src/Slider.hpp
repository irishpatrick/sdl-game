#pragma once

#include <engine.hpp>
#include "Point.hpp"

class Slider : public engine::Sprite
{
public:
    Slider();
    ~Slider();

    void update(float);
    void draw(engine::Context&);
    void setDragCallback(void(*)(void*));
    Point getDragDistance();
    static void dummyCallback(void*);

private:
    Point old;
    int status;
    void (*dragCallback)(void*);
};