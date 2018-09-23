#include "raspberry.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Raspberry::Raspberry() : engine::KeyFrameSprite()
{

}

Raspberry::~Raspberry()
{

}

void Raspberry::init(engine::Context& ctx)
{
	KeyFrameSprite::init(ctx, fs::path(fs::current_path() / fs::path("assets/raspberry.json")).generic_string());
	setBoundingBox(0, 0, w, h);
	setSolid(true);
	reset();
	setCurrentAnimation("fall", true);
}

void Raspberry::reset()
{
	x = rand() % (640 - w);
	y = -1 * (rand() % (300 - 100) + 100);
	fallSpeed = rand() % (MAX_SPEED - MIN_SPEED) + MIN_SPEED;
}

void Raspberry::velocityUpdate(float delta)
{
	KeyFrameSprite::update(delta);
	if (!visible)
	{
		return;
	}

	if (y > 580) {
		reset();
	}

	y += fallSpeed * delta;
}

void Raspberry::draw(engine::Context& ctx)
{
	//Sprite::draw(ctx);
	KeyFrameSprite::draw(ctx);
}