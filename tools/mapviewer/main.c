#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "maze.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event e;
int quit = 0;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Map Viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 480, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    maze_init(renderer);
}

void update()
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            quit = 1;
        }
    }
}

void draw()
{

}

int main(int argc, char** argv)
{
    init();
    while (!quit)
    {
        update();
        SDL_RenderClear(renderer);
        draw();
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}