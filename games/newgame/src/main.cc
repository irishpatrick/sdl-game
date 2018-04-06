#include <iostream>
#include "engine.h"
#include "game.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event e;
bool running;

engine::State* current;

void init() {
    engine::Util::initSDL(window, renderer, "title", 512, 512, false);
}

void render() {
    running = true;
    float delta;
    long now;
    long then = SDL_GetTicks();
    while (running) {
        now = SDL_GetTicks();
        delta = now - then;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                continue;
            }
        }

        const unsigned char* state = SDL_GetKeyboardState(nullptr);

        current->update(delta/1000.0f, state);

        SDL_RenderClear(renderer);
        current->render();
        SDL_RenderPresent(renderer);

        then = now;
    }
}

int main(int argc, char* argv[]) {
    cout << "hello, world!" << endl;

    init();
    current = new Game(renderer);
    render();

    delete current;

    return 0;
}
