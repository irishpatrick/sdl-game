#include "Dungeon.hpp"

Dungeon::Dungeon()
{

}

Dungeon::~Dungeon()
{

}

void Dungeon::init(Context& ctx)
{
    grid.load(ctx, "assets/grid.json");

    player.x = 100;
    player.y = 100;
    player.setTexture(Assets::getTexture("player.png"));

    grid.addChild(&player);
}

void Dungeon::update()
{
    const uint8_t* keys = SDL_GetKeyboardState(nullptr);
    int w = keys[SDL_SCANCODE_W];
    int s = keys[SDL_SCANCODE_S];
    int a = keys[SDL_SCANCODE_A];
    int d = keys[SDL_SCANCODE_D];

    if (w)
    {
        player.translateY(-1);
    }
    if (s)
    {
        player.translateY(1);
    }
    if (a)
    {
        player.translateX(-1);
    }
    if (d)
    {
        player.translateX(1);
    }
}

void Dungeon::render(Context& ctx, float ex)
{
    grid.draw(ctx, ex);
    player.draw(ctx, ex);
}
