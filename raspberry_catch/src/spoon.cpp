#include "spoon.hpp"

Spoon::Spoon(): engine::Sprite() {
	
}

Spoon::~Spoon() {

}

void Spoon::init() {
	setTexture(engine::Assets::getTexture("spoon.png"));
	queryTexture();
	setBoundingBox(w - 200, 0, (w - 200) - w, h);
}