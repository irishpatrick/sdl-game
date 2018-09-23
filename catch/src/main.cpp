#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <experimental/filesystem>
#include <engine.hpp>
#include <nlohmann/json.hpp>
#include "game.hpp"
#include <spdlog/spdlog.h>

using json = nlohmann::json;
namespace fs = std::experimental::filesystem;

engine::Context ctx;
Game game;
SDL_Event e;
bool quit;
json config;

engine::KeyFrameSprite test;

void init() {
	srand(time(nullptr));

	engine::Util::initSpdlog();
	auto logger = spdlog::get("logger");
	logger->info("this is a test of the logger");

	//std::string config_file("D:/GitHub/sdl-game/catch/assets/config-win.json");
	//std::string config_file = "./assets/config-win.json";
	//std::string config_file = "../assets/config-win.json";

	fs::path config_file("assets/config-win.json");
	fs::path assetPath("assets");

	std::ifstream i((fs::current_path() / config_file).generic_string());
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
	engine::Assets::setCwd((fs::current_path() / assetPath).generic_string());
	engine::Assets::loadTexturesFromJson(ctx, (fs::current_path() / assetPath / "assets.json").generic_string());

	std::cout << "init keyframe test" << std::endl;
	test.init(ctx, (fs::current_path() / "assets" / "test.json").generic_string());
	test.setCurrentAnimation("walk", true);
}

void render()
{
	long delta;
	long now;
	long then = engine::Timer::getNanoTime();
	quit = false;

	while (!quit)
	{
		now = engine::Timer::getNanoTime();
		delta = now - then;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
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

		game.update(engine::Timer::toSeconds(delta, engine::Unit::NANO), state);
		test.update(engine::Timer::toSeconds(delta, engine::Unit::NANO));

		ctx.clear();
		game.render(ctx);
		test.draw(ctx);
		ctx.render();

		then = now;
	}
}

void cleanup()
{
	game.destroy();
	ctx.destroy();
}

#ifdef main
#undef main
#endif /* main */
int main(int argc, char** argv)
{

	init();

	game.init(ctx);
	render();
	cleanup();

	return 0;
}
