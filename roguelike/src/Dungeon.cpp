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

    menu.init(ctx);
    menu.pushOption(ctx, "option 1");
    menu.pushOption(ctx, "option 2");
    menu.x = 20;
    menu.y = 20;
}

void Dungeon::update()
{
    const uint8_t* keys = SDL_GetKeyboardState(nullptr);
    int w = keys[SDL_SCANCODE_W];
    w_once.check(w);
    int s = keys[SDL_SCANCODE_S];
    s_once.check(s);
    int a = keys[SDL_SCANCODE_A];
    int d = keys[SDL_SCANCODE_D];
    int p = keys[SDL_SCANCODE_P];
    int e = keys[SDL_SCANCODE_E];
    prompt.check(p);

    if (!menu.isVisible())
    {
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
        
        if (e)
        {
            menu.setVisible(true);
        }

        if (prompt.fire())
        {
            player.prompt();
        }
    }
    else
    {
        if (w_once.fire())
        {
            menu.moveCursor(-1);
        }
        if (s_once.fire())
        {
            menu.moveCursor(1);
        }
        if (prompt.fire())
        {
            menu.setVisible(false);
            std::cout << "player chose option " << menu.getChoice() << std::endl;
        }
    }
    

    player.update();
}

void Dungeon::render(Context& ctx, float ex)
{
    grid.draw(ctx, ex);
    chest.draw(ctx, ex);
    player.draw(ctx, ex);
    enemy.draw(ctx, ex);
    menu.draw(ctx, ex);
}
