#include "Dungeon.hpp"

Dungeon::Dungeon()
{

}

Dungeon::~Dungeon()
{

}

void Dungeon::init(Context& ctx)
{
    grid.load(ctx, "assets/maps/grid.json");
    grid.addChild(&player);
    grid.addChild(&chest);
    grid.addChild(&enemy);

    player.setGridPos(2, 2);
    player.setTexture(Assets::getTexture("player.png"));

    chest.init(ctx);
    chest.setGridPos(4, 4);
    chest.fill();

    enemy.init(ctx);
    enemy.setGridPos(6, 6);

    test.pushOption(ctx, "test");

    textTest.create(ctx, "Hello World");
    ref.create(ctx, 1024, 1024);
    cairo_t* cr = ref.getCairo();
    //cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    //cairo_paint(cr);
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    cairo_arc(cr, 50, 50, 50, 0, 2 * M_PI);
    cairo_fill(cr);
}

void Dungeon::update()
{
    const uint8_t* keys = SDL_GetKeyboardState(nullptr);
    int w = keys[SDL_SCANCODE_W];
    int s = keys[SDL_SCANCODE_S];
    int a = keys[SDL_SCANCODE_A];
    int d = keys[SDL_SCANCODE_D];
    int p = keys[SDL_SCANCODE_P];
    prompt.check(p);

    if (!w && !s && !a && !d)
    {
        
    }
    else if (w)
    {
        player.up();
    }
    else if (s)
    {
        player.down();
    }
    else if (a)
    {
        player.left();
    }
    else if (d)
    {
        player.right();
    }

    if (prompt.fire())
    {
        player.prompt();
    }

    player.update();
}

void Dungeon::render(Context& ctx, float ex)
{
    grid.draw(ctx, ex);
    chest.draw(ctx, ex);
    player.draw(ctx, ex);
    enemy.draw(ctx, ex);
    test.draw(ctx, ex);
}
