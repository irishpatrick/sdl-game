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
    int i;
    int j;
    int x;
    int y;
    int size = 32;
    int len = 32;
    for (i = 0; i < len; ++i)
    {
        for (j = 0; j < len; ++j)
        {
            x = size * j;
            y = size * i;
            Sprite* s = tm.getTile("grass");
            if (s == nullptr)
            {
                break;
            }
            s->x = x;
            s->y = y;
            s->draw(ctx, ex);
        }
    }
    player.draw(ctx, ex);
}
