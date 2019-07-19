#include <iostream>
#include <cstdlib>
#include <engine.hpp>

#include "Player.hpp"
#include "Opponent.hpp"
#include "Ball.hpp"

using namespace engine;

void quit_cb()
{
    exit(0);
}

int main(int argc, char** argv)
{
    // declare game components
    Context ctx;
    Player player;
    Opponent opponent;
    Ball ball;
    Sprite court;

    // create context
    ctx.init(512, 480, "Tennis", false);
    ctx.setQuitCallback(&quit_cb);

    // load assets
    Assets::loadTexture(ctx, "assets/court.png");
    Assets::loadTexture(ctx, "assets/ball.png");
    Assets::loadTexture(ctx, "assets/ball_shadow.png");
    Assets::loadTexture(ctx, "assets/player.png");
    Assets::loadTexture(ctx, "assets/opponent.png");

    court.setTexture(Assets::getTexture("court.png"));
    court.scale(5.0f);
    court.x = ctx.getWidth() / 2 - court.getScaledWidth() / 2;
    court.y = ctx.getHeight() / 2 - court.getScaledHeight() / 2;

    ball.init(ctx);
    player.init(ctx);
    opponent.init(ctx);


    // main loop
    while (1)
    {
        ctx.pollEvents();
        ctx.clear();

        //court.draw(ctx);
        opponent.draw(ctx);
        ball.draw(ctx);
        player.draw(ctx);

        ctx.render();
    }

    return 0;
}