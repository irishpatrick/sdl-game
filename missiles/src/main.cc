#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "util.h"
#include "state.h"
#include "game.h"
#include "config.h"

SDL_Window *window;
SDL_Renderer *renderer = nullptr;
SDL_Event e;
bool quit = false;

State* current;

void init()
{
    Config::loadFile("../../missiles/assets/config.json");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_DisplayMode current;
    if (SDL_GetDesktopDisplayMode(0, &current) != 0)
    {
        printf("Display Mode error: %s\n", SDL_GetError());
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        printf("IMG_Init error: %s\n", IMG_GetError());
        exit(1);
    }

    if (TTF_Init() == -1)
    {
        printf("font error: %s\n", TTF_GetError());
    }

    else
    {
        window = SDL_CreateWindow(
            "Hello World!",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            Config::getScreenWidth(), Config::getScreenHeight(), SDL_WINDOW_SHOWN);
    }

    if (window == NULL)
    {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    /*icon = IMG_Load("../assets/icon.png");
    if (icon != nullptr)
    {
        SDL_SetWindowIcon(window, icon);
    }*/

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
}

void render()
{
    float delta;
    uint32_t now;
    uint32_t then = SDL_GetTicks();

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
        }

        SDL_PumpEvents();

        int x, y = 0;
        SDL_GetMouseState(&x, &y);

        const uint8_t* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_ESCAPE])
        {
            quit = true;
        }

        //printf("direct: %d, %d\n", x, y);

        Game* g = (Game*)current;
        g->setMousePos(x, y);
        current->update(delta/1000.0, keys);

        SDL_RenderClear(renderer);
        if (current != nullptr)
        {
            current->render();
        }
        SDL_RenderPresent(renderer);

        then = now;
    }
}

void cleanup()
{
    if (current != nullptr)
    {
        current->destroy();
        //SDL_FreeSurface(icon);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

int main(int argc, char** argv)
{
    std::cout << "hello world!" << std::endl;

    init();
    current = new Game(renderer);
    current->init();
    render();
    cleanup();

    return 0;
}
