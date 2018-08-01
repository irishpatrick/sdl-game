#include <SDL.h>
#include <iostream>
#include <engine.hpp>

bool quit = false;
SDL_Event e;
engine::Context ctx;

void init() {
    ctx.init(512, 480, "title", false);
}

void fontTest() {

}

void render() {
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            const uint8_t* state = SDL_GetKeyboardState(nullptr);
            if (state[SDL_SCANCODE_ESCAPE]) {
                quit = true;
            }
        }

        ctx.clear();
        fontTest();
        ctx.render();
    }
}

void cleanup() {

}

// for sdl on windows
#ifdef main
#undef main
#endif /* main */
int main(int argc, char** argv) {
    std::cout << "hello world" << std::endl;
    init();
    render();
    cleanup();
    return 0;
}
