#include "Slider.hpp"
#include "Mouse.hpp"
#include <cmath>

Slider::Slider() : Sprite()
{
    dragCallback = this->dummyCallback;
    status = 0;
}

Slider::~Slider()
{

}

void Slider::dummyCallback(void*)
{

}

void Slider::update(float delta)
{
    int mx = Mouse::getPos().x;
    int my = Mouse::getPos().y;

    if (status)
    {
        dragCallback((void*)&old);
        if (!Mouse::getRight())
        {

            status = 0;
        }
    }

    if (mx > x && 
        mx < x + w &&
        my > y &&
        my < y + h && 
        Mouse::getRight() &&
        !status)
    {
        status = 1;
        old.x = x + 64;
        old.y = y + 64;
    }
}

Point Slider::getDragDistance()
{
    Point out;
    out.x = Mouse::getPos().x - old.x;
    out.y = Mouse::getPos().y - old.y;
    return out;
}

void Slider::draw(engine::Context& ctx)
{
    Sprite::draw(ctx);
}

void Slider::setDragCallback(void(*ptr)(void*))
{
    dragCallback = ptr;
}