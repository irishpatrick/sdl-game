#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "util.h"
#include "state.h"
#include "game.h"
#include "config.h"

const int WIDTH = 1024;
const int HEIGHT = 768;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface* icon;
SDL_Event e;
bool quit;

Config config;

State* current;

void init()
{
	config.load("../assets/config.json");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        exit(1);
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        printf("IMG_Init error: %s\n", IMG_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(
        "Hello World!", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        Config::screenwidth(), Config::screenheight(), SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    icon = IMG_Load("../assets/icon.png");
    if (icon != nullptr)
    {
        SDL_SetWindowIcon(window, icon);
    }
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED);

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
        }
        
        const uint8_t* state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_ESCAPE])
        {
            quit = true;
        }

        current->update(delta/1000.0f, state);

        SDL_RenderClear(renderer);
        current->render();
        SDL_RenderPresent(renderer);

        then = now;
    }
}

void cleanup()
{
    current->destroy();
    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char** argv)
{
    printf("Hello World!\n");
    
    init();

    current = new Game(renderer);
    current->init();

    render();
    cleanup();

    delete current;

    return 0;
}
