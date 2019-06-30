#include "Dungeon.hpp"

Dungeon::Dungeon()
{

}

Dungeon::~Dungeon()
{

}

void Dungeon::init(Context& ctx)
{
    tm.setTextureAtlas(Assets::getTexture("atlas.png"));
    tm.extractTextures(ctx, "assets/atlas.txt");

    player.x = 100;
    player.y = 100;
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
        player.translateY(-100 * delta);
    }
    if (s)
    {
        player.translateY(100 * delta);
    }
    if (a)
    {
        player.translateX(-100 * delta);
    }
    if (d)
    {
        player.translateX(100 * delta);
    }
}

void Dungeon::render(Context& ctx)
{
    player.draw(ctx);

}
