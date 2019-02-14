#include "App.hpp"
#include <cstdio>
#include <cstring>

static int n = 0;

#define MS 16

App::App()
{

}

App::~App()
{

}

void App::init()
{
    ctx.init(200, 200, "testbench", false);
}

void App::mainLoop()
{
    
}

void App::draw()
{
    FILE* fp = fopen("log1.csv", "w");
    long now = 0;
    long then = engine::Timer::getNanoTime() / 1e6;
    float lag = 0.0f;
    float delta = 0.0f;
    bool quit = false;
    char line[100];
    while (!quit)
    {
        now = engine::Timer::getNanoTime() / 1e6;
        delta = now - then;
        lag += delta;
        then = now;

        while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

        while (lag >= MS)
        {
            lag -= MS;
        }

        ctx.clear();
        fprintf(fp, "%d,%f\n", n, delta);
        ctx.render();

        n++;
    }
    fclose(fp);
}
