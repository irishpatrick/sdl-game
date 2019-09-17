#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy() :
    Player()
{

}

Enemy::~Enemy()
{

}

void Enemy::init(Context& ctx)
{
    setTexture(Assets::getTexture("enemy.png"));
}

void Enemy::interact(GridSprite* prompt)
{
    std::cout << "enemy" << std::endl;
}
