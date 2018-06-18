#include "spoon.hpp"

Spoon::Spoon(): engine::Sprite() {
	
}

Spoon::~Spoon() {

}

void Spoon::init() {
	setTexture(engine::Assets::getTexture("spoon.png"));
	queryTexture();
	setBoundingBox(0.8f * w, 0.5f * h, w * 0.2f, 0.5f * h);
	setSolid(true);
}