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
	fs::path assetPath = fs::current_path() / "assets";
}

void Enemy::update(float delta)
{
	KeyFrameSprite::update(delta);
}

void Enemy::setTarget(engine::Sprite& s)
{
    target = &s;
}