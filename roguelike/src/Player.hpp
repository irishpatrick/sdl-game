#pragma once

#include <engine.hpp>

using namespace engine;

class Player : public Sprite
{
public:
    Player();
    ~Player();

    void setGridPos(int, int);
    void left();
    void right();
    void up();
    void down();

    void update();

private:
    int gridx;
    int gridy;
    int targx;
    int targy;

    int x_dir;
    int y_dir;
    int speed;
    int moving;
};
