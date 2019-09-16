#include "Dungeon.hpp"
#include "Inventory.hpp"
#include "Config.hpp"
#include "Textbox.hpp"

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
    grid.addChild(&npcTest);

    player.setGridPos(2, 2);
    player.setTexture(Assets::getTexture("player.png"));

    chest.init(ctx);
    chest.setGridPos(4, 4);
    chest.fill();

    enemy.init(ctx);
    enemy.setGridPos(6, 6);

    npcTest.init();
    npcTest.setGridPos(2, 6);
    npcTest.setTexture(Assets::getTexture("player.png"));

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
    Keyboard::poll();

    if (!pauseMenu.isVisible() && !Textbox::isVisible())
    {
        if (Keyboard::isDown(Config::getKey("strafe").c_str()))
        {
            player.strafe();
        }
        if (!Keyboard::isDown("w") &&
            !Keyboard::isDown("a") &&
            !Keyboard::isDown("s") &&
            !Keyboard::isDown("d"))
        {
            
        }
        else if (Keyboard::isDown(Config::getKey("up").c_str()))
        {
            player.up();
        }
        else if (Keyboard::isDown(Config::getKey("down").c_str()))
        {
            player.down();
        }
        else if (Keyboard::isDown(Config::getKey("left").c_str()))
        {
            player.left();
        }
        else if (Keyboard::isDown(Config::getKey("right").c_str()))
        {
            player.right();
        }

        if (Keyboard::isPressed(Config::getKey("inventory").c_str()))
        {
            Inventory* i = dynamic_cast<Inventory*>(MyEngine::getState("inventory"));
            if (i != nullptr)
            {
                i->fill(&player);
                MyEngine::setCurrentState("inventory");
            }
        }
        
        if (Keyboard::isPressed(Config::getKey("escape").c_str()))
        {
            pauseMenu.setVisible(true);
        }

        if (Keyboard::isPressed(Config::getKey("primary").c_str()))
        {
            player.prompt();
        }
    }
    else if (pauseMenu.isVisible())
    {
        if (Keyboard::isPressed(Config::getKey("up").c_str()))
        {
            pauseMenu.moveCursor(-1);
        }
        if (Keyboard::isPressed(Config::getKey("down").c_str()))
        {
            pauseMenu.moveCursor(1);
        }
        if (Keyboard::isPressed(Config::getKey("primary").c_str()))
        {
            if (pauseMenu.getChoice() == 3)
            {
                exit(0);
            }
            pauseMenu.setVisible(false);
        }
    }
    else if (Textbox::isVisible())
    {
        if (Keyboard::isPressed(Config::getKey("primary").c_str()))
        {
            Textbox::play();
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
    npcTest.draw(ex);
    Textbox::draw();
    pauseMenu.draw(ctx, ex);
}
