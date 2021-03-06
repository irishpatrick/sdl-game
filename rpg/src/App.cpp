#include "App.hpp"
#include "Config.hpp"
#include <nlohmann/json.hpp>
#include <cstdlib>

using json = nlohmann::json;

bool App::running = false;

App::App()
{
	deltaBuffer = 0;
}

App::~App()
{

}

void App::quitCallback()
{
	running = false;
}

void App::init()
{
	Config::load((fs::current_path() / fs::path("assets/config.json")).generic_string());

	int result = ctx.init(Config::getScreenWidth(), Config::getScreenHeight(), "title", false);
	if (result < 0) std::exit(-1);

	ctx.setQuitCallback(App::quitCallback);

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
	//setCurrentState("mapTest");
	setCurrentState("game");
}

void App::draw()
{
	engine::MovingAverage<long> avg;
	avg.allocate(10);

	long delta = 0;
	long now;
	long then = engine::Timer::getNanoTime();
	running = true;

	while (running)
	{
		now = engine::Timer::getNanoTime();
		delta = now - then;
		then = now;

		avg.shiftIn(delta);

		ctx.pollEvents();

		//std::cout << "delta: " << delta << " avg: " << snap.getAverage() << std::endl;
		//std::cout << "snap: " << snap.string() << std::endl;
		//SDL_Delay(200);
		getCurrentState()->update((float)(avg.getAverage()) / (float)(1e9));

		ctx.clear();
		getCurrentState()->render(ctx);
		ctx.render();
	}

	/*while (running)
	{

		now = engine::Timer::getNanoTime();
        delta = now - then;
        lag += delta;
        then = now;

        while (lag >= NS_PER_UPDATE)
        {
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					quit();
				}
			}
            getCurrentState()->update(((float)lag / (float)1e6) / (float)(NS_PER_UPDATE / 1e6));
            lag -= NS_PER_UPDATE;
        }

		ctx.clear();
		getCurrentState()->render(ctx);
		ctx.render();
	}*/

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

	/*while (running)
	{
		now = engine::Timer::getNanoTime();
		delta = now - then;
		then = now;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit();
			}
		}

		getCurrentState()->update((float)(delta * 1e-9));

		ctx.clear();
		getCurrentState()->render(ctx);
		ctx.render();
	}*/
}

void App::mainLoop()
{

}
