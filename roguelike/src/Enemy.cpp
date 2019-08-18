#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::init(Context& ctx)
{
    setTexture(Assets::getTexture("enemy.png"));
}
