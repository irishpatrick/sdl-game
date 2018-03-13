#include "game.h"
#include "background.h"
#include "player.h"

Game::Game(SDL_Renderer* r): engine::State(r) {
}

Game::~Game() {
    delete player;
    delete background;
}

void Game::init() {
    std::string assets = "../../games/runner/assets/";

    engine::Assets::loadTexture(assets + "player.png", renderer);
    engine::Assets::loadTexture(assets + "background.png", renderer);

    engine::Assets::getFutures();

    player = new Player();
    player->x = 30;
    player->y = 440 - player->h;
    player->setGround(440);

    background = new Background();

}

void Game::update(float delta, const uint8_t* keys) {
    if (keys[SDL_SCANCODE_SPACE]) {
        player->jump(40);
    }

    player->update(delta);
    background->update(delta);
}

void Game::render() {
    background->draw(renderer);
    player->draw(renderer);
}
