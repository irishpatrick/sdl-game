#include "raspberry.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Raspberry::Raspberry() : engine::Sprite() {
	Sprite::setTexture(engine::Assets::getTexture("raspberry.png"));
	reset();
}

Raspberry::~Raspberry() {

}

void Raspberry::reset() {
	x = rand() % (512 - Sprite::w);
	y = -1 * (rand() % (300 - 100) + 100);
	fallSpeed = rand() % (200 - 80) + 80;
}

void Raspberry::velocityUpdate(float delta) {
	if (!visible) return;

	if (y > 480) {
		reset();
	}

	y += fallSpeed * delta;
}

void Raspberry::draw(engine::Context& ctx) {
	Sprite::draw(ctx);
}