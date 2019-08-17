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
    grid.addChild(&player);

    player.setGridPos(2, 2);
    player.setTexture(Assets::getTexture("player.png"));
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
        player.up();
    }
    if (s)
    {
        player.down();
    }
    if (a)
    {
        player.left();
    }
    if (d)
    {
        player.right();
    }

    player.update();
}

void Dungeon::render(Context& ctx, float ex)
{
    grid.draw(ctx, ex);
    player.draw(ctx, ex);
}
