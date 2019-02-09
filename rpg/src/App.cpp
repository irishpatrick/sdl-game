#include "App.hpp"
#include "Config.hpp"
#include <nlohmann/json.hpp>

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

<<<<<<< HEAD
	//engine::Assets::loadTexturesFromJson(ctx, fs::path(assetPath / "textures-all.json").generic_string());

    stf::Loader ldr;
    ldr.open((fs::current_path() / "assets" / "textures.stf").generic_string());
    std::string dir = ldr.getSection("data").getValue<std::string>("dir");
    engine::Assets::loadTexturesFromVector(dir, ldr.getSection("files").getLines<std::string>(), ctx);
=======
	json o;
	std::ifstream in((fs::current_path() / "assets" / "textures.json").generic_string());
	in >> o;
>>>>>>> fff90d22d53fc400c2a2489284776e86d619d4fb

	engine::Assets::loadTexturesFromVector(o["dir"], o["files"], ctx);

	game.init(ctx);
	title.init(ctx);
	mapTest.init(ctx);

	addState("game", &game);
	addState("title", &title);
	addState("mapTest", &mapTest);
	setCurrentState("mapTest");
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
