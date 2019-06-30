#include <iostream>

#include <engine.hpp>
#include "Game.hpp"
#include "Dungeon.hpp"
#include "Tilemap.hpp"

using namespace engine;

void quit_cb()
{
    exit(0);
}

int main(int argc, char** argv)
{
    std::cout << "hello world\n";

    StateBasedGame game;
    Dungeon dungeon;
    Context ctx;

    ctx.init(512, 480, "Roguelike", false);
    ctx.setQuitCallback(quit_cb);

    Assets::loadTexture(ctx, "assets/player.png");
    Assets::loadTexture(ctx, "assets/atlas.png");

    dungeon.init(ctx);
    game.addState("dungeon", &dungeon);
    game.setCurrentState("dungeon");

    long now, then;
    float delta;

    then = Timer::getNanoTime();

    while (1)
    {
        now = Timer::getNanoTime();
        delta = (float)(now - then) / 1.0e9f;
        
        ctx.pollEvents();

        game.getCurrentState()->update(delta);

        ctx.clear();

        game.getCurrentState()->render(ctx);

        ctx.render();

        then = now;
    }

    return 0;
}