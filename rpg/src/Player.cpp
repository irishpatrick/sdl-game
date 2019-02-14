#include "Player.hpp"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Player::Player(): KeyFrameSprite()
{

}

Player::~Player()
{

}

void Player::init(engine::Context& ctx) {
	KeyFrameSprite::init(ctx, (fs::current_path() / "assets" / "sprites" / "player.json").generic_string());
	setMaxSpeed(10.0f);
	name = "hero";
	setBoundingBox(0, 0.35f * h, w, 0.65 * h);
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
