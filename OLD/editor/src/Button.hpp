#pragma once

#include <engine.hpp>

class Button : public engine::Sprite
{
public:
    Button();
    ~Button();

    void update(float);
    void setClickCallback(void (*)(void));
    void setToggle(int);

private:
    static void dummyCallback();
    void (*clickCallback)(void);
    int toggle;
    int status;
};