#pragma once

#include <engine.hpp>
#include "Player.hpp"

using namespace engine;

class Opponent : public Player
{
public:
    Opponent() {}
    ~Opponent() {}

    void init(Context& ctx);
};