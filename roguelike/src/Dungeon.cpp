#include "Dungeon.hpp"

Dungeon::Dungeon()
{
    setName("dungeon");
}

Dungeon::~Dungeon()
{

}

void Dungeon::init()
{
    Context& ctx = MyEngine::getContext();
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

    pauseMenu.init(ctx);
    pauseMenu.pushOption(ctx, "Resume");
    pauseMenu.pushOption(ctx, "Save");
    pauseMenu.pushOption(ctx, "Options");
    pauseMenu.pushOption(ctx, "Quit");
    pauseMenu.x = 20;
    pauseMenu.y = 20;
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
    int esc = keys[SDL_SCANCODE_ESCAPE];
    prompt.check(p);

    if (!pauseMenu.isVisible())
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
        
        if (esc)
        {
            pauseMenu.setVisible(true);
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
            pauseMenu.moveCursor(-1);
        }
        if (s_once.fire())
        {
            pauseMenu.moveCursor(1);
        }
        if (prompt.fire())
        {
            pauseMenu.setVisible(false);
            if (pauseMenu.getChoice() == 3)
            {
                exit(0);
            }
        }
    }

    player.update();
}

void Dungeon::render(float ex)
{
    Context& ctx = MyEngine::getContext();
    
    grid.draw(ctx, ex);
    chest.draw(ctx, ex);
    player.draw(ctx, ex);
    enemy.draw(ctx, ex);
    pauseMenu.draw(ctx, ex);
}
