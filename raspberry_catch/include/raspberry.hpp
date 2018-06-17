#pragma once

#include <engine.hpp>

class Raspberry : public engine::Sprite {

public:
	Raspberry();
	~Raspberry();

	void velocityUpdate(float);
	void draw(engine::Context&);
	void reset();

private:
	float fallSpeed;
};