#include "player.h"

Player::Player(): Sprite() {
    setTexture(Assets::getTexture("player.png"));
    ground = 0;
    fall = 0;
}

Player::~Player() {

}

void Player::setGround(float g) {
    ground = g;
}

void Player::jump(float j)
{
    fall -= j;
}

void Player::update(float delta) {
    fall += 18;
    y += fall * delta;

    if (y > ground - h) {
        y = ground - h;
        fall = 0;
    }
}
