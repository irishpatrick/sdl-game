#include "App.hpp"
#include "Config.hpp"
#include <nlohmann/json.hpp>
#include <cstdlib>

#define MS_PER_FRAME 16
#define MS_PER_UPDATE 33

using json = nlohmann::json;

App::App()
{

}

App::~App()
{

}

void App::init()
{
#ifdef _WIN32
		Config::load((fs::current_path() / fs::path("assets/config-win.json")).generic_string());
	#elif __linux__
		Config::load((fs::current_path() / fs::path("assets/config.json")).generic_string());
	#endif

	int result = ctx.init(Config::getScreenWidth(), Config::getScreenHeight(), "title", false);
	if (result < 0) std::exit(-1);

	fs::path assetPath = fs::current_path() / "assets";
	engine::Assets::setCwd(assetPath);

	std::string fn = (fs::current_path() / "assets" / "textures.json").generic_string();
	json o = engine::Util::loadJson(fn);

	engine::Assets::loadTexturesFromVector(o["dir"], o["files"], ctx);

	game.init(ctx);
	title.init(ctx);
	mapTest.init(ctx);

	addState("game", &game);
	addState("title", &title);
	addState("mapTest", &mapTest);
	setCurrentState("game");
}

void App::draw()
{
	long delta = 0;
	long now;
	long then = engine::Timer::getNanoTime() / 1e6;
    double lag = 0;
	while (running)
	{
		now = engine::Timer::getNanoTime() / 1e6;
        delta = now - then;
        lag += delta;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit();
			}
		}

        while (lag >= MS_PER_UPDATE)
        {
            getCurrentState()->update((float)lag / MS_PER_UPDATE);
            lag -= MS_PER_UPDATE;
        }

		ctx.clear();
		getCurrentState()->render(ctx);
		ctx.render();

		then = now;
	}

    /*while (running)
    {
        now = engine::Timer::getNanoTime();
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit();
            }
        }

        getCurrentState()->update(1.0f);
        ctx.clear();
        getCurrentState()->render(ctx);
        ctx.render();

        long delay = (now/1e9) + MS_PER_FRAME - (engine::Timer::getNanoTime()/1e9);
        //std::cout << "delay: " << delay << std::endl;
        SDL_Delay(delay);
    }*/
}

void App::mainLoop()
{

}
