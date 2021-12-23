#include "TitleScreenState.hpp"

TitleScreenState::TitleScreenState()
{

}

void TitleScreenState::init(Context& ctx)
{
    bg.setTexture(Assets::getTexture("title.png"));
    bg.w *= 8;
    bg.h *= 8;
}

void TitleScreenState::update(float ex)
{
    const uint8_t* keys = SDL_GetKeyboardState(NULL);
    int space = keys[SDL_SCANCODE_SPACE];

    if (space)
    {
        StateBasedGame* sbg = (StateBasedGame*)game;
        sbg->setCurrentState("match");
    }
}

void TitleScreenState::render(Context& ctx, float e)
{
    bg.draw(ctx, e);
}