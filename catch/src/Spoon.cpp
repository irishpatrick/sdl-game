#include "spoon.hpp"
#include <iostream>

Spoon::Spoon(): engine::Sprite() {
	
}

Spoon::~Spoon() {

}

void Spoon::init() {
	setTexture(engine::Assets::getTexture("spoon.png"));
	if (getTexture() == nullptr)
	{
		std::cout << "error: texture was null" << std::endl;
		std::exit(1);
	}
	queryTexture();
	setBoundingBox(0.8f * w, 0.5f * h, w * 0.2f, 0.5f * h);
	setSolid(true);
}