#include <iostream>
#include <SDL2/SDL.h>
#include <engine.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

#include "game.h"

using namespace std;

SDL_Window* w;
SDL_Renderer* r;
SDL_Event e;
bool running;

engine::Context ctx;
engine::State* current;

void init() {
    boost::log::add_file_log("newgame.log");
    boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= boost::log::trivial::info
    );
    ctx.init(512, 480, "title", false);
    current = new Game(&ctx);
    current->init();
}

void render() {
    running = true;

    float delta;
    uint32_t now, then;
    then = SDL_GetTicks();

    while (running) {

        now = SDL_GetTicks();
        delta = now - then;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                continue;
            }
            else if (e.type == SDL_MOUSEMOTION) {
                engine::Mouse::x = e.button.x;
                engine::Mouse::y = e.button.y;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                //cout << "mouse button down ";
                switch (e.button.button) {
                    case SDL_BUTTON_LEFT:
                        engine::Mouse::left = true;
                        break;
                    case SDL_BUTTON_MIDDLE:
                        engine::Mouse::middle = true;
                        break;
                    case SDL_BUTTON_RIGHT:
                        engine::Mouse::right = true;
                        break;
                }
                cout << endl;
            }
            else if (e.type == SDL_MOUSEBUTTONUP) {
                //cout << "mouse button up" << endl;
                switch (e.button.button) {
                    case SDL_BUTTON_LEFT:
                        engine::Mouse::left = false;
                        break;
                    case SDL_BUTTON_MIDDLE:
                        engine::Mouse::middle = false;
                        break;
                    case SDL_BUTTON_RIGHT:
                        engine::Mouse::right = false;
                        break;
                }
            }
        }

        const uint8_t* state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_ESCAPE])
        {
            running = false;
            continue;
        }

        current->update(delta/1000.0f, state);

        ctx.clear();
        current->render();
        ctx.render();

        then = now;
    }
}

void destroy() {
    delete current;
}

#ifdef main
#undef main
#endif // main

int main(int argc, char** argv) {
    cout << "hello, world!" << endl;
    init();
    render();
    destroy();
    return 0;
}
