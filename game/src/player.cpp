#include "player.hpp"

Player::Player(): Sprite()
{

}

Player::~Player()
{

}

void Player::init(engine::Context& ctx) {
	setTexture(engine::Assets::getTexture("hero.png"));
	setMaxSpeed(250.0f);
	name = "hero";
	setBoundingBox(0, 0, w, h);

	queryTexture();
}

json Player::toJson() {
    json o;

    int i = 0;
    for (auto& e : inventory) {

        o["inventory"][i++] = e;
    }

	return o;
}

engine::LocationStack* Player::getDoorStack()
{
    return &doorstack;
}
