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
    ball.serve(ctx, 0);
    player.init(ctx);
    opponent.init(ctx);

    long now;
    long then = SDL_GetTicks();
    float delta;

    // main loop
    while (1)
    {
        now = SDL_GetTicks();
        delta = (now - then) / 1000.0f;
        then = now;

        ctx.pollEvents();

        const uint8_t* keys = SDL_GetKeyboardState(NULL);

        int left = keys[SDL_SCANCODE_LEFT];
        int right = keys[SDL_SCANCODE_RIGHT];
        int space = keys[SDL_SCANCODE_SPACE];

        if (space)
        {
            ball.serve(ctx, 0);
        }

        if (left && right)
        {

        }
        else if (left)
        {
            player.left(delta);
        }
        else if (right)
        {
            player.right(delta);
        }

        player.checkAndHit(ctx, &ball);
        opponent.checkAndHit(ctx, &ball);

        player.update(delta);
        opponent.update(delta);
        ball.update(delta);

        ctx.clear();

        //court.draw(ctx);
        opponent.draw(ctx);
        ball.draw(ctx);
        player.draw(ctx);

        ctx.render();
    }

    return 0;
}