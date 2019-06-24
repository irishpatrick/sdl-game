#include <iostream>

#include <engine.hpp>
#include "Game.hpp"
#include "Dungeon.hpp"

using namespace engine;

void quit_cb()
{
    exit(1);
}

int main(int argc, char** argv)
{
    std::cout << "hello world\n";

    //Game game;
    StateBasedGame game;
    Dungeon dungeon;
    Context ctx;

    game.addState("dungeon", &dungeon);
    game.setCurrentState("dungeon");

    ctx.init(512, 480, "Roguelike", false);

    while (1)
    {
        ctx.clear();

        ctx.setQuitCallback()

        ctx.render();
    }

    return 0;
}