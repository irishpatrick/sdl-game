#include "Button.hpp"
#include "Mouse.hpp"

void Button::dummyCallback()
{
    
}

Button::Button() : Sprite()
{
    clickCallback = this->dummyCallback;
}

Button::~Button()
{
    
}

void Button::setClickCallback(void (*ptr)(void))
{
    clickCallback = ptr;
}

void Button::setToggle(int v)
{
    toggle = v;
}

void Button::update(float delta)
{
    int mx = Mouse::getPos().x;
    int my = Mouse::getPos().y;

    if (mx > x && 
        mx < x + w &&
        my > y &&
        my < y + h && 
        Mouse::getLeft())
    {
        if (toggle)
        {
            if (!status)
            {
                clickCallback();
                status = 1;
            }
        }
        else
        {
            clickCallback();
        }
    }
    else
    {
        if (!Mouse::getLeft())
        {
            status = 0;
        }
    }
    
}