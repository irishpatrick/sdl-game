#include "game.h"
#include "background.h"
#include "player.h"

Game::Game(SDL_Renderer* r): State(r) {
}

Game::~Game() {
    delete player;
    delete background;
}

void Game::init() {
    std::string assets = "../../runner/assets/";

    Assets::loadTexture(assets + "player.png", renderer);
    Assets::loadTexture(assets + "background.png", renderer);

    Assets::getFutures();

    player = new Player();
    player->x = 10;
    player->y = 10;
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
