#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <engine.hpp>
#include <nlohmann/json.hpp>
#include "game.hpp"

using json = nlohmann::json;

engine::Context ctx;
Game game;
SDL_Event e;
bool quit;
json config;

void init() {
	srand(time(nullptr));
	
	std::string config_file("D:/GitHub/sdl-game/catch/assets/config-win.json");

	std::ifstream i(config_file);
	if (i.fail())
	{
		std::cout << "failed to load " << config_file << std::endl;
		std::exit(1);
	}
	i >> config;
	std::cout << "load config" << std::endl;
	int err = ctx.init(config["screenWidth"].get<int>(), config["screenHeight"].get<int>(), config["title"].get<std::string>(), false);
	if (err < 0)
	{
		std::cout << "something is wrong here" << std::endl;
	}
	engine::Assets::loadTexturesFromJson("assets.json", config["assetPath"].get<std::string>(), ctx);
	//engine::Assets::useAll(ctx);
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
		if (state[SDL_SCANCODE_ESCAPE]) {
			quit = true;
		}

		game.update(delta / 1000.0f, state);

		ctx.clear();
		game.render(ctx);
		ctx.render();

		then = now;
	}
}

void cleanup() {
	game.destroy();
	ctx.destroy();
}

#ifdef main
#undef main
#endif /* main */
int main(int argc, char** argv) {
	std::cout << "hello world" << std::endl;

	init();

	game.init(ctx);
	render();
	cleanup();

	return 0;
}