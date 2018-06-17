#include "spoon.hpp"

Spoon::Spoon(): engine::Sprite() {
	
}

Spoon::~Spoon() {

}

void Spoon::init() {
	this->setTexture(engine::Assets::getTexture("spoon.png"));
	this->queryTexture();
}