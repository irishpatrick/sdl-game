#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <engine.h>

#include "config.hpp"
#include "game.hpp"

using namespace std;

SDL_Surface* icon;
SDL_Event e;
bool quit;

engine::Context ctx;

engine::State* current;

void init()
{
    Config::load("../games/rpg/assets/config.json");

    ctx.init(Config::getScreenWidth(), Config::getScreenHeight(), "hello world!", false);

    //engine::Util::initSDL(&window, &renderer, "Hello, World!", 512, 480, Config::fullscreen());

    if (!IMG_Init(IMG_INIT_PNG))
    {
        printf("IMG_Init error: %s\n", IMG_GetError());
        exit(1);
    }

    /*if (TTF_Init() == -1)
    {
        printf("font error: %s\n", TTF_GetError());
    }*/
}

void render()
{
    float delta;
    uint32_t now;
    uint32_t then = SDL_GetTicks();

    quit = false;
    while (!quit)
    {
        now = SDL_GetTicks();
        delta = now - then;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
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
            engine::Controllers::ProcessEvent(e);
        }

        int x;
        int y;
        SDL_GetMouseState(&x, &y);

        const uint8_t* state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_ESCAPE])
        {
            quit = true;
        }

        current->update(delta/1000.0f, state);

        ctx.clear();
        current->render();
        ctx.render();

        then = now;
    }
}

void cleanup()
{
    current->destroy();
    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(ctx.getRenderer());
    SDL_DestroyWindow(ctx.getWindow());
    SDL_Quit();
}

#ifdef main
#undef main
#endif /* main */
int main(int argc, char** argv)
{
    cout << "hello, world!" << endl;

    init();

    string textures = Config::getAssetPath() + "textures/";
    SDL_Renderer* r = ctx.getRenderer();
    engine::Assets::loadTexture(textures + "med-background.png", r);
    engine::Assets::loadTexture(textures + "hero.png", r);
    engine::Assets::loadTexture(textures + "monster.png", r);
    engine::Assets::loadTexture(textures + "grass1.png", r);
    engine::Assets::loadTexture(textures + "room-bg.png", r);
    engine::Assets::loadTexture(textures + "opposite.png", r);
    engine::Assets::loadTexture(textures + "animtest.png", r);
    engine::Assets::loadTexture(textures + "door.png", r);
    engine::Assets::loadTexture(Config::getAssetPath() + "font/out.png", r);
    engine::Assets::getFutures();

    current = new Game(&ctx);
    current->init();

    render();
    cleanup();

    delete current;

    return 0;
}
