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
    void update();
    void draw(Context&);

private:
    Sprite l0;
    Sprite l1;
    Sprite r0;
    Sprite r1;
};
