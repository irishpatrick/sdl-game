#include <iostream>
#include <cstdlib>
#include <engine.hpp>

#include "Player.hpp"
#include "Opponent.hpp"
#include "Ball.hpp"
#include "Court.hpp"


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
    Court crt;

    int scale = 12;

    // create context
    ctx.init(39 * scale, 79 * scale, "Tennis", false);
    //
    //ctx.init(500, 1000, "Tennis", false);
    ctx.setQuitCallback(&quit_cb);

    // load assets
    Assets::loadTexture(ctx, "assets/court.png");
    Assets::loadTexture(ctx, "assets/ball.png");
    Assets::loadTexture(ctx, "assets/ball_shadow.png");
    Assets::loadTexture(ctx, "assets/player.png");
    Assets::loadTexture(ctx, "assets/opponent.png");

    court.setTexture(Assets::getTexture("court.png"));
    court.scale((float)scale);
    court.x = ctx.getWidth() / 2 - court.getScaledWidth() / 2;
    court.y = ctx.getHeight() / 2 - court.getScaledHeight() / 2;

    crt.init(ctx);
    ball.init(ctx);
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
        int escape = keys[SDL_SCANCODE_ESCAPE];

        if (escape)
        {
            quit_cb();
        }

        if (ball.isVisible())
        {
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
        }
        else
        {
            player.x = ctx.getWidth() / 2 - player.w / 2;
            opponent.x = ctx.getWidth() / 2 - opponent.w / 2;

            if (space)
            {
                ball.serve(ctx, &player);
            }
        }

        crt.contain(&player);
        crt.contain(&opponent);

        opponent.process(&ball);

        player.checkAndHit(crt.getBounds(), &ball);
        opponent.checkAndHit(crt.getBounds(), &ball);

        crt.update(ctx, delta);
        player.update(delta);
        opponent.update(delta);
        ball.setShadow(ctx);
        ball.update(ctx, delta);

        ctx.clear();

        //court.draw(ctx);
        crt.draw(ctx);
        opponent.draw(ctx);
        ball.draw(ctx);
        player.draw(ctx);

        ctx.render();
    }

    return 0;
}