#include "Hud.hpp"
#include "Player.hpp"
#include <iostream>

Hud::Hud() :
    Sprite(),
    player(nullptr)
{

}

Hud::~Hud()
{

}

void Hud::init()
{
    Context& ctx = MyEngine::getContext();

    heart.init(ctx);
    heart.setTexture(Assets::getTexture("heart.png"));
    heart.x = 10;
    heart.y = 10;
}

void Hud::setPlayer(Player* p)
{
    player = p;
}

void Hud::draw()
{
    if (player == nullptr)
    {
        return;
    }

    Context& ctx = MyEngine::getContext();

    int hearts = player->getStats().getHp();
    for (int i = 0; i < hearts; ++i)
    {
        heart.draw(ctx, 0.0f, Point(i * (20), 0));
    }

    if (player->getWeapon() != nullptr)
    {
        player->getWeapon()->draw(ctx, 0.0f, Point(ctx.getWidth() - 64, 32));
    }
}
