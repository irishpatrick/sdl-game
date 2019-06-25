#include "Dungeon.hpp"

Dungeon::Dungeon()
{

}

Dungeon::~Dungeon()
{

}

void Dungeon::init(Context& ctx)
{
    player.setTexture(Assets::getTexture("player.png"));
}

void Dungeon::update(float delta)
{
    const uint8_t* keys = SDL_GetKeyboardState(nullptr);
    int w = keys[SDL_SCANCODE_W];
    int s = keys[SDL_SCANCODE_S];
    int a = keys[SDL_SCANCODE_A];
    int d = keys[SDL_SCANCODE_D];

    if (w)
    {
        player.y -= 100 * delta;
    }
    if (s)
    {
        player.y += 100 * delta;
    }
    if (a)
    {
        player.x -= 100 * delta;
    }
    if (d)
    {
        player.x += 100 * delta;
    }
}

void Dungeon::render(Context& ctx)
{
    player.draw(ctx);
}
