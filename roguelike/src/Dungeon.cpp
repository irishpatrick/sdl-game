#include "Dungeon.hpp"
#include "Inventory.hpp"

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

    text.init();
    text.x = 20;
    text.y = 20;
}

void Dungeon::update()
{
    Keyboard::poll();

    if (!pauseMenu.isVisible())
    {
        if (!Keyboard::isDown("w") &&
            !Keyboard::isDown("a") &&
            !Keyboard::isDown("s") &&
            !Keyboard::isDown("d"))
        {
            
        }
        else if (Keyboard::isDown("w"))
        {
            player.up();
        }
        else if (Keyboard::isDown("s"))
        {
            player.down();
        }
        else if (Keyboard::isDown("a"))
        {
            player.left();
        }
        else if (Keyboard::isDown("d"))
        {
            player.right();
        }

        if (Keyboard::isPressed("e"))
        {
            Inventory* i = dynamic_cast<Inventory*>(MyEngine::getState("inventory"));
            if (i != nullptr)
            {
                i->fill(&player);
                MyEngine::setCurrentState("inventory");
            }
        }
        
        if (Keyboard::isPressed("escape"))
        {
            pauseMenu.setVisible(true);
        }

        if (Keyboard::isPressed("p"))
        {
            player.prompt();
        }

        if (Keyboard::isPressed("l"))
        {
            text.fillDialogue("hello world");
            text.play();
        }
    }
    else if (pauseMenu.isVisible())
    {
        if (Keyboard::isPressed("w"))
        {
            pauseMenu.moveCursor(-1);
        }
        if (Keyboard::isPressed("s"))
        {
            pauseMenu.moveCursor(1);
        }
        if (Keyboard::isPressed("p"))
        {
            if (pauseMenu.getChoice() == 3)
            {
                exit(0);
            }
            pauseMenu.setVisible(false);
        }
    }
    else if (text.isVisible())
    {
        if (Keyboard::isPressed("p"))
        {
            text.play();
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
    text.draw(ex);
    pauseMenu.draw(ctx, ex);
}
