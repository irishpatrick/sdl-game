#include <iostream>
#include <cstdlib>
#include <engine.hpp>

#include "Player.hpp"
#include "Opponent.hpp"
#include "Ball.hpp"
#include "Court.hpp"
#include "Stats.hpp"
#include "Scoreboard.hpp"

using namespace engine;

int running = 1;

void quit_cb()
{
    running = 0;
}

#ifdef main
#undef main
#endif
int main(int argc, char** argv)
{
    Clock clock;
    Stats stats;
    Context ctx;
    Player player;
    Opponent opponent;
    Ball ball;
    Court court;
    Scoreboard board;

    int scale = 8;

    // create context
    ctx.init(39 * scale, 79 * scale, "Tennis", false);
    //ctx.init(512, 480, "Tennis", false);
    ctx.setQuitCallback(&quit_cb);

    // load assets
    Assets::loadTexture(ctx, "assets/ball.png");
    Assets::loadTexture(ctx, "assets/ball_shadow.png");
    Assets::loadTexture(ctx, "assets/cat1.png");
    Assets::loadTexture(ctx, "assets/cat2.png");
    Assets::loadTexture(ctx, "assets/numbers.png");

    court.init(ctx);
    ball.init(ctx);
    player.init(ctx);
    opponent.init(ctx);
    board.init(ctx);

    // main loop
    clock.start();
    while (running)
    {
        clock.tick();

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

        while (clock.hasLag())
        {
            if (ball.isVisible())
            {
                if (left && right)
                {

                }
                else if (left)
                {
                    player.left();
                }
                else if (right)
                {
                    player.right();
                }
            }
            else
            {
                player.x = ctx.getWidth() / 2 - player.w / 2;
                opponent.x = ctx.getWidth() / 2 - opponent.w / 2;

                if (space)
                {
                    ball.serve(ctx, &player);
                    opponent.calculate(&ball);
                }
            }

            court.contain(&player);
            court.contain(&opponent);

            opponent.process(&ball);

            int success = 0;
            success = player.checkAndHit(court.getBounds(), &ball);
            if (success)
            {
                opponent.calculate(&ball);
            }

            success = opponent.checkAndHit(court.getBounds(), &ball);

            if (success)
            {
                stats.recordVolley();
            }
            else
            {
                stats.resetVolley();
            }

            court.judge(&ball);

            player.update();
            opponent.update();
            ball.setShadow(ctx);
            ball.update(ctx);

            clock.lagTick();
        }

        ctx.clear();

        double e = clock.extrapolate();

        court.draw(ctx, e);
        opponent.draw(ctx, e);
        ball.draw(ctx, e);
        player.draw(ctx, e);

        ctx.render();
    }

    Assets::destroy();

    return 0;
}
