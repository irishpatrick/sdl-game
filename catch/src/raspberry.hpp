#pragma once

#define MIN_SPEED 30
#define MAX_SPEED 100

#include <engine.hpp>

class Raspberry : public engine::KeyFrameSprite {

public:
	Raspberry();
	~Raspberry();

	void init(engine::Context&);
	void update(float);
	void draw(engine::Context&);
	void caught();
	void reset();

private:
	float fallSpeed;
	engine::Timer timer;
};