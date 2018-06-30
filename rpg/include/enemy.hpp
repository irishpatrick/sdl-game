#pragma once

#include <engine.hpp>

class Enemy : public engine::Sprite {
public:
    Enemy();
    ~Enemy();

    void init(engine::Context&);
    void velocityUpdate(float);

    static void setTarget(engine::Sprite&);

private:
    static engine::Sprite* target;
};