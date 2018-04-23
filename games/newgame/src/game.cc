#include "game.h"

Game::Game(engine::Context* ctx): engine::State(ctx) {

}

Game::~Game() {

}

void Game::init() {
    ifstream in("../games/newgame/assets/config.json");
    in >> config;

    camera.screen(ctx->getWidth(), ctx->getHeight());

    engine::Assets::loadTexturesFromVector(
        config["assetPath"],
        config["textures"].get<vector<string>>(),
        ctx->getRenderer()
    );

    engine::Assets::getFutures();

    bg.setGridSize(32);
    bg.setGridPos(0,0);
    bg.setTexture(engine::Assets::getTexture("bg.png"));
    bg.queryTexture();
    stage.add(&bg);

    player.setGridSize(32);
    player.setGridPos(2,2);
    player.setMovementSpeed(0.2);
    player.setTexture(engine::Assets::getTexture("test.png"));
    player.queryTexture();

    camera.setFocus(&player);
    stage.setCamera(&camera);
    stage.add(&player);

    f.setGridSize(32);
    f.generate(10);
    f.printMap();
}

void Game::update(float delta, const uint8_t* keys) {
    bool w = keys[SDL_SCANCODE_W];
    bool s = keys[SDL_SCANCODE_S];
    bool a = keys[SDL_SCANCODE_A];
    bool d = keys[SDL_SCANCODE_D];

    if (w) {
        player.up();
    }
    if (s) {
        player.down();
    }
    if (a) {
        player.left();
    }
    if (d) {
        player.right();
    }

    player.velocityUpdate(delta);
    camera.update(delta);
}

void Game::render() {
    stage.draw(ctx->getRenderer());
}

void Game::destroy() {

}
