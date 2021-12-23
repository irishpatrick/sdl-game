#include "TennisGame.hpp"

TennisGame::TennisGame() : 
    StateBasedGame()
{

}

void TennisGame::init()
{
    int scale = 8;

    // create context
    ctx.init(39 * scale, 79 * scale, "Tennis", false);
    //ctx.setQuitCallback(&quit_cb);

    // load assets
    Assets::loadTexture(ctx, "assets/ball.png");
    Assets::loadTexture(ctx, "assets/ball_shadow.png");
    Assets::loadTexture(ctx, "assets/cat1.png");
    Assets::loadTexture(ctx, "assets/cat2.png");
    Assets::loadTexture(ctx, "assets/numbers.png");

    this->addState("title", &state_titleScreen);
    this->addState("match", &state_match);

    state_match.init(ctx);

    this->setCurrentState("match");
}
