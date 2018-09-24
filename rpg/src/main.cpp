#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <engine.hpp>
#include <experimental/filesystem>

#include "config.hpp"
#include "game.hpp"

using namespace std;
namespace fs = std::experimental::filesystem;

SDL_Surface* icon;
SDL_Event e;
bool quit;

engine::Context ctx;

engine::State* current;
Game game;

void init() {
    // a more elegant solution is needed
    #ifdef _WIN32
		
		Config::load((fs::current_path() / fs::path("assets/config-win.json")).generic_string());
    #elif __linux__
	Config::load((fs::current_path() / fs::path("assets/config.json")).generic_string());
    #endif

    int result = ctx.init(Config::getScreenWidth(), Config::getScreenHeight(), "hello world!", false);
	if (result == -1) {
		std::cout << "fatal error" << std::endl;
		std::exit(-1);
	}
}

void loadingScreen() {
    SDL_RenderClear(ctx.getRenderer());
    SDL_Texture* t = IMG_LoadTexture(ctx.getRenderer(), (fs::current_path() / fs::path("textures/loading.png")).generic_string().c_str());
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = ctx.getWidth();
    rect.h = ctx.getHeight();
    SDL_RenderCopy(ctx.getRenderer(), t, NULL, &rect);
    SDL_RenderPresent(ctx.getRenderer());
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
            }
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
        current->render(ctx);
        ctx.render();

        then = now;
    }
}

void cleanup() {
	current = nullptr;
	game.destroy();
    //SDL_FreeSurface(icon);
	ctx.destroy();
}

// for sdl on windows
#ifdef main
#undef main
#endif /* main */
int main(int argc, char** argv) {
    cout << "hello, world!" << endl;

    init();

	fs::path assetPath = fs::current_path() / Config::getAssetPath();

    /*SDL_RenderClear(r);
    SDL_Rect c;
    c.x = 10;
    c.y = 10;
    c.w = 20;
    c.h = 20;
    SDL_SetRenderDrawColor(r, 0, 200, 100, 255);
    SDL_RenderDrawRect(r, &c);
    SDL_RenderPresent(r);
    //SDL_Delay(200);*/

    //loadingScreen();

    engine::Assets::loadTexturesFromJson(ctx, fs::path(assetPath / fs::path("textures-all.json")).generic_string());
    //engine::Assets::useAll(ctx);

	game.init(ctx);

	current = &game;

    SDL_SetRenderDrawColor(ctx.getRenderer(), 0, 0, 0, 255);

    render();
    cleanup();

    return 0;
}
