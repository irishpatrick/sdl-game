#include "player.h"

Player::Player(): Sprite() {
    setTexture(Assets::getTexture("player.png"));
}

Player::~Player() {

}
