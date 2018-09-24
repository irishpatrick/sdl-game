#pragma once

#include <engine.hpp>

class Enemy : public engine::KeyFrameSprite {
public:
    Enemy();
    ~Enemy();

    void init(engine::Context&);
	void update(float);

    static void setTarget(engine::Sprite&);

private:
    static engine::Sprite* target;
};