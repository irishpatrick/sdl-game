#include "Mouse.hpp"
#include <SDL.h>

int Mouse::x = 0;
int Mouse::y = 0;
int Mouse::left = 0;
int Mouse::right = 0;
uint32_t Mouse::state = 0;
float Mouse::scale = 1.0f;

void Mouse::poll()
{
    state = SDL_GetMouseState(&x, &y);
    left = state & SDL_BUTTON(SDL_BUTTON_LEFT);
    right = state & SDL_BUTTON(SDL_BUTTON_RIGHT);
}

void Mouse::setScale(float val)
{
    if (val <= 0)
    {
        scale = 1;
        return;
    }
    scale = val;
}

Point Mouse::getPos()
{
    Point out;
    out.x = x / scale;
    out.y = y / scale;
    return out;
}

int Mouse::getLeft()
{
    return left;
}

int Mouse::getRight()
{
    return right;
}