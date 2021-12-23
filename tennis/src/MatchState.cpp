#include "MatchState.hpp"

#include <iostream>

MatchState::MatchState()
{

}

void MatchState::onEntry()
{

}

void MatchState::init(Context& ctx)
{
    court.init(ctx);
    ball.init(ctx);
    player.init(ctx);
    opponent.init(ctx);
    board.init(ctx);
}

void MatchState::update(float e)
{
    Context& ctx = game->getContext();

    const uint8_t* keys = SDL_GetKeyboardState(NULL);

    int left = keys[SDL_SCANCODE_LEFT];
    int right = keys[SDL_SCANCODE_RIGHT];
    int space = keys[SDL_SCANCODE_SPACE];
    int escape = keys[SDL_SCANCODE_ESCAPE];

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
    ball.setShadow(game->getContext());
    ball.update(game->getContext());
    board.update();
}

void MatchState::render(Context& ctx, float e)
{
    court.draw(ctx, e);
    opponent.draw(ctx, e);
    ball.draw(ctx, e);
    player.draw(ctx, e);
    board.draw(ctx);
}

void MatchState::destroy()
{

}
