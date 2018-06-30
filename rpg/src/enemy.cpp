#include "enemy.hpp"

engine::Sprite* Enemy::target = nullptr;

Enemy::Enemy(): Sprite() {

}

Enemy::~Enemy() {

}

void Enemy::init(engine::Context& ctx) {

}

void Enemy::velocityUpdate(float delta) {

}

void Enemy::setTarget(engine::Sprite& s) {
    target = &s;
}