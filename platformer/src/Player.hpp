#pragma once

#include <engine.hpp>

class Player : public engine::Sprite
{
public:
    Player() : Sprite() {}
    ~Player() {}

    void jump(float);
};