#pragma once

#include <engine.hpp>
#include "Player.hpp"

class Ball;

using namespace engine;

class Opponent : public Player
{
public:
    Opponent()
    {}
    ~Opponent() {}

    void init(Context& ctx);
    void calculate(Ball*);
    void process(Ball*);
    //int checkAndHit(BoundingBox&, Ball*) override;

private:
    float target;
};