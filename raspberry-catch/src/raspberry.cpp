#include "raspberry.hpp"

Raspberry::Raspberry() : engine::Sprite() {
	setTexture(engine::Assets::getTexture("raspberry.png"));
}

Raspberry::~Raspberry() {

}