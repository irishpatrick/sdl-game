#include "Enemy.hpp"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

engine::Sprite* Enemy::target = nullptr;

Enemy::Enemy(): KeyFrameSprite()
{

}

Enemy::~Enemy()
{

}

void Enemy::init(engine::Context& ctx) 
{
	KeyFrameSprite::init(ctx, (fs::current_path() / "assets" / "sprites" / "enemy.json").generic_string());
}

void Enemy::update(float delta)
{
	KeyFrameSprite::update(delta);
}

void Enemy::setTarget(engine::Sprite& s)
{
    target = &s;
}