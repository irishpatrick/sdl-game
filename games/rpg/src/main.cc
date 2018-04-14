#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <engine.h>

#include "config.h"
#include "game.h"

SDL_Surface* icon;
SDL_Event e;
bool quit;

engine::Context ctx;

engine::State* current;

void init()
{
    Config::load("../../games/rpg/assets/config.json");

    ctx.init(Config::getScreenWidth(), Config::getScreenHeight(), "hello world!", false);

    //engine::Util::initSDL(&window, &renderer, "Hello, World!", 512, 480, Config::fullscreen());

    if (!IMG_Init(IMG_INIT_PNG))
    {
        printf("IMG_Init error: %s\n", IMG_GetError());
        exit(1);
    }

    if (TTF_Init() == -1)
    {
        printf("font error: %s\n", TTF_GetError());
    }
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

            engine::Controllers::ProcessEvent(e);
        }



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

#undef main
int main(int argc, char** argv)
{
    printf("Hello World!\n");

    init();

    current = new Game(&ctx);
    current->init();

    render();
    cleanup();

    delete current;

    return 0;
}
