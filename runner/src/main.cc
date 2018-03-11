#include <iostream>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <engine.h>

#include "game.h"

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface* icon;
SDL_Event e;
bool quit;

engine::State* current;

void init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        exit(1);
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("IMG_Init error: %s\n", IMG_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(
        "Title",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        512, 480,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        cout << "window error: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        cout << "renderer error: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
}

void render() {
    float delta;
    uint32_t now;
    uint32_t then = SDL_GetTicks();
    quit = false;
    while (!quit) {
        now = SDL_GetTicks();
        delta = now - then;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                continue;
            }
        }

        const uint8_t* state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_ESCAPE]) {
            quit = true;
            continue;
        }

        if (current == nullptr) {
            continue;
        }

        current->update(delta/1000.0f, state);

        SDL_RenderClear(renderer);
        current->render();
        SDL_RenderPresent(renderer);

        then = now;
    }
}

void cleanup() {
    current->destroy();
    delete current;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void create() {
    current = new Game(renderer);
    current->init();
}

int main(int argc, char** argv) {
    init();
    create();
    render();
    cleanup();

    return 0;
}
