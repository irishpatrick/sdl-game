#pragma once

#include <engine.hpp>

using namespace engine;

class Scoreboard : public Sprite
{
public:
    Scoreboard()
    {}
    ~Scoreboard();

    void init(Context&);

private:
    KeyFrameSprite l0;
    KeyFrameSprite l1;
    KeyFrameSprite r0;
    KeyFrameSprite r1;
};
