#include "Enemy.hpp"
#include <cstdlib>
#include <ctime>

int randint(int low, int high)
{
    return rand() % (high + 1 - low) + low;
}

Enemy::Enemy() : Ship()
{

}

Enemy::~Enemy()
{

}

void Enemy::init(engine::Context& ctx)
{
    setTexture(engine::Assets::getTexture("enemy.png"));
    reset();
}

void Enemy::reset()
{
    y = -32 - randint(10, 300);
    x = randint(0,15) * 32;
    yvel = randint(30, 60);
}
