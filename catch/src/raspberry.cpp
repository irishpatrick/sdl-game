#include "raspberry.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Raspberry::Raspberry() : engine::Sprite() {
	Sprite::setTexture(engine::Assets::getTexture("raspberry.png"));
	setBoundingBox(0, 0, w, h);
	setSolid(true);
	reset();
}

Raspberry::~Raspberry() {

}

void Raspberry::reset() {
	x = rand() % (640 - w);
	y = -1 * (rand() % (300 - 100) + 100);
	fallSpeed = rand() % (MAX_SPEED - MIN_SPEED) + MIN_SPEED;
}

void Raspberry::velocityUpdate(float delta) {
	if (!visible) return;

	if (y > 580) {
		reset();
	}

	y += fallSpeed * delta;
}

void Raspberry::draw(engine::Context& ctx) {
	Sprite::draw(ctx);
}