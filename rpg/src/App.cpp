#include "App.hpp"
#include "Config.hpp"

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
	engine::Assets::loadTexturesFromJson(ctx, fs::path(assetPath / "textures-all.json").generic_string());

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
	long delta;
	long now;
	long then = engine::Timer::getNanoTime();

	while (running)
	{
		now = engine::Timer::getNanoTime();
		delta = now - then;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit();
			}
		}

		getCurrentState()->update((float)delta / (float)(1e9));

		ctx.clear();
		getCurrentState()->render(ctx);
		ctx.render();

		then = now;
	}
}

void App::mainLoop()
{

}
