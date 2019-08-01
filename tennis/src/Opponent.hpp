#pragma once

#include <engine.hpp>
#include "Player.hpp"

class Ball;

using namespace engine;

class Opponent : public Player
{
public:
    Opponent() :
        dir(0)
    {}
    ~Opponent() {}

    void init(Context& ctx);
    void process(Ball*);
    void update(float) override;

private:
    int dir;
};