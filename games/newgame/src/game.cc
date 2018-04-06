#include "game.h"

Game::Game(SDL_Renderer* r): engine::State(r) {

}

Game::~Game() {

}

void Game::init() {
    uint32_t rmask, gmask, bmask, amask;
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    } else {
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    }
    SDL_Surface* s = SDL_CreateRGBSurface(
        0,
        512,
        512,
        32,
        rmask,
        gmask,
        bmask,
        amask
    );

    if (s == nullptr) {
        
    }
}

void Game::update(float delta, const uint8_t* state) {

}

void Game::render() {

}

void Game::destroy() {

}
