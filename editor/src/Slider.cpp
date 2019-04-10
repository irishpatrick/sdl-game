#include "Slider.hpp"
#include "Mouse.hpp"

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

    if (mx > x && 
        mx < x + w &&
        my > y &&
        my < y + h && 
        Mouse::getLeft() &&
        !status)
    {
        status = 1;
        old.x = mx;
        old.y = my;
    }

    if (status)
    {
        dragCallback((void*)&old);
        if (!Mouse::getLeft())
        {
            status = 0;
        }
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