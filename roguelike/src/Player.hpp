#pragma once

#include <engine.hpp>

using namespace engine;

class Player : public Sprite
{
public:
    Player();
    ~Player();

    void translateX(float);
    void translateY(float);

    void attack(Group&);

private:
    int x_dir;
    int y_dir;
};